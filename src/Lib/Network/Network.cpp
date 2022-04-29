#include "Network.hpp"

#include <array>
#include <iostream>
#include <zstd.h>

using namespace lib::network;

using ErrorCode = boost::system::error_code;
using ConstBuffer = boost::asio::const_buffer;
using MutableBuffer = boost::asio::mutable_buffer;


constexpr size_t REQUEST_HEADER_SIZE = sizeof(Request::HeaderType);
constexpr size_t RESPONSE_HEADER_SIZE = sizeof(Response::HeaderType);

Network::Network() :
        ioContext_(),
        socket_(ioContext_) {}

Response Network::SendRequest(std::string_view data, Request::TypeEnum type, ssize_t endpointId) {
    using TimePoint = std::chrono::steady_clock::time_point;

    auto compressed = Compress(data);

    std::unique_lock lock(requestsMutex_);

    TimePoint requestBegin = std::chrono::steady_clock::now();

    auto request = Request({compressed.data(), compressed.size()}, type, endpointId);

    auto response = TransferData(request);

    lock.unlock();

    TimePoint end = std::chrono::steady_clock::now();
    std::cout << request.Header
              << "\nRequest Time = "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - requestBegin).count()
              << "[ns]" << std::endl;

    return response;
}

bool Network::TryConnect(const std::string &ip) {
    using endpoint_type = boost::asio::ip::tcp::resolver::endpoint_type;

    socket_.close();

    endpoint_type endpoint(boost::asio::ip::make_address(ip), PORT);

    socket_.async_connect(endpoint, [&](const ErrorCode &errorCode) {});

    if (!RunFor(CONNECTION_TIMEOUT))
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

    std::string responseData;
    Response::HeaderType responseHeader;
    std::array<ConstBuffer, 2> requestData{ConstBuffer(&request.Header, REQUEST_HEADER_SIZE),
                                           ConstBuffer(request.Data.data(), request.Header.Length)};

    auto setErrorData = [](std::string &data, Response::HeaderType &header, ssize_t endpointId) {
        data = "";
        header.Code = Response::ConnectionError;
        header.EndpointId = endpointId;
    };

    auto readDataCallback = [&](const ErrorCode &errorCode, size_t bytes) {
        if (errorCode.failed())
            setErrorData(responseData, responseHeader, request.Header.EndpointId);
    };

    auto readHeaderCallback = [&](const ErrorCode &errorCode, size_t bytes) {

        if (errorCode.failed()) {
            setErrorData(responseData, responseHeader, request.Header.EndpointId);
            return;
        }

        responseData = std::string(responseHeader.Length, 0);

        async_read(socket_,
                   MutableBuffer(responseData.data(), responseHeader.Length),
                   transfer_exactly(responseHeader.Length),
                   readDataCallback);
    };

    auto requestCallback = [&](const ErrorCode &errorCode, size_t bytes) {
        if (errorCode.failed()) {
            setErrorData(responseData, responseHeader, request.Header.EndpointId);
            return;
        }

        async_read(socket_,
                   MutableBuffer(&responseHeader, RESPONSE_HEADER_SIZE),
                   transfer_exactly(RESPONSE_HEADER_SIZE),
                   readHeaderCallback);

    };

    async_write(socket_,
                requestData,
                transfer_exactly(REQUEST_HEADER_SIZE + request.Header.Length),
                requestCallback);

    if (!RunFor(TRANSFER_TIMEOUT))
        setErrorData(responseData, responseHeader, request.Header.EndpointId);

    return {std::move(responseData), responseHeader.Code, responseHeader.EndpointId};
}

std::vector<char> Network::Compress(const std::string_view &data) {
    auto maxCompressSize = ZSTD_compressBound(data.size());

    std::vector<char> compressed(maxCompressSize, 0);

    auto compressSize = ZSTD_compress(&compressed[0], maxCompressSize, &data[0], data.size(), 0);

    compressed.resize(compressSize);

    return compressed;
}