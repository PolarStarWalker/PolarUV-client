#ifndef CLIENT_ROBOTSETTINGSPROTOCOL_HPP
#define CLIENT_ROBOTSETTINGSPROTOCOL_HPP

#include <cstring>

#include "../BaseProtocol/Base.hpp"
#include "../../DataStructs/RobotSettingsStruct/RobotSettingsStruct.hpp"
#include "../Socket/Socket.hpp"

class RobotSettingsProtocol : protected BaseProtocol{

public:
    void SendAsync(const QString &address, uint16_t port, RobotSettingsStruct &&robotSettingsStruct);


private:
    mutable std::shared_mutex _errorStatusMutex;

    ErrorType _errorStatus;

    void Send(const QString &address, uint16_t port, RobotSettingsStruct &&robotSettingsStruct);
    void Recv(const QString &address, uint16_t port, RobotSettingsStruct &robotSettingsStruct);

    inline void SetErrorStatus(BaseProtocol::ErrorType errorType) {
        this->_errorStatusMutex.lock();
        this->_errorStatus = errorType;
        this->_errorStatusMutex.unlock();
    }

};


#endif
