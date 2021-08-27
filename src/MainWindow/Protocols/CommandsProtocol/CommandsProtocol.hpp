#ifndef CLIENT_COMMANDSPROTOCOL_HPP
#define CLIENT_COMMANDSPROTOCOL_HPP

#include "synchapi.h"

#include "../Socket/Socket.hpp"
#include "../BaseProtocol/BaseProtocol.hpp"
#include "../../Gamepad/Gamepad.hpp"
class CommandsProtocol : public BaseProtocol{

public:
    explicit CommandsProtocol(size_t gamepadId);
    ~CommandsProtocol();

    bool GetError() const;

    void SetGamepadId(size_t id);
    size_t GetGamepadId() const;

    void StartAsync(const QString &address, uint16_t port);
    void Stop();

private:
    Socket _socket;

    mutable std::shared_mutex _errorStatusMutex;

    Control::Gamepad _gamepad;

    ErrorType _errorStatus;

    void Start(const QString &address, uint16_t port);

    inline void SetErrorStatus(BaseProtocol::ErrorType errorType) {
        this->_errorStatusMutex.lock();
        this->_errorStatus = errorType;
        this->_errorStatusMutex.unlock();
    }

};

#endif
