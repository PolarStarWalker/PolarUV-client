#include "SensorsWidget.hpp"
#include <iostream>

#include <QWindow>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLPaintDevice>
#include <QPainter>

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

QOpenGLFramebufferObjectFormat SensorsWidget::CreateFBOFormat() {

    //QSurfaceFormat format;
    //format.setMajorVersion(3);
    //format.setMinorVersion(3);

    QWindow window;
    window.setSurfaceType(QWindow::OpenGLSurface);
    //window.setFormat(QSurfaceFormat());
    window.create();

    QOpenGLContext context;
    //context.setFormat(QSurfaceFormat());
    if (!context.create())
        std::cout << "Cannot create the OpenGL context!" << std::endl;
    context.makeCurrent(&window);

    QOpenGLFramebufferObjectFormat fboFormat;
    fboFormat.setSamples(16);
    fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);

    return fboFormat;
}

void SensorsWidget::PaintTelemetryFrame() {
    resources_.telemetryFBO->bind();

    QOpenGLPaintDevice device(1920, 1080);

    QPainter painter;
    painter.begin(&device);
    painter.setRenderHints(QPainter::Antialiasing);

    PaintYawIndicator(painter,
                      device.width(),
                      device.height(),
                      sensors_.Rotation[SensorsStruct::Z]);

    PaintCentralIndicator(painter,
                          device.width(),
                          device.height(),
                          sensors_.Rotation[SensorsStruct::X],
                          sensors_.Rotation[SensorsStruct::Y]);

    PaintDepthIndicator(painter,
                        device.width(),
                        device.height(),
                        sensors_.Depth,
                        10);

    painter.end();

    resources_.telemetryFBO->release();
}