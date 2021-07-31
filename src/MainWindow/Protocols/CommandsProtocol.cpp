#include "CommandsProtocol/CommandsProtocol.hpp"
#include "../../DataStruct.hpp"

#include <iostream>

CommandsProtocol::CommandsProtocol(size_t gamepadId)
        : _gamepad(gamepadId) {
    this->_isOnline = false;
    this->_errorStatus = CommandsProtocol::ErrorType::Ok;
}

CommandsProtocol::~CommandsProtocol() {
    ///ToDo: motov.s - когда-нибудь придумай что-нибудь получше этого безобразия
    while (this->IsThreadActive())
        std::this_thread::sleep_for(std::chrono::microseconds(1));
}

bool CommandsProtocol::IsOnline() const {
    std::shared_lock<std::shared_mutex> guard(this->_statusStatusMutex);
    return this->_isOnline;
}

bool CommandsProtocol::GetError() const {
    std::shared_lock<std::shared_mutex> guard(this->_errorStatusMutex);
    return this->_errorStatus;
}

bool CommandsProtocol::IsThreadActive() const {
    std::shared_lock<std::shared_mutex> threadStatusGuard(this->_threadStatusMutex);
    return this->_isThreadActive;
}

void CommandsProtocol::Start(const QString &address, uint16_t port) {

    bool isConnected = this->_socket.ConnectToServer(address, port);

    if (!isConnected) {
        this->SetErrorStatus(CommandsProtocol::ErrorType::CantConnectToServer);
        return;
    }

    std::chrono::high_resolution_clock timer;

    this->SetOnlineStatus(true);

    for (size_t i = 0; _socket.IsOnline(); i++) {
        auto currentTime = timer.now();

        std::shared_ptr<CommandsStruct> commands = this->_gamepad.GetCommandsStruct();
        QByteArray commandsStruct((char *) commands.get(), CommandsStructLen);
        _socket.SendCommand(commandsStruct);

        size_t deltaTime = std::chrono::duration<double, std::micro>(currentTime - timer.now()).count();
        std::this_thread::sleep_for(std::chrono::microseconds(2000 - deltaTime));
    }

    this->SetThreadStatus(false);
}

void CommandsProtocol::Stop() {
    this->_socket.Disconnect();
    this->SetErrorStatus(CommandsProtocol::ErrorType::ConnectionLost);
    this->SetOnlineStatus(false);
}

void CommandsProtocol::StartAsync(const QString &address, uint16_t port) {
    if (this->IsOnline())
        return;

    this->_transferThread = std::thread(&CommandsProtocol::Start, this, address, port);
    this->_transferThread.detach();

    this->SetThreadStatus(true);
}