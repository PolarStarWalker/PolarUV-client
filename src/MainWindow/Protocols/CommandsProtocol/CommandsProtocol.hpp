#ifndef CLIENT_COMMANDSPROTOCOL_HPP
#define CLIENT_COMMANDSPROTOCOL_HPP

#include <shared_mutex>
#include <thread>
#include <chrono>

#include "../Socket/Socket.hpp"
#include "../../Gamepad/Gamepad.hpp"

class CommandsProtocol {
    enum ErrorType : uint8_t {
        Ok = 0,
        CantConnectToServer = 1,
        ConnectionLost = 2,
    };

public:
    explicit CommandsProtocol(size_t gamepadId);
    ~CommandsProtocol();

    bool IsOnline() const;
    bool GetError() const;
    bool IsThreadActive() const;

    void StartAsync(const QString &address, uint16_t port);
    void Stop();

private:
    Socket _socket;

    /// mutable нужен для того чтобы менять поля в const функциях
    mutable std::shared_mutex _statusStatusMutex;
    mutable std::shared_mutex _errorStatusMutex;
    mutable std::shared_mutex _threadStatusMutex;

    std::thread _transferThread;

    Control::Gamepad _gamepad;

    bool _isOnline;
    bool _isThreadActive{};
    ErrorType _errorStatus;

    void Start(const QString &address, uint16_t port);

    inline void SetOnlineStatus(bool status) {
        this->_statusStatusMutex.lock();
        this->_isOnline = status;
        this->_statusStatusMutex.unlock();
    }

    inline void SetErrorStatus(CommandsProtocol::ErrorType errorType) {
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
