#ifndef CLIENT_BASEEXCEPTION_HPP
#define CLIENT_BASEEXCEPTION_HPP

#include <string>

namespace lib::exceptions {

    enum ExceptionType : uint8_t {
        information,
        about,
        warning,
        critical,
        question
    };

    class BaseException : public std::exception {
    public:
        BaseException(std::string_view error, std::string_view& details, ExceptionType exceptionType) :
                Error(error),
                Details(details),
                _exceptionType(exceptionType){}

        const std::string_view Error;
        const std::string_view Details;
        const ExceptionType _exceptionType;
    };
}
#endif
