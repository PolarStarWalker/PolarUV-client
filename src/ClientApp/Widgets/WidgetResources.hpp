#ifndef CLIENT_WIDGETRESOURCES_HPP
#define CLIENT_WIDGETRESOURCES_HPP

#define WIN32_LEAN_AND_MEAN

#include <QOpenGLFramebufferObject>
#include <QImage>

#include <Network/Network.hpp>

#include <string>

struct SensorsStruct {

    enum Position {
        X = 0,
        Y = 1,
        Z = 2,
        W = 3
    };

    std::array<float, 4> Rotation{};

    std::array<float, 3> Acceleration{};

    float Depth = 0.0f;

    float Pressure = 0.0f;

    float BatteryVoltage = 0.0f;

    std::array<int8_t, 4> MotionCalibration {};

    bool Euler = true;
};

struct WidgetResources {

    SensorsStruct Sensors{};

    lib::network::Network Network{};
    std::string ClientIp{};
    int GamepadId{};

};




#endif