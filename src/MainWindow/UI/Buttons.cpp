#include <iphlpapi.h>
#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"
#include "../ExceptionHandler/ExceptionHandler.hpp"

void MainWindow::setupButtons() {
    this->connect(ui->VideoStreamButton, SIGNAL(clicked(bool)), SLOT(switchVideoStream()));
    this->connect(ui->ScreenshotButton, SIGNAL(clicked(bool)), SLOT(takeScreenshot()));
    this->connect(ui->VideoCaptureButton, SIGNAL(clicked(bool)), SLOT(switchVideoCapture()));
    this->connect(ui->CommandsProtocolButton, SIGNAL(clicked(bool)), SLOT(switchSendingCommands()));
    this->connect(ui->ReceiveSettingsButton, SIGNAL(clicked(bool)), SLOT(ReceiveRobotSettings()));
    this->connect(ui->SendSettingsButton, SIGNAL(clicked(bool)), SLOT(SendRobotSettings()));
    this->connect(ui->SaveClientSettingsButton, SIGNAL(clicked(bool)), SLOT(saveClientSettings()));
    this->connect(ui->LoadClientSettingsButton, SIGNAL(clicked(bool)), SLOT(loadClientSettings()));
    this->connect(ui->RefreshGamepadsButton, SIGNAL(clicked(bool)), SLOT(refreshGamepads()));
    this->connect(ui->RefreshClientIPsButton, SIGNAL(clicked(bool)), SLOT(refreshClientIps()));
    this->connect(ui->FullScreenButton, SIGNAL(clicked(bool)), SLOT(switchFullScreen()));
    this->connect(ui->ShowTabBarButton, SIGNAL(clicked(bool)), SLOT(showTabBar()));
    this->connect(ui->HideTabBarButton, SIGNAL(clicked(bool)), SLOT(hideTabBar()));
}

void MainWindow::switchVideoStream() {
    if (!_videoStream->IsStreamOnline()) {
        QString clientAddress = ui->ClientIPComboBox->itemText(ui->ClientIPComboBox->currentIndex());
        QString robotAddress = ui->RobotIPEdit->text();
        _videoStream->StartAsync(robotAddress, clientAddress);
    } else {
        _videoStream->Stop(ui->RobotIPEdit->text());
    }
}

void MainWindow::takeScreenshot() {
    _videoStream->MakeScreenShot();
}

void MainWindow::switchVideoCapture() {
    _videoStream->IsVideoWriterOnline() ?
    _videoStream->StopVideoWrite() :
    _videoStream->StartVideoWrite();
}

void MainWindow::switchSendingCommands() {
    _commandsProtocol->IsStreamOnline() ?
    _commandsProtocol->Stop() :
    _commandsProtocol->StartAsync(ui->RobotIPEdit->text(), COMMANDS_PORT);
}

void MainWindow::ReceiveRobotSettings() {
    std::function<void(MainWindow*)> function = &MainWindow::RawReceiveRobotSettings;
    ExceptionHandler(this, function, "Успех", "Настройки успешно приняты");
}

void MainWindow::SendRobotSettings() {

    std::function<void(MainWindow*)> function = &MainWindow::RawSendRobotSettings;

    ExceptionHandler(this, function, "Успех", "Настройки успешно отправлены");
}

void MainWindow::saveClientSettings() {

    RawSaveClientSettings();

    QMessageBox::information(this, "Сообщение", "Настройки успешно сохранены");
}

void MainWindow::loadClientSettings() {

    RawLoadClientSettings();

    //QMessageBox::information(this, "Сообщение", "Настройки успешно восстановлены");
}

void MainWindow::refreshGamepads() {
    std::list<int> gamepads = Control::GetGamepadsIds();
    ui->GamepadComboBox->clear();
    for (int id : gamepads) {
        ui->GamepadComboBox->addItem(QString::number(id));
    }

    std::list<std::string> ips = GetClientIps();

    // The path to get the selected ID:
    // ui->GamepadComboBox->itemText(ui->GamepadComboBox->currentIndex()).toInt()
}

void MainWindow::refreshClientIps() {
    std::list<std::string> addresses = GetClientIps();
    ui->ClientIPComboBox->clear();
    for (std::string address : addresses) {
        ui->ClientIPComboBox->addItem(QString::fromStdString(address));
    }

    std::list<std::string> ips = GetClientIps();

    // The path to get the selected ID:
    //QString ip = ui->ClientIPComboBox->itemText(ui->ClientIPComboBox->currentIndex());

}

void MainWindow::switchFullScreen() {
    this->windowState() == Qt::WindowFullScreen ?
    this->setWindowState(Qt::WindowNoState) :
    this->setWindowState(Qt::WindowFullScreen);
}

void MainWindow::showTabBar() {
    /// Showing the TabBar
    ui->TabWidget->tabBar()->show();

    /// Showing all the buttons on the TabBar
    ui->FullScreenButton->show();
    ui->HideTabBarButton->show();
    ui->CommandsProtocolButton->show();

    /// Hiding ShowTabBar button
    ui->ShowTabBarButton->hide();
}

void MainWindow::hideTabBar() {
    /// Hiding the TabBar
    ui->TabWidget->tabBar()->hide();

    /// Hiding all the buttons on the TabBar
    ui->FullScreenButton->hide();
    ui->HideTabBarButton->hide();
    ui->CommandsProtocolButton->hide();

    /// Showing ShowTabBar button
    ui->ShowTabBarButton->show();
}

std::list<std::string> GetClientIps() {
    std::list<std::string> ips;
    PIP_ADAPTER_INFO adapterInfo = nullptr;
    ULONG ulOutBufLen = 0;

    DWORD result = GetAdaptersInfo(nullptr, &ulOutBufLen);

    if (result == ERROR_BUFFER_OVERFLOW) {
        HeapFree(GetProcessHeap(), 0, adapterInfo);
        adapterInfo = new IP_ADAPTER_INFO[ulOutBufLen / sizeof(IP_ADAPTER_INFO)];
        result = GetAdaptersInfo(adapterInfo, &ulOutBufLen);
    }

    if (result != ERROR_SUCCESS) {

        HeapFree(GetProcessHeap(), 0, adapterInfo);

        return ips;
    }

    PIP_ADAPTER_INFO deleteAdapter = adapterInfo;

    std::string nullIp = "0.0.0.0";
    for (size_t i = 0; i < ulOutBufLen / sizeof(IP_ADAPTER_INFO); ++i) {

        bool isEqual = !std::strcmp(nullIp.c_str(), adapterInfo->IpAddressList.IpAddress.String);

        if (isEqual) {
            adapterInfo = adapterInfo->Next;
            continue;
        }

        ips.push_back(std::string(adapterInfo->IpAddressList.IpAddress.String));
        adapterInfo = adapterInfo->Next;
    }

    delete[] deleteAdapter;
    return ips;
}