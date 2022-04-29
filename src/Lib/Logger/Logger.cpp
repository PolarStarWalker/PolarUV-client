#include <boost/log/trivial.hpp>
#include "iostream"
#include "Logger.hpp"
#include <boost/stacktrace.hpp>

using namespace lib::logger;

class Info &Info::operator<<(std::string_view data) {
    if (LogLevel >= LogLevelEnum::Info)
        std::clog << "[INFO] " << data.data();

    return *this;
}


class Warning &Warning::operator<<(std::string_view data) {
    if (LogLevel >= LogLevelEnum::Warning)
        std::clog << "[WARNING] " << data.data();
    return *this;
}

class Error &Error::operator<<(std::string_view data) {
    if (LogLevel >= LogLevelEnum::Error)
        std::clog << "[ERROR] " << data.data();
    return *this;
}

class Critical &Critical::operator<<(std::string_view data) {
    if (logLevel_ >= LogLevelEnum::Critical)
        buf << data.data();
    return *this;
}

lib::logger::Critical::Critical() : buf(){}

lib::logger::Critical::~Critical() {
    if (logLevel_ >= LogLevelEnum::Critical)
        std::clog << "[Critical]" << buf.rdbuf()
                  << "[At this point]\n"
                  << boost::stacktrace::stacktrace();
}
