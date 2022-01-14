#include "TcpSession.hpp"

#include <iostream>

using namespace lib::network;

TcpSession::TcpSession(QObject *parent) : QObject(parent) {}

TcpSession &TcpSession::GetInstance() {
    static TcpSession instance;
    return instance;
}

Response TcpSession::Send(const Packet &packet) const {

    if(!_status) return {"", Response::ConnectionError};

    std::promise<Response *> promise;
    auto future = promise.get_future();

    TcpRequest request(promise, packet);

    AddToQueue(request);

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

    for (;;) {

        for (;;) {
            ErrorCode errorCode;
            socket.connect(ENDPOINT, errorCode);

            if (!errorCode.failed()) break;

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

        while (socket.is_open()) {

            std::unique_lock guard(_requestsMutex);

            _queueIsNotEmpty.wait(guard, [&]() noexcept {return _requests.empty();});

            TcpRequest request = *_requests.front();
            _requests.pop();

            ErrorCode errorCode;
            size_t length = boost::asio::write(socket,
                                               buffer(request.Packet.Data),
                                               transfer_exactly(request.Packet.Data.size()),
                                               errorCode);

            if (errorCode.failed() || !length) {
                socket.close();
                _status.store(false);
            }

        }
    }
}

void TcpSession::AddToQueue(const TcpRequest& request) const {
    std::lock_guard guard(_requestsMutex);
    _requests.push(&request);
    _queueIsNotEmpty.notify_one();
}

void test() {
    //boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("192.168.1.50"), 2022);

    boost::asio::io_context ioContext;

    boost::asio::ip::tcp::socket socket(ioContext);

    boost::system::error_code errorCode;

    socket.connect(ENDPOINT, errorCode);

    if (errorCode.failed()) {
        std::cerr << errorCode.value() << " " << errorCode.message() << std::endl;
        return;
    }

    while (socket.is_open()) {

        std::string msg;
        std::getline(std::cin, msg);

        size_t length = boost::asio::write(socket,
                                           boost::asio::buffer(msg),
                                           boost::asio::transfer_exactly(32),
                                           errorCode);

        if (errorCode.failed())
            socket.close();

        if (!length)
            socket.close();
    }
}