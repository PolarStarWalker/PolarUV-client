#include "DisplayWidget.hpp"
#include "ui_DisplayWidget.h"

#include <QPainter>

#include <iostream>

void DisplayWidget::SwitchVideoStream() {
    std::string message;

    if (stream_.IsOnline()) {
        message = lib::processing::VideoStream::GetStopMessage();
        stream_.RestartClient();
    } else {
        message = lib::processing::VideoStream::GetStartMessage(resources_.ClientIp);
    }

    resources_.Network.SendRequest(message, lib::network::Request::TypeEnum::W, 2);
}

void DisplayWidget::SwitchVideoCapture() {

}

void DisplayWidget::TakeScreenshot() {

}

void DisplayWidget::SwitchSendingCommands() {

}

void DisplayWidget::initializeGL() {

}

void DisplayWidget::resizeGL(int w, int h) {

}

void DisplayWidget::paintGL() {

    const auto &sensors = resources_.Sensors;
    const auto &sensorsSettings = resources_.SensorsSettings;

    QImage currentFrame{};

    if (stream_.IsOnline()) {
        auto videoFrame = stream_.GetQImage();

        if (!videoFrame.isNull()) {
            videoFrame_ = std::move(videoFrame);
        }

        currentFrame = videoFrame_.scaled(this->width(), this->height());
    } else {
        currentFrame = placeholderImage_.scaled(this->width(), this->height());
    }

    drawer_.Begin(this)
            .SetRenderHint(QPainter::Antialiasing)
            .SetResolution(width(), height())
            .DrawImage(0, 0, currentFrame);

    if (sensorsSettings.IndicatorsEnabled) {
        drawer_.Draw(PaintYawIndicator, sensors.Rotation[SensorsStruct::Z])
                .Draw(PaintCentralIndicator, sensors.Rotation[SensorsStruct::X], sensors.Rotation[SensorsStruct::Y])
                .Draw(PaintDepthIndicator, sensors.Depth - sensorsSettings.DepthOffset, sensorsSettings.MaxDepth)
                .Draw(PaintTextInfo, sensors.MotionCalibration);
    }

    drawer_.DrawImage(width() / 2 - 400 - 60, 0, currentFrame, width() / 2 - 400 - 60, 0, 60, 30)
            .DrawImage(width() / 2 + 400, 0, currentFrame, width() / 2 + 400, 0, 60, 30)
            .End();
}