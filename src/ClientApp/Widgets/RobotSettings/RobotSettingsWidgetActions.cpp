#include <Exceptions/Exceptions.hpp>
#include "./RobotSettingsWidget.hpp"
#include "./RobotSettingsMessage.pb.h"
#include "./ui_RobotSettingsWidget.h"

void RobotSettingsWidget::SendSettings() const {
    using namespace lib::network;

    std::string message = Serialize();

    Packet packet(Packet::Type::W, message, 0);

    Response response = _transmitter.Send(packet);

    switch (response.Code) {
        case Response::Ok:
            throw Exception::InvalidOperationException("Неправильный код возврата");
        case Response::NoContent:
            return;
        case Response::BadRequest:
            throw Exception::InvalidOperationException("Возникла ошибка на сервере");
        case Response::ConnectionError:
            throw Exception::ConnectionException("Не удалось подключиться к роботу");
    }
}

void RobotSettingsWidget::ReceiveSettings() {
    using namespace lib::network;

    Packet packet(Packet::Type::R, std::string(), 0);

    Response response = _transmitter.Send(packet);

    switch(response.Code){
        case Response::Ok:
            Deserialize(response.Data);
            return;
        case Response::NoContent:
            throw Exception::InvalidOperationException("Нет данных");
        case Response::BadRequest:
            throw Exception::InvalidOperationException("Возникла ошибка на сервере");
        case Response::ConnectionError:
            throw Exception::ConnectionException("Не удалось подключиться к роботу");
    }
}

void RobotSettingsWidget::Deserialize(const std::string &data) noexcept {

    RobotSettingsMessage message;
    message.ParseFromString(data);

    /// Writing number of motor coefficients
    auto& thrusterCoefficient = message.thrusters_coefficient();
    ui->MotorsNumberSpinBox->setValue(thrusterCoefficient.size());

    /// Writing motor coefficients
    for (int i = 0; i < thrusterCoefficient.size(); i++) {
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
        case RobotSettingsMessage::DSHOT150:
            ui->MotorsProtocolComboBox->setCurrentIndex(0);
            break;
        case RobotSettingsMessage::DSHOT300:
            ui->MotorsProtocolComboBox->setCurrentIndex(1);
            break;
        case RobotSettingsMessage::DSHOT600:
            ui->MotorsProtocolComboBox->setCurrentIndex(2);
            break;
        case RobotSettingsMessage::DSHOT1200:
            ui->MotorsProtocolComboBox->setCurrentIndex(3);
            break;
    }

}

std::string RobotSettingsWidget::Serialize() const noexcept {

    RobotSettingsMessage message;

    /// Reading max motor speed
    message.set_maximum_motor_speed((int16_t) ui->MaxSpeedEdit->text().toInt());

    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            bool isConverted;
            double value = ui->MotorsTable->item(i, j)->text().toFloat(&isConverted);

            if (!isConverted)
                throw Exception::InvalidOperationException(
                        "Матрица коэффициентов двигателей\n содержит некорректный символ");

            message.add_thrusters_coefficient(value);
        }
    }

    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        bool isConverted;

        double value = ui->HandTable->item(0, j)->text().toFloat(&isConverted);

        if (!isConverted)
            throw Exception::InvalidOperationException(
                    "Матрица коэффициентов манипулятора\n содержит некорректный символ");

        message.add_hand_coefficient(value);
    }

    /// Reading motors protocol
    switch (ui->MotorsProtocolComboBox->currentIndex()) {
        case 0:
            message.set_motors_protocol(RobotSettingsMessage::DSHOT150);
            break;
        case 1:
            message.set_motors_protocol(RobotSettingsMessage::DSHOT300);
            break;
        case 2:
            message.set_motors_protocol(RobotSettingsMessage::DSHOT600);
            break;
        case 3:
            message.set_motors_protocol(RobotSettingsMessage::DSHOT1200);
            break;
    }

    return message.SerializeAsString();
}

