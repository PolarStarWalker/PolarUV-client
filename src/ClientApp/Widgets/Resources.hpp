#ifndef CLIENT_RESOURCES_HPP
#define CLIENT_RESOURCES_HPP

#include <TcpSession/TcpSession.hpp>
#include <string>

struct Resources {

    explicit Resources(boost::asio::io_context &ioContext) : Network(ioContext) {}

    lib::network::Network Network;
    std::string ClientIp{};
    int GamepadId{};
};




#endif