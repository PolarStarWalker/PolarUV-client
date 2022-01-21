#include "TcpSession.hpp"

#include <iostream>

using namespace lib::network;

using Socket = boost::asio::ip::tcp::socket;
using ErrorCode = boost::system::error_code;

TcpSession::TcpSession(QObject *parent) :
        QObject(parent) {
    _thread = std::thread(&TcpSession::Start, this);
    _thread.detach();
}

TcpSession::~TcpSession() noexcept {
    //poison pill
    auto future = Send("", Request::TypeEnum::W, -1);
}

TcpSession &TcpSession::GetInstance() {
    static TcpSession instance;
    return instance;
}

Response TcpSession::Send(std::string_view data, Request::TypeEnum type, ssize_t endpointId) const {


    std::clog << "SendingData" << std::endl;
    ///ToDo очень ленивое решение, нужно лучше
    if (!_status) {
        std::clog << "[CONNECTION IS INACTIVE]" << std::endl;
        return {std::string(), Response::ConnectionError, -1};
    }
    std::promise<Response> promise;
    auto future = promise.get_future();

    Request request(data, type, endpointId, promise);

    AddTaskToQueue(request);

    return future.get();
}

inline std::pair<int, ErrorCode> SendData(Socket &socket, const Request &request) {
    using namespace boost::asio;
    constexpr size_t HeaderSize = sizeof(Request::HeaderType);

    ErrorCode errorCode;

    std::cout << "\n[HEADER SIZE]  " << HeaderSize << std::endl;

    ///SendHeader
    size_t length = write(socket,
                          buffer(&request.Header, HeaderSize),
                          transfer_exactly(HeaderSize),
                          errorCode);

    std::clog << "[REQUEST TYPE]: " << (size_t) request.Header.Type
              << "\n[ENDPOINT]: " << request.Header.EndpointId
              << "\n[DATA LENGTH]: " << request.Header.Length << std::endl;

    length += write(socket,
                    buffer(request.Data),
                    transfer_exactly(request.Header.Length),
                    errorCode);

    std::clog << "[BYTES SEND]: " << length << '\n' << std::endl;

    std::clog << '|';
    for (uint32_t symbol: request.Data) {
        std::clog << symbol << '|';
    }
    std::clog << std::endl;

    return {length, errorCode};
}

inline Response ReadData(Socket &socket) {
    using namespace boost::asio;
    constexpr size_t HeaderSize = sizeof(Response::HeaderType);

    Response::HeaderType header;

    size_t length = read(socket,
                         buffer(&header, HeaderSize),
                         transfer_exactly(HeaderSize));

    std::string data(header.Length, 0);

    if (header.Length > 0)
        length += read(socket,
                       buffer(data.data(), data.size()),
                       transfer_exactly(header.Length));

    return {std::move(data), header.Code, header.EndpointId};
}

void TcpSession::Start() {
    using namespace boost::asio;
    constexpr size_t HeaderSize = sizeof(Request::HeaderType);

    io_context ioContext;
    ip::tcp::socket socket(ioContext);

    constexpr size_t PORT = 2022;
    std::string_view IP = "192.168.1.25";
    ip::tcp::endpoint ENDPOINT(boost::asio::ip::make_address(IP), PORT);

    while (!_isDone) {

        ///Connect
        while (!_isDone) {

            std::clog << "[TRY CONNECT]" << std::endl;

            ErrorCode errorCode;
            socket.connect(ENDPOINT, errorCode);

            if (!errorCode.failed()) {
                _status.store(true);
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        std::clog << "[CONNECTED]" << std::endl;

        ///main cycle
        while (socket.is_open()) {

            ///ToDo пофиксить блокирующую очередь
            /// когда мы зависним на таске, а связь разорвётся, то застопорившись здесь мы не узнаем об этом
            auto &request = GetTask();

            if (request.Header.EndpointId == -1) {
                socket.close();
                _isDone.store(true);
            }

            auto[length, errorCode] = SendData(socket, request);

            if (errorCode.failed() || length != request.Data.size() + HeaderSize) {
                socket.close();
                _status.store(false);
                request.Response.set_value(Response("", Response::ConnectionError, -1));
                break;
            }

            Response response = ReadData(socket);

            request.Response.set_value(std::move(response));
        }
    }
}

void TcpSession::AddTaskToQueue(Request &request) const {
    std::lock_guard guard(_requestsMutex);
    _requests.push(&request);
    _queueIsNotEmpty.notify_one();
}

Request &TcpSession::GetTask() {
    std::unique_lock guard(_requestsMutex);

    _queueIsNotEmpty.wait(guard, [&]() noexcept { return !_requests.empty(); });

    auto &request = *_requests.front();
    _requests.pop();

    return request;
}