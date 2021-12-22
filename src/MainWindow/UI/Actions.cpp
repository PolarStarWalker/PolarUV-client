#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"
#include "../ExceptionHandler/ExceptionHandler.hpp"
#include "../Exceptions/Exceptions.hpp"


void MainWindow::RawSwitchVideoStream() {
    if (ui->RobotIPEdit->text() == "..." ||
        ui->ClientIPComboBox->itemText(ui->ClientIPComboBox->currentIndex()) == "") {

        throw Exception::InvalidOperationException("Невозможно начать трансляцию:\n"
                                                   "не указан IP-адрес ТНПА или клиента\n"
                                                   "(Настройки -  ТНПА - Подключение)");
    }

    if (!_videoStream->IsStreamOnline()) {
        QString clientAddress = ui->ClientIPComboBox->itemText(ui->ClientIPComboBox->currentIndex());
        QString robotAddress = ui->RobotIPEdit->text();
        _videoStream->StartAsync(robotAddress, clientAddress);
    } else {
        _videoStream->Stop(ui->RobotIPEdit->text());
    }
}

void MainWindow::RawSwitchVideoCapture() {
    if (!_videoStream->IsStreamOnline()) {
        throw Exception::InvalidOperationException("Невозможно записать видео:\n"
                                                   "трансляция не включена");
    }

    if (_videoStream->IsVideoWriterOnline()) {
        _videoStream->StopVideoWrite();
        ui->VideoCaptureButton->setIcon(QIcon("Icons/WhiteVideoIcon.png"));
    } else {
        _videoStream->StartVideoWrite();
        ui->VideoCaptureButton->setIcon(QIcon("Icons/GreenVideoIcon.png"));
    }
}

void MainWindow::RawTakeScreenshot() {
    if (!_videoStream->IsStreamOnline()) {
        throw Exception::InvalidOperationException("Невозможно сделать снимок:\n"
                                                   "трансляция не включена");
    }

    _videoStream->TakeScreenshot();
}

void MainWindow::RawSwitchSendingCommands() {

    if (ui->RobotIPEdit->text() == "...")
        throw Exception::InvalidOperationException("Невозможно начать отправку команд:\n"
                                                   "не указан IP-адрес ТНПА\n"
                                                   "(Настройки клиента - Подключение)");

    if (!_commandsProtocol->IsStreamOnline()) {
        _commandsProtocol->Connect(ui->RobotIPEdit->text(), COMMANDS_PORT);
        return;
    }

    _commandsProtocol->Stop();
}

void MainWindow::RawSendRobotSettings() {
    BaseRobotSettingsStruct baseRobotSettingsStruct{};
    baseRobotSettingsStruct.ThrusterNumber = ui->MotorsTable->rowCount();
    baseRobotSettingsStruct.HandFreedom = ui->HandTable->columnCount();

    RobotSettingsStruct robotSettingsStruct(baseRobotSettingsStruct);

    /// Reading motor coefficients
    float *moveCoefficientArray = robotSettingsStruct.ThrusterCoefficientArray();
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            bool isConverted;
            double value = ui->MotorsTable->item(i, j)->text().toFloat(&isConverted);
            if (isConverted) {
                moveCoefficientArray[i * 6 + j] = value;
            } else {
                throw Exception::InvalidOperationException("Матрица коэффициентов двигателей\n"
                                                           "содержит некорректный символ");
            }
        }
    }

    /// Reading hand coefficients
    float *handCoefficientArray = robotSettingsStruct.HandCoefficientArray();
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        bool isConverted;
        double value = ui->HandTable->item(0, j)->text().toFloat(&isConverted);
        if (isConverted) {
            handCoefficientArray[j] = value;
        } else {
            throw Exception::InvalidOperationException("Матрица коэффициентов манипулятора\n"
                                                       "содержит некорректный символ");
        }
    }

    /// Reading max motor speed
    robotSettingsStruct.MaxMotorsSpeed() = (int16_t) ui->MaxSpeedEdit->text().toInt();

    /// Reading motors protocol
    switch (ui->MotorsProtocolComboBox->currentIndex()) {
        case 0:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot150;
            break;
        case 1:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot300;
            break;
        case 2:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot600;
            break;
        case 3:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot1200;
            break;
    }

#if DEBUG
    std::cout << robotSettingsStruct;
#endif

    /// Sending settings to robot
    RobotSettingsProtocol().Send(ui->RobotIPEdit->text(), SETTINGS_PORT, std::move(robotSettingsStruct));
}

void MainWindow::RawReceiveRobotSettings() {

    RobotSettingsStruct robotSettingsStruct = RobotSettingsProtocol().Recv(ui->RobotIPEdit->text(), SETTINGS_PORT);

    /// Writing motors number
    const float *moveCoefficientArray = robotSettingsStruct.ThrusterCoefficientArray();
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
    const float *handCoefficientArray = robotSettingsStruct.HandCoefficientArray();
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
}

void MainWindow::RawSaveClientSettings() {
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
}

void MainWindow::RawLoadClientSettings() {
    ClientSettingsStruct settings;

    if (!settings.Load())
        throw Exception::InvalidOperationException("Файл настроек не существует");

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
