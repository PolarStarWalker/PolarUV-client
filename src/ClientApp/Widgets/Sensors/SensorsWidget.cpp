#include "SensorsWidget.hpp"
#include <iostream>

#include <QWindow>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>

SensorsWidget::SensorsWidget(QObject *parent, WidgetResources &resources) :
        QObject(parent),
        resources_(resources),
        timer_(){

    connect(&timer_, SIGNAL(timeout()), this, SLOT(ReceiveTelemetry()));
    connect(&timer_, SIGNAL(timeout()), this, SLOT(PaintTelemetryFrame()));

    PaintTelemetryFrame();
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

    if (sensors) {
        sensors_ = *sensors;
        std::cout << sensors_.Rotation[SensorsStruct::X] << std::endl;
    }
}

void SensorsWidget::PaintTelemetryFrame() {
    resources_.telemetryFBO->bind();

    painter_.begin(&paintDevice_);
    painter_.setRenderHints(QPainter::Antialiasing);

    PaintYawIndicator(painter_,
                      paintDevice_.width(),
                      paintDevice_.height(),
                      sensors_.Rotation[SensorsStruct::Z]);

    PaintCentralIndicator(painter_,
                          paintDevice_.width(),
                          paintDevice_.height(),
                          sensors_.Rotation[SensorsStruct::X],
                          sensors_.Rotation[SensorsStruct::Y]);

    PaintDepthIndicator(painter_,
                        paintDevice_.width(),
                        paintDevice_.height(),
                        sensors_.Depth,
                        10);

    painter_.end();

    resources_.telemetryFBO->release();
}