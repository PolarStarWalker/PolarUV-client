#ifndef CLIENT_WIDGETRESOURCES_HPP
#define CLIENT_WIDGETRESOURCES_HPP

#include <QImage>

#include <Network/Network.hpp>

#include <string>

struct WidgetResources {

    QImage TelemetryFrame = QImage(1920,1080,QImage::Format_ARGB32);
    QImage VideoFrame = QImage(1920,1080,QImage::Format_RGB888);
    lib::network::Network Network{};
    std::string ClientIp{};
    int GamepadId{};

};




#endif