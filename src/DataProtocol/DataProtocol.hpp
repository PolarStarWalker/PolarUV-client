#ifndef CLIENT_DATAPROTOCOL_HPP
#define CLIENT_DATAPROTOCOL_HPP

#include <QTcpSocket>

class DataProtocol {

public:

    bool ConnectToServer(QString ip, int port, int timeout);

    void SendCommand(QByteArray command);

private:

    QTcpSocket _qTcpSocket;

};

#endif
