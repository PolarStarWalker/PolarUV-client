#ifndef CLIENT_BASEPROTOCOL_HPP
#define CLIENT_BASEPROTOCOL_HPP

#include <shared_mutex>
#include <thread>
#include <chrono>
#include <atomic>

#include "../../Exceptions/Exceptions.hpp"

class BaseProtocol {
public:

    enum ErrorType : uint8_t {
        Ok = 0,
        CantConnectToServer = 1,
        ConnectionLost = 2,
    };

    bool IsStreamOnline() const { return _isOnline; }

    bool IsThreadActive() const { return _isThreadActive; }


protected:
    std::thread _transferThread;

    std::atomic<bool> _isOnline;
    std::atomic<bool> _isThreadActive;

    inline void SetOnlineStatus(bool status) {
        _isOnline = status;
    }

    inline void SetThreadStatus(bool status) {
        _isThreadActive = status;
    }
};

#endif
