#include "TcpSession.hpp"

#include <iostream>

using namespace lib::network;

TcpSession::TcpSession(QObject *parent) :
        QObject(parent) {
    _thread = std::thread(&TcpSession::Start, this);
    _thread.detach();
}

TcpSession::~TcpSession() noexcept {
    //poison pill
    auto future  = Send(Packet(Packet::TypeEnum::W, "", -1));
    _thread.join();
}

TcpSession &TcpSession::GetInstance() {
    static TcpSession instance;
    return instance;
}

Response TcpSession::Send(const Packet &packet) const {

    if (!_status) return {"", Response::ConnectionError};

    std::promise<Response *> promise;
    auto future = promise.get_future();

    TcpRequest request(promise, packet);

    AddTaskToQueue(request);

    return *(future.get());
}

Response TcpSession::Send(Packet &&packet) const {
    return Send(packet);
}

void TcpSession::Start() {

    using namespace boost::asio;
    using ErrorCode = boost::system::error_code;

    io_context ioContext;
    ip::tcp::socket socket(ioContext);

    size_t PORT = 2022;
    std::string_view IP = "192.168.1.50";
    ip::tcp::endpoint ENDPOINT(boost::asio::ip::make_address(IP), PORT);

    while (!_isDone) {

        ///Connect
        for (;;) {

            std::clog << "start listening" << std::endl;

            ErrorCode errorCode;
            socket.connect(ENDPOINT, errorCode);

            if (!errorCode.failed()) break;

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        ///main cycle
        while (socket.is_open()) {

            auto &request = GetTask();

            if (request.Packet.EndpointId == -1) {
                socket.close();
                _isDone.store(true);
            }

            ErrorCode errorCode;

            ///some transfer logic
            size_t length = boost::asio::write(socket,
                                               buffer(request.Packet.Data),
                                               transfer_exactly(request.Packet.Data.size()),
                                               errorCode);

            if (errorCode.failed() || !length) {
                socket.close();
                _status.store(false);
                break;
            }
        }
    }
}

void TcpSession::AddTaskToQueue(const TcpRequest &request) const {
    std::lock_guard guard(_requestsMutex);
    _requests.push(&request);
    _queueIsNotEmpty.notify_one();
}

const TcpRequest &TcpSession::GetTask() {
    std::unique_lock guard(_requestsMutex);

    _queueIsNotEmpty.wait(guard, [&]() noexcept { return _requests.empty(); });

    auto &request = *_requests.front();
    _requests.pop();

    return request;
}