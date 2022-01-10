#include "TcpSession.hpp"

#include <iostream>

using namespace lib::network;

TcpSession &TcpSession::GetInstance() {
    static TcpSession instance;
    return instance;
}

Response TcpSession::Send(const Packet &packet) const {

    std::promise<Response* > promise;
    auto future = promise.get_future();

    TcpRequest request(promise, packet);

    {
        std::lock_guard<std::shared_mutex> guard(_requestsMutex);
        _requests.push(&request);
    }

    return *(future.get());
}

void test(){
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

        size_t length = boost::asio::write(socket, boost::asio::buffer(msg), boost::asio::transfer_exactly(32), errorCode);

        if (errorCode.failed())
            socket.close();

        if (!length)
            socket.close();
    }
}