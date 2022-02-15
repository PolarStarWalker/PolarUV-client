#ifndef CLIENT_COMMANDSWIDGET_HPP
#define CLIENT_COMMANDSWIDGET_HPP
#include "../WidgetResources.hpp"

#include <QWidget>
#include <QTimer>

struct CommandsStruct {
    enum MoveDimensions : uint8_t {
        Fx = 0,
        Fy = 1,
        Fz = 2,
        Mx = 3,
        My = 4,
        Mz = 5
    };

    std::array<float, 6> Move{};
    std::array<float, 6> Hand{};
    std::array<float, 4> LowPWM{};
};

struct Telemetry {

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

class CommandsWidget final : public QWidget {
Q_OBJECT

public slots:
    void StartWidget();
    void StopWidget();

private slots:
    void SendCommands();

public:

    CommandsWidget(QWidget *parent, WidgetResources& resources);

private:
    Telemetry telemetry_;
    WidgetResources& resources_;
    QTimer timer_;
};


#endif
