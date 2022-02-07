#ifndef CLIENT_WIDGETRESOURCES_HPP
#define CLIENT_WIDGETRESOURCES_HPP

#include <TcpSession/TcpSession.hpp>

#include <string>

struct WidgetResources {

    lib::network::Network Network{};
    std::string ClientIp{};
    int GamepadId{};

};




#endif