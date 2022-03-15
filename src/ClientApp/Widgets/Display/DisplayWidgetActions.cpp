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

    if (stream_.IsOnline()) {
        auto videoFrame = stream_.GetQImage();
        if (!videoFrame.isNull()) {
            frame_ = videoFrame;
        }
    } else {
        frame_ = QImage(placeholderImage_);
    }

    frame_ = frame_.scaled(this->width(), this->height());

    painter_.begin(this);

    painter_.setRenderHint(QPainter::Antialiasing);

    painter_.drawImage(0, 0, frame_);

    PaintYawIndicator(painter_, this->width(), this->height(),
                      resources_.Sensors.Rotation[SensorsStruct::Z]);

    PaintCentralIndicator(painter_, this->width(), this->height(),
                          resources_.Sensors.Rotation[SensorsStruct::X],
                          resources_.Sensors.Rotation[SensorsStruct::Y]);

    PaintDepthIndicator(painter_, this->width(), this->height(),
                        resources_.Sensors.Depth, 10);

    painter_.drawImage(this->width() / 2 - 400 - 60, 0, frame_,
                       this->width() / 2 - 400 - 60, 0, 60, 30);

    painter_.drawImage(this->width() / 2 + 400, 0, frame_,
                       this->width() / 2 + 400, 0, 60, 30);

    painter_.end();

}