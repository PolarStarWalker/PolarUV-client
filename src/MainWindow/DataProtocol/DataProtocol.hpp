#ifndef CLIENT_DATAPROTOCOL_HPP
#define CLIENT_DATAPROTOCOL_HPP

#include <mutex>
#include <thread>
#include <chrono>

#include "Socket.hpp"

class DataProtocol : public QObject {
    enum ErrorType : uint8_t {
        Ok = 0,
        CantConnectToServer = 1,
        ConnectionLost = 2,
    };

public:
    DataProtocol();
    ~DataProtocol();

    bool IsOnline() const;
    bool GetError() const;
    bool IsThreadActive() const;

    void StartAsync(const QString &address, uint16_t port);
    void Stop();

private:
    Socket _socket;

    /// mutable нужен для того чтобы менять поля в const функциях
    mutable std::mutex _statusStatusMutex;
    mutable std::mutex _errorStatusMutex;
    mutable std::mutex _threadStatusMutex;

    std::thread _transferThread;

    bool _isOnline;
    bool _isThreadActive;
    ErrorType _errorStatus;

    void Start(const QString &address, uint16_t port);

    inline void SetOnlineStatus(bool status) {
        this->_statusStatusMutex.lock();
        this->_isOnline = status;
        this->_statusStatusMutex.unlock();
    }

    inline void SetErrorStatus(DataProtocol::ErrorType errorType) {
        this->_errorStatusMutex.lock();
        this->_errorStatus = errorType;
        this->_errorStatusMutex.unlock();
    }

    inline void SetThreadStatus(bool status) {
        this->_threadStatusMutex.lock();
        this->_isThreadActive = status;
        this->_threadStatusMutex.unlock();
    }

};

#endif
