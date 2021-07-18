#include "DataProtocol.hpp"

bool DataProtocol::ConnectToServer(QString address, int port) {

    this->_qTcpSocket.connectToHost(address,port);

    if (this->_qTcpSocket.waitForConnected()) {
        this->_isOnline = true;
        return true;
    }
    else {
        return false;
    }
}

void DataProtocol::Disconnect() {

    this->_qTcpSocket.disconnectFromHost();

    this->_isOnline = false;
}

bool DataProtocol::GetStatus() {
    return this->_isOnline;
}

void DataProtocol::SendCommand(QByteArray command) {
    this->_qTcpSocket.write(command);
    this->_qTcpSocket.waitForBytesWritten();
}