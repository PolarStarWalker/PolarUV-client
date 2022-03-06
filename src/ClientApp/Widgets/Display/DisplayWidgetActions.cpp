#include "DisplayWidget.hpp"
#include "ui_DisplayWidget.h"

#include <QPainter>

#include <iostream>


void DisplayWidget::UpdateBackgroundImage() {
    /// Если нужно вывести кадр видео
    if (stream_.IsOnline()) {
        auto image = stream_.GetQImage();
        if (!image.isNull()) {
            /// Рисуем кадр телеметрии поверх кадра видео
            QPainter painter(&image);
            painter.drawImage(0,0,resources_.TelemetryFrame);

            /// Масштабируем кадр под размер окна
            pixmap_.convertFromImage(image);
            pixmap_ = pixmap_.scaled(this->size(), Qt::IgnoreAspectRatio);

            /// Выводим кадр
            palette_.setBrush(QPalette::Window, pixmap_);
            this->setAutoFillBackground(true);
            this->setPalette(palette_);
            isPlaceholder = false;
        }
    /// Если нужно вывести картинку
    } else /*if (!isPlaceholder)*/ {
        /// Рисуем кадр телеметрии поверх картинки
        QImage image(placeholderImage_);
        QPainter painter(&image);
        painter.drawImage(0,0,resources_.TelemetryFrame);

        /// Масштабируем кадр под размер окна
        pixmap_.convertFromImage(image);
        pixmap_ = pixmap_.scaled(this->size(), Qt::IgnoreAspectRatio);

        /// Выводим кадр
        palette_.setBrush(QPalette::Window, pixmap_);
        this->setAutoFillBackground(true);
        this->setPalette(palette_);
        isPlaceholder = true;
    }
    /// Если нужно поменять размер картинки ToDo: разобраться
//    else {
//        std::cout << 3 << std::endl;
//        QRect currentGeometry = geometry();
//        if (geometry_ != currentGeometry) {
//            geometry_ = currentGeometry;
//
//            pixmap_.convertFromImage(placeholderImage_);
//            pixmap_ = pixmap_.scaled(this->size(), Qt::IgnoreAspectRatio);
//
//            palette_.setBrush(QPalette::Window, pixmap_);
//            this->setAutoFillBackground(true);
//            this->setPalette(palette_);
//        }
//    }
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