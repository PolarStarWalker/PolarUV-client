#ifndef CLIENT_BASEEXCEPTION_HPP
#define CLIENT_BASEEXCEPTION_HPP

#include <string>

namespace Exception {

    enum ExceptionType : uint8_t {
        information,
        about,
        warning,
        critical,
        question
    };

    class BaseException : public std::exception {
    public:
        BaseException(std::string &&error, std::string &&details, ExceptionType exceptionType) {
            _error = std::move(error);
            _details = std::move(details);
            _exceptionType = exceptionType;
        }

        std::string GetError() const {
            return _error;
        }

        std::string GetDetails() const {
            return _details;
        }

        ExceptionType GetExceptionType() const {
            return _exceptionType;
        }

    private:
        std::string _error;
        std::string _details;
        ExceptionType _exceptionType;
    };
}
#endif
