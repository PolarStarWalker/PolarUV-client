#include "DisplayWidget.hpp"
#include "ui_DisplayWidget.h"


void DisplayWidget::UpdateBackgroundImage() {
    /// Если нужно вывести кадр видео
    if (stream_.IsOnline()) {
        auto img = stream_.GetQImage();
        if (!img.isNull()) {
            pixmap_.convertFromImage(img);
            pixmap_ = pixmap_.scaled(this->size(), Qt::IgnoreAspectRatio);
            palette_.setBrush(QPalette::Window, pixmap_);
            this->setAutoFillBackground(true);
            this->setPalette(palette_);
            isPlaceholder = false;
        }
    /// Если нужно вывести картинку
    } else if (!isPlaceholder) {
        pixmap_ = placeholderPixmap_.scaled(this->size(), Qt::IgnoreAspectRatio);
        palette_.setBrush(QPalette::Window, pixmap_);
        this->setAutoFillBackground(true);
        this->setPalette(palette_);
        isPlaceholder = true;
    }
    /// Если нужно поменять размер картинки
    else {
        QRect currentGeometry = geometry();
        if (geometry_ != currentGeometry) {
            geometry_ = currentGeometry;
            pixmap_ = placeholderPixmap_.scaled(this->size(), Qt::IgnoreAspectRatio);
            palette_.setBrush(QPalette::Window, pixmap_);
            this->setAutoFillBackground(true);
            this->setPalette(palette_);
        }
    }
}

void DisplayWidget::SwitchVideoStream() {
    std::string message;

    if (stream_.IsOnline()) {
        message = stream_.GetStopMessage();
        stream_.RestartClient();
    } else {
        message = stream_.GetStartMessage(resources_.ClientIp);
    }

    resources_.Network.SendRequest(message, lib::network::Request::TypeEnum::W, 2);
}

void DisplayWidget::SwitchVideoCapture() {
}

void DisplayWidget::TakeScreenshot() {

}

void DisplayWidget::SwitchSendingCommands() {
}