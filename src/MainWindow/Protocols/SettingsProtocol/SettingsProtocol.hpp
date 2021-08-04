#ifndef CLIENT_SETTINGSPROTOCOL_HPP
#define CLIENT_SETTINGSPROTOCOL_HPP

#include <cstring>

#include "../BaseProtocol/BaseProtocol.hpp"
#include "../../DataStructs/RobotSettingsStruct/RobotSettingsStruct.hpp"
#include "../Socket/Socket.hpp"

class SettingsProtocol : protected BaseProtocol{

public:
    void SendAsync(const QString &address, uint16_t port, RobotSettingsStruct &&robotSettingsStruct);


private:
    Socket _socket;

    mutable std::shared_mutex _errorStatusMutex;

    ErrorType _errorStatus;

    void Send(const QString &address, uint16_t port, RobotSettingsStruct &&robotSettingsStruct);

    inline void SetErrorStatus(BaseProtocol::ErrorType errorType) {
        this->_errorStatusMutex.lock();
        this->_errorStatus = errorType;
        this->_errorStatusMutex.unlock();
    }

};


#endif
