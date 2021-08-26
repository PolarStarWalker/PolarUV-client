#include <iphlpapi.h>
#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"
#include "../ExceptionHandler/ExceptionHandler.hpp"

void MainWindow::setupButtons() {
    this->connect(ui->VideoStreamButton, SIGNAL(clicked(bool)), SLOT(switchVideoStream()));
    this->connect(ui->ScreenshotButton, SIGNAL(clicked(bool)), SLOT(takeScreenshot()));
    this->connect(ui->VideoCaptureButton, SIGNAL(clicked(bool)), SLOT(switchVideoCapture()));
    this->connect(ui->CommandsProtocolButton, SIGNAL(clicked(bool)), SLOT(switchSendingCommands()));
    this->connect(ui->ReceiveSettingsButton, SIGNAL(clicked(bool)), SLOT(receiveRobotSettings()));
    this->connect(ui->SendSettingsButton, SIGNAL(clicked(bool)), SLOT(sendRobotSettings()));
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

void MainWindow::receiveRobotSettings() {

    RobotSettingsStruct robotSettingsStruct = RobotSettingsProtocol().Recv(ui->RobotIPEdit->text(), SETTINGS_PORT);

    /// Writing motors number
    const double *moveCoefficientArray = robotSettingsStruct.ThrusterCoefficientArray();
    int motorsNumber = robotSettingsStruct.ThrusterNumber();
    ui->MotorsNumberSpinBox->setValue(motorsNumber);

    /// Writing motor coefficients
    for (int i = 0; i < motorsNumber; i++) {
        for (int j = 0; j < 6; j++) {
            QString itemText = QString::number(moveCoefficientArray[i * 6 + j]);
            ui->MotorsTable->setItem(i, j, new QTableWidgetItem(itemText));
        }
    }

    /// Writing the number of degrees of freedom of the hand
    const double *handCoefficientArray = robotSettingsStruct.HandCoefficientArray();
    int handFreedom = robotSettingsStruct.HandFreedom();
    ui->HandFreedomSpinBox->setValue(handFreedom);

    /// Writing hand coefficients
    for (int j = 0; j < handFreedom; j++) {
        QString itemText = QString::number(handCoefficientArray[j]);
        ui->HandTable->setItem(0, j, new QTableWidgetItem(itemText));
    }

    /// Writing max motor speed
    ui->MaxSpeedEdit->setText(QString::number(robotSettingsStruct.MaxMotorsSpeed()));

    /// Writing motors protocol
    switch (robotSettingsStruct.MotorsProtocol()) {
        case 1:
            ui->MotorsProtocolComboBox->setCurrentIndex(0);
            break;
        case 2:
            ui->MotorsProtocolComboBox->setCurrentIndex(1);
            break;
        case 4:
            ui->MotorsProtocolComboBox->setCurrentIndex(2);
            break;
        case 8:
            ui->MotorsProtocolComboBox->setCurrentIndex(3);
            break;
    }

    QMessageBox::information(this, "Сообщение", "Настройки успешно получены");
}

void MainWindow::sendRobotSettings() {

    std::function<void(MainWindow*)> function = &MainWindow::RawSendClientSettings;

    ExceptionHandler(this, function, "Успех", "Настройки успешно отправлены");
}

void MainWindow::saveClientSettings() {
    ClientSettingsStruct settings;

    std::memcpy(settings.serverIP, ui->RobotIPEdit->text().begin(), sizeof(settings.serverIP));

    settings.leftShoulderActionID = (int8_t) ui->LeftShoulderComboBox->currentIndex();
    settings.rightShoulderActionID = (int8_t) ui->RightShoulderComboBox->currentIndex();
    settings.leftStickXActionID = (int8_t) ui->LeftStickXComboBox->currentIndex();
    settings.leftStickYActionID = (int8_t) ui->LeftStickYComboBox->currentIndex();
    settings.leftStickPressActionID = (int8_t) ui->LeftStickPressComboBox->currentIndex();
    settings.rightStickXActionID = (int8_t) ui->RightStickXComboBox->currentIndex();
    settings.rightStickYActionID = (int8_t) ui->RightStickYComboBox->currentIndex();
    settings.rightStickPressActionID = (int8_t) ui->RightStickPressComboBox->currentIndex();
    settings.dPadXActionID = (int8_t) ui->DPadXComboBox->currentIndex();
    settings.dPadYActionID = (int8_t) ui->DPadYComboBox->currentIndex();
    settings.triangleActionID = (int8_t) ui->TriangleComboBox->currentIndex();
    settings.crossActionID = (int8_t) ui->CrossComboBox->currentIndex();
    settings.rectangleActionID = (int8_t) ui->RectangleComboBox->currentIndex();
    settings.circleActionID = (int8_t) ui->CircleComboBox->currentIndex();
    settings.startActionID = (int8_t) ui->StartComboBox->currentIndex();
    settings.backActionID = (int8_t) ui->BackComboBox->currentIndex();

    settings.leftShoulderInverted = ui->LeftShoulderCheckBox->isChecked();
    settings.rightShoulderInverted = ui->RightShoulderCheckBox->isChecked();
    settings.leftStickXInverted = ui->LeftStickXCheckBox->isChecked();
    settings.leftStickYInverted = ui->LeftStickYCheckBox->isChecked();
    settings.rightStickXInverted = ui->RightStickXCheckBox->isChecked();
    settings.rightStickYInverted = ui->RightStickYCheckBox->isChecked();
    settings.dPadXInverted = ui->DPadXCheckBox->isChecked();
    settings.dPadYInverted = ui->DPadYCheckBox->isChecked();

    settings.Save();

    QMessageBox::information(this, "Сообщение", "Настройки успешно сохранены");
}

void MainWindow::loadClientSettings() {
    ClientSettingsStruct settings;
    settings.Load();

    ui->RobotIPEdit->setText(QString(settings.serverIP));

    ui->LeftShoulderComboBox->setCurrentIndex(settings.leftShoulderActionID);
    ui->RightShoulderComboBox->setCurrentIndex(settings.rightShoulderActionID);
    ui->LeftStickXComboBox->setCurrentIndex(settings.leftStickXActionID);
    ui->LeftStickYComboBox->setCurrentIndex(settings.leftStickYActionID);
    ui->LeftStickPressComboBox->setCurrentIndex(settings.leftStickPressActionID);
    ui->RightStickXComboBox->setCurrentIndex(settings.rightStickXActionID);
    ui->RightStickYComboBox->setCurrentIndex(settings.rightStickYActionID);
    ui->RightStickPressComboBox->setCurrentIndex(settings.rightStickPressActionID);
    ui->DPadXComboBox->setCurrentIndex(settings.dPadXActionID);
    ui->DPadYComboBox->setCurrentIndex(settings.dPadYActionID);
    ui->TriangleComboBox->setCurrentIndex(settings.triangleActionID);
    ui->CrossComboBox->setCurrentIndex(settings.crossActionID);
    ui->RectangleComboBox->setCurrentIndex(settings.rectangleActionID);
    ui->CircleComboBox->setCurrentIndex(settings.circleActionID);
    ui->StartComboBox->setCurrentIndex(settings.startActionID);
    ui->BackComboBox->setCurrentIndex(settings.backActionID);

    ui->LeftShoulderCheckBox->setChecked(settings.leftShoulderInverted);
    ui->RightShoulderCheckBox->setChecked(settings.rightShoulderInverted);
    ui->LeftStickXCheckBox->setChecked(settings.leftStickXInverted);
    ui->LeftStickYCheckBox->setChecked(settings.leftStickYInverted);
    ui->RightStickXCheckBox->setChecked(settings.rightStickXInverted);
    ui->RightStickYCheckBox->setChecked(settings.rightStickYInverted);
    ui->DPadXCheckBox->setChecked(settings.dPadXInverted);
    ui->DPadYCheckBox->setChecked(settings.dPadYInverted);

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