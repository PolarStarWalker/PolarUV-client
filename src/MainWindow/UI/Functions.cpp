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

