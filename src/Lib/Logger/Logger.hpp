#ifndef CLIENT_LOGGER_HPP
#define CLIENT_LOGGER_HPP

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

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
        Critical();
        Critical& operator<<(std::string_view);
        ~Critical();
    private:
        LogLevelEnum logLevel_ = LogLevel;
        std::stringstream buf;
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

    static void Setup() {
#if 1
        std::clog.rdbuf(std::cout.rdbuf());
#else
        static std::fstream output("log.txt", std::ios_base::out | std::ios_base::trunc);
        std::clog.rdbuf(output.rdbuf());
#endif
    }

};

#endif