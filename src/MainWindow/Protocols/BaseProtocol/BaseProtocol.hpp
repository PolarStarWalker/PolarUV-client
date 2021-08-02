#ifndef CLIENT_BASEPROTOCOL_HPP
#define CLIENT_BASEPROTOCOL_HPP
#include <shared_mutex>
#include <thread>
#include <chrono>


class BaseProtocol{
public:

    bool IsOnline() const;
    bool IsThreadActive() const;



protected:


    /// mutable нужен для того чтобы менять поля в const функциях
    mutable std::shared_mutex _statusStatusMutex;
    mutable std::shared_mutex _threadStatusMutex;

    std::thread _transferThread;

    bool _isOnline;
    bool _isThreadActive;

    inline void SetOnlineStatus(bool status) {
        this->_statusStatusMutex.lock();
        this->_isOnline = status;
        this->_statusStatusMutex.unlock();
    }


    inline void SetThreadStatus(bool status) {
        this->_threadStatusMutex.lock();
        this->_isThreadActive = status;
        this->_threadStatusMutex.unlock();
    }
};


#endif //CLIENT_BASEPROTOCOL_HPP
