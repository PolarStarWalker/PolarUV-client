#include "DataProtocol.hpp"
#include "../../DataStruct.hpp"

#include <iostream>

DataProtocol::DataProtocol() {
    this->_socket = new Socket;
    this->_isOnline = false;
    this->_errorStatus = DataProtocol::ErrorType::Ok;
}

DataProtocol::~DataProtocol() {
    ///ToDo: motov.s - когда-нибудь придумай что-нибудь получше этого безобразия
    while (this->IsThreadActive())
        std::this_thread::sleep_for(std::chrono::microseconds(1));

    delete this->_socket;
}

bool DataProtocol::IsOnline() const {
    std::lock_guard<std::mutex> guard(this->_statusStatusMutex);
    return this->_isOnline;
}

bool DataProtocol::GetError() const {
    std::lock_guard<std::mutex> guard(this->_errorStatusMutex);
    return this->_errorStatus;
}

bool DataProtocol::IsThreadActive() const {
    std::lock_guard<std::mutex> threadStatusGuard(this->_threadStatusMutex);
    return this->_isThreadActive;
}

void DataProtocol::Start(const QString &address, uint16_t port) {

    bool isConnected = this->_socket->ConnectToServer(address, port);

    if (!isConnected) {
        this->SetErrorStatus(DataProtocol::ErrorType::CantConnectToServer);
        return;
    }

    this->SetOnlineStatus(true);

    QByteArray commandsStruct(CommandsStructLen, 0);

    ///Не удивляйся, это типа while, но со счётчиком
    for (size_t i = 0; _socket->IsOnline(); i++) {

        ///ToDo: реализовать тут протокол

        ((CommandsStruct *) commandsStruct.data())->VectorArray[0] = i;
        _socket->SendCommand(commandsStruct);

        ///Пока 2 мс, потом это скорее всего надо будет вынести в отдельную настройку
        std::this_thread::sleep_for(std::chrono::microseconds(2000));
    }

    this->SetThreadStatus(false);
}

void DataProtocol::Stop() {
    this->_socket->Disconnect();
    this->SetErrorStatus(DataProtocol::ErrorType::ConnectionLost);
    this->SetOnlineStatus(false);
}

void DataProtocol::StartAsync(const QString &address, uint16_t port) {
    if (this->IsOnline())
        return;

    this->_transferThread = std::thread(&DataProtocol::Start, this, address, port);
    this->_transferThread.detach();

    this->SetThreadStatus(true);
}