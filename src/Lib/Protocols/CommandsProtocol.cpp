#include "./CommandsProtocol/CommandsProtocol.hpp"

#include <iostream>

CommandsProtocol::CommandsProtocol(int gamepadId, QObject *parent)
        : QObject(parent),
          _gamepad(gamepadId) {
    this->_isOnline = false;
    this->_isThreadActive = false;
    this->_errorStatus = CommandsProtocol::ErrorType::Ok;

    connect(&this->_timer, SIGNAL(timeout()), this, SLOT(SendCommand()));

    _timer.start(1);
}

CommandsProtocol::~CommandsProtocol() {
    this->_socket.Disconnect();
    this->SetOnlineStatus(false);
}

void CommandsProtocol::SetGamepadId(size_t id) {
    this->_gamepad.UpdateGamepadId(id);
}

size_t CommandsProtocol::GetGamepadId() const {
    return this->_gamepad.GetGamepadId();
}

void CommandsProtocol::Stop() {
    this->_socket.Disconnect();
    this->SetErrorStatus(CommandsProtocol::ErrorType::ConnectionLost);
    this->SetOnlineStatus(false);
}


bool CommandsProtocol::Connect(const QString &address, uint16_t port) {

    if (_socket.ConnectToServer(address, port)) {
        SetOnlineStatus(true);
        return true;
    }

    SetOnlineStatus(false);
    return false;
}

void CommandsProtocol::SendCommand() {

    TelemetryStruct telemetry{};

    if (!_socket.IsOnline()) {
        this->SetTelemetryStruct(telemetry);
        return;
    }

    lib::CommandsStruct commands = this->_gamepad.GetCommandsStruct();
    _socket.Send((char *) (&commands), lib::CommandsStructLen);

    _socket.Recv((char *) &telemetry, TelemetryStructLen);

    this->SetTelemetryStruct(telemetry);
}




