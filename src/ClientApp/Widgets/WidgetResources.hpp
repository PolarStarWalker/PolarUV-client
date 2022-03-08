#ifndef CLIENT_WIDGETRESOURCES_HPP
#define CLIENT_WIDGETRESOURCES_HPP

#define WIN32_LEAN_AND_MEAN

#include <QOpenGLFramebufferObject>
#include <QImage>

#include <Network/Network.hpp>

#include <string>

struct WidgetResources {

    QOpenGLFramebufferObject* telemetryFBO = nullptr;
    QOpenGLFramebufferObject* displayFBO = nullptr;

    lib::network::Network Network{};
    std::string ClientIp{};
    int GamepadId{};

};




#endif