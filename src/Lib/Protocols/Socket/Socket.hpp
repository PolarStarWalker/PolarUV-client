#ifndef CLIENT_SOCKET_HPP
#define CLIENT_SOCKET_HPP

#include <QString>
#include <QTcpSocket>

#include <shared_mutex>

class Socket {
public:
    bool ConnectToServer(const QString &address, uint16_t port);

    void Disconnect();

    void Send(const char *data, ssize_t size);

    void Recv(char *data, ssize_t size);

    inline bool IsOnline() const {
        return _isOnline;
    };

private:
    QTcpSocket _qTcpSocket;
    mutable std::mutex _socketMutex;
    std::atomic<bool> _isOnline = false;

    inline void SetOnlineStatus(bool isOnline) {
        _isOnline = isOnline;
    }
};

#endif
