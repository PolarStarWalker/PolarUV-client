#include "Socket.hpp"

bool Socket::ConnectToServer(const QString &address, uint16_t port) {
    ///lock_guard в конструкторе захватывает мьютекс и лочит его, в деструктуре разлочивает
    ///(без него не получистя, ибо нужно разлочить мьютекс после return, когда совершён выход из функции)
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.connectToHost(address, port);
    this->_isOnline = _qTcpSocket.waitForConnected();
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

void Socket::SendCommand(const QByteArray &command) {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.write(command);
    this->_isOnline = this->_qTcpSocket.waitForBytesWritten(1000);
}

void Socket::SendSettings(const QByteArray &settings) {
    this->_qTcpSocket.write(settings);
    this->_isOnline = this->_qTcpSocket.waitForBytesWritten(2000);
}