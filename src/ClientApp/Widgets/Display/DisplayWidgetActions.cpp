#include "DisplayWidget.hpp"
#include "ui_DisplayWidget.h"

#include <QPainter>
#include <QOpenGLPaintDevice>

#include <iostream>


void DisplayWidget::UpdateBackgroundImage() {

    /// Выбираем задний фон в зависимости от статуса стрима
    QImage backgroundImage;
    if (stream_.IsOnline()) {
        auto videoFrame = stream_.GetQImage();
        if (!videoFrame.isNull()) {
            backgroundImage = QImage(videoFrame);
        }
    } else {
        backgroundImage = QImage(placeholderImage_);
    }

    resources_.displayFBO->bind();

    painter_.begin(&paintDevice_);
    painter_.setRenderHints(QPainter::Antialiasing);
    painter_.drawImage(0, 0, backgroundImage);                      /// Рисуем задний фон
    painter_.drawImage(0, 0, resources_.telemetryFBO->toImage());   /// Рисуем телеметрию
    painter_.end();

    resources_.displayFBO->release();

    /// Масштабируем кадр под размер окна
    pixmap_.convertFromImage(resources_.displayFBO->toImage());
    pixmap_ = pixmap_.scaled(this->size(), Qt::IgnoreAspectRatio);

    /// Выводим кадр
    palette_.setBrush(QPalette::Window, pixmap_);
    this->setAutoFillBackground(true);
    this->setPalette(palette_);
}

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