#include <Exceptions/Exceptions.hpp>

#include "RobotSettings/RobotSettingsWidget.hpp"

#include "RobotSettingsMessage.pb.h"

using namespace lib;



RobotSettingsWidget::RobotSettingsWidget() : _transmitter(network::TcpSession::GetInstance()) {

}

std::string RobotSettingsWidget::Serialize() const {

    RobotSettingsMessage message;

    ///Copy from widget to message;

//    example std::vector<float> is field in widget
//    for (float coefficient: std::vector<float>(0)) {
//        message.add_thrusters_coefficient(coefficient);
//    }

    return message.SerializeAsString();
}

void RobotSettingsWidget::Deserialize(const std::string &data) {

    RobotSettingsMessage message;
    message.ParseFromString(data);


    ///
}

void RobotSettingsWidget::SendSettings() const {
    using namespace network;

    std::string message = Serialize();

    network::Packet packet(Packet::Type::W, message, 0);

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
    using namespace network;

    Packet packet(Packet::Type::W, "", 0);

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

