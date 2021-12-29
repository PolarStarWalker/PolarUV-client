#ifndef CLIENT_CONNECTIONEXCEPTION_HPP
#define CLIENT_CONNECTIONEXCEPTION_HPP

#include "../BaseException/BaseException.hpp"

namespace Exception {
    class ConnectionException : public BaseException {
    public:
        explicit ConnectionException(std::string &&details) : BaseException("Ошибка подключения", std::move(details), warning) {}
    };
}

#endif
