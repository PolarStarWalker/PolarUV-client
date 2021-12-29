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

void Socket::Send(const char *data, ssize_t size) {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.write(data, size);
    bool isOnline = this->_qTcpSocket.waitForBytesWritten(1000);
    this->SetOnlineStatus(isOnline);
}

void Socket::Recv(char *data, ssize_t size) {
    std::lock_guard<std::mutex> guard(this->_socketMutex);

    bool isHasData = _qTcpSocket.bytesAvailable() >= size;

    if(!isHasData)
        isHasData = _qTcpSocket.waitForReadyRead(1000);

    if (isHasData)
        this->_qTcpSocket.read(data, size);

    this->SetOnlineStatus(isHasData);
}
