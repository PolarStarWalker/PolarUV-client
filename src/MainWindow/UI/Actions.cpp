#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"
#include "../ExceptionHandler/ExceptionHandler.hpp"

void MainWindow::RawSendClientSettings() {
    BaseRobotSettingsStruct baseRobotSettingsStruct{};
    baseRobotSettingsStruct.ThrusterNumber = ui->MotorsTable->rowCount();
    baseRobotSettingsStruct.HandFreedom = ui->HandTable->columnCount();

    RobotSettingsStruct robotSettingsStruct(baseRobotSettingsStruct);

    /// Reading motor coefficients
    double *moveCoefficientArray = robotSettingsStruct.ThrusterCoefficientArray();
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            moveCoefficientArray[i * 6 + j] = ui->MotorsTable->item(i, j)->text().toDouble();
        }
    }

    /// Reading hand coefficients
    double *handCoefficientArray = robotSettingsStruct.HandCoefficientArray();
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        handCoefficientArray[j] = ui->HandTable->item(0, j)->text().toDouble();
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

void MainWindow::RawReceiveClientSettings() {

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
}
