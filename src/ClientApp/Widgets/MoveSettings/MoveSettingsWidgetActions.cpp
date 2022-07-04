#include <ranges>
#include <Exceptions/Exceptions.hpp>
#include <QMessageBox>
#include "./MoveSettingsWidget.hpp"
#include "./MoveSettingsMessage.pb.h"
#include "./ui_MoveSettingsWidget.h"

void MoveSettingsWidget::SendSettings() {
    using namespace lib::network;

    std::string message = Serialize();

    Response response = resources_.Network.SendRequest(message, Request::TypeEnum::W, 0);

    StatusCodeCheck<Request::TypeEnum::W>(response.Header.Code);

    QMessageBox::about(nullptr, "Успех", "Настройки успешно отправлены");
}

void MoveSettingsWidget::ReceiveSettings() {
    using namespace lib::network;

    Response response = resources_.Network.SendRequest(std::string(), Request::TypeEnum::R, 0);

    StatusCodeCheck<Request::TypeEnum::R>(response.Header.Code, [&](){ Deserialize(response.Data);});
}

void MoveSettingsWidget::Deserialize(const std::string &data) noexcept {

    MoveSettingsMessage message;
    message.ParseFromArray(data.data(), data.size());

    /// Writing number of motor coefficients
    auto& thrusterCoefficient = message.thrusters_coefficient();
    ui->MotorsNumberSpinBox->setValue(thrusterCoefficient.size()/6);

    /// Writing motor coefficients
    for (int i = 0; i < thrusterCoefficient.size()/6; i++) {
        for (int j = 0; j < 6; j++) {
            QString itemText = QString::number(thrusterCoefficient[i * 6 + j]);
            ui->MotorsTable->setItem(i, j, new QTableWidgetItem(itemText));
        }
    }

    /// Writing the number of degrees of freedom of the hand
    auto& handCoefficient = message.hand_coefficient();
    ui->HandFreedomSpinBox->setValue(handCoefficient.size());

    /// Writing hand coefficients
    for (int j = 0; j < handCoefficient.size(); j++) {
        QString itemText = QString::number(handCoefficient[j]);
        ui->HandTable->setItem(0, j, new QTableWidgetItem(itemText));
    }

    /// Writing max motor speed
    ui->MaxSpeedEdit->setText(QString::number(message.maximum_motor_speed()));

    /// Writing motors protocol
    switch (message.motors_protocol()) {
        case MoveSettingsMessage::DSHOT150:
            ui->MotorsProtocolComboBox->setCurrentIndex(0);
            break;
        case MoveSettingsMessage::DSHOT300:
            ui->MotorsProtocolComboBox->setCurrentIndex(1);
            break;
        case MoveSettingsMessage::DSHOT600:
            ui->MotorsProtocolComboBox->setCurrentIndex(2);
            break;
        case MoveSettingsMessage::DSHOT1200:
            ui->MotorsProtocolComboBox->setCurrentIndex(3);
            break;
    }

}

std::string MoveSettingsWidget::Serialize() const noexcept {

    MoveSettingsMessage message;

    /// Reading max motor speed
    message.set_maximum_motor_speed((int16_t) ui->MaxSpeedEdit->text().toInt());

    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            bool isConverted;
            float value = ui->MotorsTable->item(i, j)->text().toFloat(&isConverted);

            if (!isConverted)
                throw lib::exceptions::InvalidOperationException(
                        "Матрица коэффициентов двигателей\n содержит некорректный символ");

            message.add_thrusters_coefficient(value);
        }
    }

    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        bool isConverted;

        float value = ui->HandTable->item(0, j)->text().toFloat(&isConverted);

        if (!isConverted )
            throw lib::exceptions::InvalidOperationException(
                    "Матрица коэффициентов манипулятора\n содержит некорректный символ");

        message.add_hand_coefficient(value);
    }

    /// Reading motors protocol
    switch (ui->MotorsProtocolComboBox->currentIndex()) {
        case 0:
            message.set_motors_protocol(MoveSettingsMessage::DSHOT150);
            break;
        case 1:
            message.set_motors_protocol(MoveSettingsMessage::DSHOT300);
            break;
        case 2:
            message.set_motors_protocol(MoveSettingsMessage::DSHOT600);
            break;
        case 3:
            message.set_motors_protocol(MoveSettingsMessage::DSHOT1200);
            break;
    }

    ///add pid
    auto X = message.mutable_pid()->Add();
    X->set_p(ui->XAxisPCoefficientEdit->text().toFloat());
    X->set_i(ui->XAxisICoefficientEdit->text().toFloat());
    X->set_d(ui->XAxisDCoefficientEdit->text().toFloat());

    auto Y = message.mutable_pid()->Add();
    Y->set_p(ui->YAxisPCoefficientEdit->text().toFloat());
    Y->set_i(ui->YAxisICoefficientEdit->text().toFloat());
    Y->set_d(ui->YAxisDCoefficientEdit->text().toFloat());

    auto Z = message.mutable_pid()->Add();
    Z->set_p(ui->ZAxisPCoefficientEdit->text().toFloat());
    Z->set_i(ui->ZAxisICoefficientEdit->text().toFloat());
    Z->set_d(ui->ZAxisDCoefficientEdit->text().toFloat());

    ///ToDo: depth PID interface
    auto Depth = message.mutable_pid()->Add();
    Depth->set_p(0);
    Depth->set_i(0);
    Depth->set_d(0);

    return message.SerializeAsString();
}

void MoveSettingsWidget::StartWidget() {
    ///ToDo: почему то если запускать .exe файл, то из-за этого всё ломается, я хз
//    ReceiveSettings();
}

void MoveSettingsWidget::StopWidget() {

}

