#include "TcpSession.hpp"

#include <iostream>

using namespace lib::network;

using Socket = boost::asio::ip::tcp::socket;
using ErrorCode = boost::system::error_code;
using IOContext = boost::asio::io_context;
using Endpoint = boost::asio::ip::tcp::endpoint;

constexpr size_t PORT = TcpSession::PORT;
constexpr size_t REQUEST_HEADER_SIZE = sizeof(Request::HeaderType);
constexpr size_t RESPONSE_HEADER_SIZE = sizeof(Response::HeaderType);


inline ErrorCode TryConnect(const std::string_view &IP, Socket &socket) {

    Endpoint endpoint(boost::asio::ip::make_address(IP), PORT);

    std::clog << "[TRY CONNECT]" << std::endl;

    ErrorCode errorCode;
    socket.connect(endpoint, errorCode);

    return errorCode;
}

inline std::pair<int, ErrorCode> SendData(Socket &socket, const Request &request) {
    using namespace boost::asio;

    ErrorCode errorCode;

    std::cout << "\n[HEADER SIZE]  " << REQUEST_HEADER_SIZE << std::endl;

    ///SendHeader
    size_t length = write(socket,
                          buffer(&request.Header, REQUEST_HEADER_SIZE),
                          transfer_exactly(REQUEST_HEADER_SIZE),
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

    Response::HeaderType header;

    size_t length = read(socket,
                         buffer(&header, RESPONSE_HEADER_SIZE),
                         transfer_exactly(RESPONSE_HEADER_SIZE));

    std::string data(header.Length, 0);

    if (header.Length > 0)
        length += read(socket,
                       buffer(data.data(), data.size()),
                       transfer_exactly(header.Length));

    return {std::move(data), header.Code, header.EndpointId};
}

/*************************TcpSession member functions********************************/
void TcpSession::Start() {

    IOContext ioContext;
    Socket socket(ioContext);

    std::string_view IP = "192.168.1.25";

    while (!_isDone) {

        ///Connect
        while (!_isDone) {

            auto errorCode = TryConnect(IP, socket);

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
            auto &request = _request.GetTask();

            if (request.Header.EndpointId == -1) {
                socket.close();
                _isDone.store(true);
            }

            auto[length, errorCode] = SendData(socket, request);

            if (errorCode.failed() || length != request.Data.size() + REQUEST_HEADER_SIZE) {
                socket.close();
                _status.store(false);
                request.Response.set_value(Response("Проблемы с соединением", Response::ConnectionError, -1));
                break;
            }

            Response response = ReadData(socket);

            request.Response.set_value(std::move(response));
        }
    }
}

TcpSession::TcpSession(QObject *parent) :
        QObject(parent) {
    thread_ = std::thread(&TcpSession::Start, this);
}

TcpSession::~TcpSession() noexcept {
    //poison pill
    auto future = SendRequest("", Request::TypeEnum::W, -1);
    thread_.detach();
}

TcpSession &TcpSession::GetInstance() {
    static TcpSession instance;
    return instance;
}

Response TcpSession::SendRequest(std::string_view data, Request::TypeEnum type, ssize_t endpointId) {

    if (endpointId < 1 && !(data == "" && type == Request::TypeEnum::W && endpointId == -1))
        return {std::string("Неправильный адрес"), Response::ConnectionError, endpointId};

    std::clog << "[SENDING DATA]" << std::endl;
    ///ToDo очень ленивое решение, нужно лучше
    if (!_status)
        return {"Соединение не установлено", Response::ConnectionError, -1};

    std::promise<Response> promise;
    auto future = promise.get_future();

    Request request(data, type, endpointId, promise);

    _request.AddToQueue(request);

    return future.get();
}