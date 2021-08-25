#include "./BaseProtocol/BaseProtocol.hpp"

bool BaseProtocol::IsStreamOnline() const {

    this->_protocolStatusMutex.lock_shared();
    bool isOnline = this->_isOnline;
    this->_protocolStatusMutex.unlock_shared();

    return isOnline;
}
bool BaseProtocol::IsThreadActive() const {

    this->_threadStatusMutex.lock_shared();
    bool isThreadActive = this->_isThreadActive;
    this->_threadStatusMutex.unlock_shared();

    return isThreadActive;
}
