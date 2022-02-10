#include "DisplayWidget.hpp"
#include "ui_DisplayWidget.h"


void DisplayWidget::UpdateBackgroundImage() {
    if (stream_.IsOnline()) {
        pixmap_.convertFromImage(stream_.GetQImage());
    } else {
        pixmap_ = placeholderPixmap_.scaled(this->size(), Qt::IgnoreAspectRatio);
    }
    palette_.setBrush(QPalette::Window, pixmap_);
    this->setAutoFillBackground(true);
    this->setPalette(palette_);
}

void DisplayWidget::SwitchVideoStream() {
    std::string message;

    if (stream_.IsOnline()) {
        message = stream_.GetStopMessage();
    } else {
        message = stream_.GetStartMessage(ClientIP);
    }

    ///ToDo: отправка данных
}

void DisplayWidget::SwitchVideoCapture() {
}

void DisplayWidget::TakeScreenshot() {

}

void DisplayWidget::SwitchSendingCommands() {
    if (!commandsProtocol_->IsStreamOnline()) {
        commandsProtocol_->Connect(RobotIP, COMMANDS_PORT);
        return;
    }
    commandsProtocol_->Stop();
}