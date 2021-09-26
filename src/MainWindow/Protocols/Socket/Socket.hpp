#ifndef CLIENT_SOCKET_HPP
#define CLIENT_SOCKET_HPP

#include <QString>
#include <QTcpSocket>

#include <shared_mutex>

class Socket {
public:
    bool ConnectToServer(const QString& address, uint16_t port);
    void Disconnect();
    void Send(const char *data, size_t size);
    void Recv(char *data, size_t size);
    bool IsOnline() const;

private:
    QTcpSocket _qTcpSocket;
    mutable std::mutex _socketMutex;
    mutable std::shared_mutex _statusMutex;
    bool _isOnline = false;

    inline void SetOnlineStatus(bool isOnline){
        this->_statusMutex.lock();
        this->_isOnline = isOnline;
        this->_statusMutex.unlock();
    }
};

#endif
