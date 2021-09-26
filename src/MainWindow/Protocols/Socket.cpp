#include "Socket/Socket.hpp"

bool Socket::ConnectToServer(const QString &address, uint16_t port) {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.connectToHost(address, port);
    bool isOnline = _qTcpSocket.waitForConnected(1000);
    this->SetOnlineStatus(isOnline);

    return isOnline;
}

void Socket::Disconnect() {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.disconnectFromHost();
    this->SetOnlineStatus(false);
}

bool Socket::IsOnline() const {
    this->_statusMutex.lock_shared();
    bool status = this->_isOnline;
    this->_statusMutex.unlock_shared();
    return status;
}

void Socket::Send(const char *data, size_t size) {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.write(data, size);
    bool isOnline = this->_qTcpSocket.waitForBytesWritten(1000);
    this->SetOnlineStatus(isOnline);
}

void Socket::Recv(char *data, size_t size) {
    std::lock_guard<std::mutex> guard(this->_socketMutex);

    bool isHasData = _qTcpSocket.waitForReadyRead(1000);

    if (isHasData)
        this->_qTcpSocket.read(data, size);

    this->SetOnlineStatus(isHasData);
}
