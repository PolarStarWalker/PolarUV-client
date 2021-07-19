#ifndef CLIENT_SOCKET_HPP
#define CLIENT_SOCKET_HPP

#include <QString>
#include <QTcpSocket>

#include <mutex>

class Socket {
public:
    bool ConnectToServer(const QString& address, uint16_t port);
    void Disconnect();
    void SendCommand(const QByteArray& command);
    bool IsOnline() const;

private:
    QTcpSocket _qTcpSocket;
    mutable std::mutex _socketMutex;
    bool _isOnline = false;
};

#endif
