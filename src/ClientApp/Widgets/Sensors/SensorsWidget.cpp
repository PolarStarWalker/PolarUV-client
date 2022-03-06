#include "SensorsWidget.hpp"
#include <iostream>

#include <QPainter>

SensorsWidget::SensorsWidget(QObject *parent, WidgetResources &resources) :
        QObject(parent),
        resources_(resources),
        timer_() {

    connect(&timer_, SIGNAL(timeout()), this, SLOT(ReceiveTelemetry()));
    connect(&timer_, SIGNAL(timeout()), this, SLOT(PaintTelemetryFrame()));

}

void SensorsWidget::SetSensorsStruct(const SensorsStruct &sensors) {
    std::unique_lock lock(sensorsMutex_);
    sensors_ = sensors;
}

void SensorsWidget::StartWidget() {
    timer_.start(TIMEOUT_ms);
}

void SensorsWidget::StopWidget() {
    timer_.stop();
}

void SensorsWidget::ReceiveTelemetry() {
    using RequestType = lib::network::Request::TypeEnum;
    auto response = resources_.Network.SendRequest("", RequestType::R, 1);

    auto sensors = response.DataAs<SensorsStruct>();

    if (sensors != nullptr) {
        sensors_ = *sensors;
        std::cout << sensors_.Rotation[SensorsStruct::X] << std::endl;
    }
}

void SensorsWidget::PaintTelemetryFrame() {
    std::cout << "Нарисовал кадр телеметрии!" << std::endl;
    QPainter painter(&resources_.TelemetryFrame);
    painter.setRenderHints(QPainter::Antialiasing);

    PaintYawIndicator(painter,
                      resources_.TelemetryFrame.width(),
                      resources_.TelemetryFrame.height(),
                      sensors_.Rotation[SensorsStruct::Z]);

    PaintCentralIndicator(painter,
                          resources_.TelemetryFrame.width(),
                          resources_.TelemetryFrame.height(),
                          sensors_.Rotation[SensorsStruct::X],
                          sensors_.Rotation[SensorsStruct::Y]);

    PaintDepthIndicator(painter,
                        resources_.TelemetryFrame.width(),
                        resources_.TelemetryFrame.height(),
                        sensors_.Depth,
                        10);

}