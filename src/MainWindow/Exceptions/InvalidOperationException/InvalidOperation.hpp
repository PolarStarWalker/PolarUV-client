#ifndef CLIENT_INVALIDOPERATION_HPP
#define CLIENT_INVALIDOPERATION_HPP

#include "../BaseException/BaseException.hpp"

namespace Exception {
    class InvalidOperation : public BaseException {
    public:
        explicit InvalidOperation(std::string &&details) : BaseException("Неправильная операция", std::move(details), information) {}
    };
}

#endif
