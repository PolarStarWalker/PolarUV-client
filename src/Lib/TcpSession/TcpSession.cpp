#include "TcpSession.hpp"

#include <iostream>

using namespace lib::network;

TcpSession *TcpSession::GetInstance() {
    static TcpSession instance;
    return &instance;
}


void test(){
    //boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("192.168.1.50"), 2022);

    boost::asio::io_context ioContext;

    boost::asio::ip::tcp::socket socket(ioContext);

    boost::system::error_code errorCode;

    socket.connect(endpoint, errorCode);

    if (errorCode.failed()) {
        std::cerr << errorCode.value() << " " << errorCode.message() << std::endl;
        return;
    }

    while (socket.is_open()) {

        std::string msg;
        std::getline(std::cin, msg);

        size_t length = socket.write_some(boost::asio::buffer(msg), errorCode);

        if (errorCode.failed())
            socket.close();

        if (!length)
            socket.close();
    }
}