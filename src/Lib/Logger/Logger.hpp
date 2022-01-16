#ifndef CLIENT_LOGGER_HPP
#define CLIENT_LOGGER_HPP

#include <ostream>

namespace lib::logger {

    ///It must be ordered
    enum LogLevelEnum : uint8_t{
        Zero,
        Critical,
        Error,
        Warning,
        Info
    };

    static LogLevelEnum LogLevel = LogLevelEnum::Error;

    struct Critical{
        Critical& operator<<(std::string_view);
    };

    struct Error{
        class Error& operator<<(std::string_view);
    };

    struct Warning {
        Warning& operator<<(std::string_view);
    };

    struct Info {
        Info& operator<<(std::string_view);
    };

    static class Critical critical;
    static class Error error;
    static class Warning warning;
    static class Info info;

    static void Setup() {
#if DEBUG
        std::clog.rdbuf(std::cout.rdbuf());
#else
        std::fstream output("log.txt", std::ios_base::out | std::ios_base::trunc);
        std::clog.rdbuf(output.rdbuf());
#endif
    }

};

#endif