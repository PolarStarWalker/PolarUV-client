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

    QImage image;

    if (stream_.IsOnline()) {
        auto videoFrame = stream_.GetQImage();
        if (!videoFrame.isNull()) {
            image = videoFrame;
        }
    } else {
        image = QImage(placeholderImage_);
    }

    image = image.scaled(this->width(), this->height());

    painter_.begin(this);

    painter_.setRenderHint(QPainter::Antialiasing);

    painter_.drawImage(0, 0, image);

    PaintYawIndicator(painter_, this->width(), this->height(),
                      resources_.Sensors.Rotation[SensorsStruct::Z]);

    PaintCentralIndicator(painter_, this->width(), this->height(),
                          resources_.Sensors.Rotation[SensorsStruct::X],
                          resources_.Sensors.Rotation[SensorsStruct::Y]);

    PaintDepthIndicator(painter_, this->width(), this->height(),
                        resources_.Sensors.Depth, 10);

    painter_.drawImage(this->width() / 2 - 400 - 60, 0, image,
                       this->width() / 2 - 400 - 60, 0, 60, 30);

    painter_.drawImage(this->width() / 2 + 400, 0, image,
                       this->width() / 2 + 400, 0, 60, 30);

    painter_.end();

}