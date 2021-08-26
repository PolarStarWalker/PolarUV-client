#ifndef CLIENT_BASEPROTOCOL_HPP
#define CLIENT_BASEPROTOCOL_HPP

#include <shared_mutex>
#include <thread>
#include <chrono>

#include "../../Exceptions/Exceptions.hpp"

class BaseProtocol {
public:

    enum ErrorType : uint8_t {
        Ok = 0,
        CantConnectToServer = 1,
        ConnectionLost = 2,
    };

    bool IsStreamOnline() const;

    bool IsThreadActive() const;

protected:
    mutable std::shared_mutex _protocolStatusMutex;
    mutable std::shared_mutex _threadStatusMutex;

    std::thread _transferThread;

    bool _isOnline;
    bool _isThreadActive;

    inline void SetOnlineStatus(bool status) {
        this->_protocolStatusMutex.lock();
        this->_isOnline = status;
        this->_protocolStatusMutex.unlock();
    }

    inline void SetThreadStatus(bool status) {
        this->_threadStatusMutex.lock();
        this->_isThreadActive = status;
        this->_threadStatusMutex.unlock();
    }
};

#endif
