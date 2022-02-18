#ifndef CLIENT_SENSORSWIDGET_HPP
#define CLIENT_SENSORSWIDGET_HPP

#include "../WidgetResources.hpp"

#include <QWidget>
#include <QTimer>

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

class SensorsWidget final : public QWidget{

    constexpr static int FPS = 60;
    constexpr static auto TIMEOUT_ms = std::chrono::milliseconds( 1000 / FPS);

    Q_OBJECT

public:
    SensorsWidget(QWidget* parent, WidgetResources& resources);

public slots:
    void StartWidget();
    void StopWidget();

private slots:
    void ReceiveTelemetry();

public:
    inline SensorsStruct GetSensorsStruct(){
        std::shared_lock lock(sensorsMutex_);
        auto sensors = sensors_;
        return sensors;
    }
private:
    void SetSensorsStruct(const SensorsStruct& sensors);


private:
    std::shared_mutex sensorsMutex_;
    SensorsStruct sensors_;
    WidgetResources& resources_;
    QTimer timer_;
};

#endif