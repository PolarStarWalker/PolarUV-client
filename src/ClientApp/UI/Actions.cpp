#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"
#include "Exceptions/Exceptions.hpp"


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
    using namespace data_structs;

    data_structs::BaseRobotSettingsDto baseRobotSettingsStruct{};
    baseRobotSettingsStruct.ThrusterNumber = ui->MotorsTable->rowCount();
    baseRobotSettingsStruct.HandFreedom = ui->HandTable->columnCount();

    data_structs::OldRobotSettingsDto robotSettingsStruct(baseRobotSettingsStruct);

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

    data_structs::OldRobotSettingsDto robotSettingsStruct = RobotSettingsProtocol().Recv(ui->RobotIPEdit->text(), SETTINGS_PORT);

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

    data_structs::ClientSettingsDto settings;

    std::string serverIp = ui->RobotIPEdit->text().toStdString();
    std::memcpy(settings.ServerIP, serverIp.c_str(), serverIp.size());

    settings.LeftShoulderAction = ui->LeftShoulderComboBox->currentIndex();
    settings.RightShoulderAction = ui->RightShoulderComboBox->currentIndex();

    settings.LeftStickXAction = ui->LeftStickXComboBox->currentIndex();
    settings.LeftStickYAction = ui->LeftStickYComboBox->currentIndex();

    settings.RightStickXAction = ui->RightStickXComboBox->currentIndex();
    settings.RightStickYAction = ui->RightStickYComboBox->currentIndex();

    settings.dPadXAction = ui->DPadXComboBox->currentIndex();
    settings.dPadYAction = ui->DPadYComboBox->currentIndex();

    settings.LeftStickPressAction = ui->LeftStickPressComboBox->currentIndex();
    settings.RightStickPressAction = ui->RightStickPressComboBox->currentIndex();

    settings.TriangleAction = ui->TriangleComboBox->currentIndex();
    settings.CrossAction = ui->CrossComboBox->currentIndex();
    settings.SquareAction = ui->RectangleComboBox->currentIndex();
    settings.CircleAction = ui->CircleComboBox->currentIndex();

    settings.StartAction = ui->StartComboBox->currentIndex();
    settings.BackAction = ui->BackComboBox->currentIndex();

    settings.LeftShoulderInverted = ui->LeftShoulderCheckBox->isChecked();
    settings.RightShoulderInverted = ui->RightShoulderCheckBox->isChecked();
    settings.LeftStickXInverted = ui->LeftStickXCheckBox->isChecked();
    settings.LeftStickYInverted = ui->LeftStickYCheckBox->isChecked();
    settings.RightStickXInverted = ui->RightStickXCheckBox->isChecked();
    settings.RightStickYInverted = ui->RightStickYCheckBox->isChecked();
    settings.dPadXInverted = ui->DPadXCheckBox->isChecked();
    settings.dPadYInverted = ui->DPadYCheckBox->isChecked();

    settings.Save();
}

void MainWindow::RawLoadClientSettings() {

    using namespace data_structs;

    ClientSettingsDto settings = ClientSettingsDto::Load();

    ui->RobotIPEdit->setText(QString(settings.ServerIP));

    ui->LeftShoulderComboBox->setCurrentIndex(settings.LeftShoulderAction);
    ui->RightShoulderComboBox->setCurrentIndex(settings.RightShoulderAction);
    ui->LeftStickXComboBox->setCurrentIndex(settings.LeftStickXAction);
    ui->LeftStickYComboBox->setCurrentIndex(settings.LeftStickYAction);
    ui->LeftStickPressComboBox->setCurrentIndex(settings.LeftStickPressAction);
    ui->RightStickXComboBox->setCurrentIndex(settings.RightStickXAction);
    ui->RightStickYComboBox->setCurrentIndex(settings.RightStickYAction);
    ui->RightStickPressComboBox->setCurrentIndex(settings.RightStickPressAction);
    ui->DPadXComboBox->setCurrentIndex(settings.dPadXAction);
    ui->DPadYComboBox->setCurrentIndex(settings.dPadYAction);
    ui->TriangleComboBox->setCurrentIndex(settings.TriangleAction);
    ui->CrossComboBox->setCurrentIndex(settings.CrossAction);
    ui->RectangleComboBox->setCurrentIndex(settings.SquareAction);
    ui->CircleComboBox->setCurrentIndex(settings.CircleAction);
    ui->StartComboBox->setCurrentIndex(settings.StartAction);
    ui->BackComboBox->setCurrentIndex(settings.BackAction);

    ui->LeftShoulderCheckBox->setChecked(settings.LeftShoulderInverted);
    ui->RightShoulderCheckBox->setChecked(settings.RightShoulderInverted);
    ui->LeftStickXCheckBox->setChecked(settings.LeftStickXInverted);
    ui->LeftStickYCheckBox->setChecked(settings.LeftStickYInverted);
    ui->RightStickXCheckBox->setChecked(settings.RightStickXInverted);
    ui->RightStickYCheckBox->setChecked(settings.RightStickYInverted);
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

        ips.emplace_back(std::string(adapterInfo->IpAddressList.IpAddress.String));
        adapterInfo = adapterInfo->Next;
    }

    delete[] deleteAdapter;
    return ips;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::Resize) {
        MainWindow::resizeEvent((QResizeEvent*)event);
    }
    if (event->type() == QEvent::Show ||
        event->type() == QEvent::Resize ||
        event->type() == QEvent::WindowStateChange) {

        this->MoveWidgets();

        emit SizeChanged(ui->TabWidget->currentWidget()->size());
    }
    return false;
}