#ifndef CLIENT_ROBOTSETTINGSPROTOCOL_HPP
#define CLIENT_ROBOTSETTINGSPROTOCOL_HPP

#include <cstring>

#include "DataStructs/RobotSettings/OldRobotSettingsDto.hpp"
#include "../BaseProtocol/BaseProtocol.hpp"
#include <QTcpSocket>

class RobotSettingsProtocol : protected BaseProtocol {
public:
    void SendAsync(const QString &address, uint16_t port, data_structs::OldRobotSettingsDto &&robotSettingsStruct);

    void Send(const QString &address, uint16_t port, data_structs::OldRobotSettingsDto &&robotSettingsStruct);

    ///NRVO, i choose you
    data_structs::OldRobotSettingsDto Recv(const QString &address, uint16_t port);

private:
    mutable std::shared_mutex _errorStatusMutex;

    ErrorType _errorStatus;

    inline void SetErrorStatus(BaseProtocol::ErrorType errorType) {
        this->_errorStatusMutex.lock();
        this->_errorStatus = errorType;
        this->_errorStatusMutex.unlock();
    }

};


#endif
