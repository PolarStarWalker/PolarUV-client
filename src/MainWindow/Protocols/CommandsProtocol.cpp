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

    this->_statusStatusMutex.lock_shared();
    bool isOnline = this->_isOnline;
    this->_statusStatusMutex.unlock_shared();

    return isOnline;
}

bool CommandsProtocol::GetError() const {

    this->_errorStatusMutex.lock_shared();
    bool errorStatus = this->_errorStatus;
    this->_errorStatusMutex.unlock_shared();

    return errorStatus;
}

bool CommandsProtocol::IsThreadActive() const {

    this->_threadStatusMutex.lock_shared();
    bool isThreadActive = this->_isThreadActive;
    this->_threadStatusMutex.unlock_shared();

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

        ///ToDo: найти способ получше держать период 2мс
        while (std::chrono::duration<double, std::micro>(timer.now() - currentTime).count() < 2000) {}

        //std::this_thread::sleep_for(std::chrono::microseconds(2000 - (size_t) deltaTime));

        std::cout << i << ' ' <<std::chrono::duration<double, std::micro>(timer.now() - currentTime).count()<<std::endl;

    }

    this->SetOnlineStatus(false);
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