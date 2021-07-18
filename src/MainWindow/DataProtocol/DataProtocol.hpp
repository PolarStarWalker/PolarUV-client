#ifndef CLIENT_DATAPROTOCOL_HPP
#define CLIENT_DATAPROTOCOL_HPP

#include <QTcpSocket>

class DataProtocol {

public:

    bool ConnectToServer(QString address, int port);
    void Disconnect();
    bool GetStatus();
    void SendCommand(QByteArray command);

private:

    QTcpSocket _qTcpSocket;
    bool _isOnline = false;

};

#endif
