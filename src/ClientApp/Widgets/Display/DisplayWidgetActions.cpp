#include "DisplayWidget.hpp"

void DisplayWidget::SwitchVideoStream() {
    std::string message;

    if(stream_.IsOnline()){
        message = stream_.GetStopMessage();
    }else{
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