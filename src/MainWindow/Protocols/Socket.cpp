#include "Socket/Socket.hpp"

bool Socket::ConnectToServer(const QString &address, uint16_t port) {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.connectToHost(address, port);
    this->_isOnline = _qTcpSocket.waitForConnected(1000);
    return this->_isOnline;
}

void Socket::Disconnect() {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.disconnectFromHost();
    this->_isOnline = false;
}

bool Socket::IsOnline() const {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    return this->_isOnline;
}

void Socket::Send(const char *data, size_t size) {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.write(data, size);
    this->_isOnline = this->_qTcpSocket.waitForBytesWritten(1000);
}

void Socket::Recv(char *data, size_t size) {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    bool isHasData = _qTcpSocket.readBufferSize() < size;

    if (!isHasData)
        isHasData = _qTcpSocket.waitForReadyRead(1000);

    if(isHasData)
        this->_qTcpSocket.read(data, size);

    this->_isOnline = isHasData;
}
