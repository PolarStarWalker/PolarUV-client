#ifndef CLIENT_INVALIDOPERATIONEXCEPTION_HPP
#define CLIENT_INVALIDOPERATIONEXCEPTION_HPP

#include "../BaseException/BaseException.hpp"

namespace Exception {
    class InvalidOperationException : public BaseException {
    public:
        explicit InvalidOperationException(std::string &&details) : BaseException("Неправильная операция", std::move(details), information) {}
    };
}

#endif
