#include "DataProtocol.hpp"

bool DataProtocol::ConnectToServer(QString ip, int port, int timeout = 30000) {

    this->_qTcpSocket.connectToHost("169.254.154.5",1999);

    if (this->_qTcpSocket.waitForConnected(timeout)) {
        return true;
    }
    else {
        return false;
    }
}

void DataProtocol::SendCommand(QByteArray command) {
    this->_qTcpSocket.write(command);
    this->_qTcpSocket.waitForBytesWritten();
}