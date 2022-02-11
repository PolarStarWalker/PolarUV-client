#include "Network.hpp"

#include <iostream>

using namespace lib::network;

using Socket = boost::asio::ip::tcp::socket;
using ErrorCode = boost::system::error_code;

constexpr size_t REQUEST_HEADER_SIZE = sizeof(Request::HeaderType);
constexpr size_t RESPONSE_HEADER_SIZE = sizeof(Response::HeaderType);

Network::Network() :
        ioContext_(),
        socket_(ioContext_),
        isOnline_(false) {}

Response Network::SendRequest(std::string_view data, Request::TypeEnum type, ssize_t endpointId) {
    std::lock_guard guard(requestsMutex_);

    auto response = TransferData({data, type, endpointId});

    return response;
}

bool Network::TryConnect(const std::string &ip) {
    using endpoint_type = boost::asio::ip::tcp::resolver::endpoint_type;

    socket_.close();

    endpoint_type endpoint(boost::asio::ip::make_address(ip), PORT);

    socket_.async_connect(endpoint, [&](const ErrorCode &errorCode) {
        isOnline_ = !errorCode.failed();
    });

    if (!RunFor(TIMEOUT))
        return false;

    return true;
}

bool Network::RunFor(std::chrono::steady_clock::duration timeout) {
    ioContext_.restart();

    ioContext_.run_for(timeout);

    if (ioContext_.stopped())
        return true;

    socket_.close();
    ioContext_.run();
    return false;
}

Response Network::TransferData(const Request &request) {
    using namespace boost::asio;
    using namespace std::chrono_literals;

    std::string data;
    Response::HeaderType responseHeader;

    auto setErrorData = [](std::string &data, Response::HeaderType &header, ssize_t endpointId) {
        data = "";
        header.Code = Response::ConnectionError;
        header.EndpointId = endpointId;
    };

    auto readDataCallback = [&](const ErrorCode &errorCode, size_t bytes) {
        if (errorCode.failed())
            setErrorData(data, responseHeader, request.Header.EndpointId);
    };

    auto readHeaderCallback = [&](const ErrorCode &errorCode, size_t bytes) {

        if (errorCode.failed()) {
            setErrorData(data, responseHeader, request.Header.EndpointId);
            return;
        }

        data = std::string(responseHeader.Length, 0);

        async_read(socket_,
                   buffer(data),
                   transfer_exactly(data.size()),
                   readDataCallback);
    };

    auto sendDataCallback = [&](const ErrorCode &errorCode, size_t bytes) {
        if (errorCode.failed()) {
            setErrorData(data, responseHeader, request.Header.EndpointId);
            return;
        }

        async_read(socket_,
                   buffer(&responseHeader, RESPONSE_HEADER_SIZE),
                   transfer_exactly(RESPONSE_HEADER_SIZE),
                   readHeaderCallback);

    };

    auto sendHeaderCallback = [&](const ErrorCode &errorCode, size_t bytes) {

        if (errorCode.failed()) {
            setErrorData(data, responseHeader, request.Header.EndpointId);
            return;
        }

        async_write(socket_,
                    buffer(request.Data.begin(), request.Header.Length),
                    transfer_exactly(request.Header.Length),
                    sendDataCallback);
    };

    async_write(socket_,
                buffer(&request.Header, REQUEST_HEADER_SIZE),
                transfer_exactly(REQUEST_HEADER_SIZE),
                sendHeaderCallback);

    if (!RunFor(100ms))
        setErrorData(data, responseHeader, request.Header.EndpointId);

    return {std::move(data), responseHeader.Code, responseHeader.EndpointId};
}
