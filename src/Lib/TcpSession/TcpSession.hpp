#ifndef CLIENT_TCPSESSION_HPP
#define CLIENT_TCPSESSION_HPP

#include <boost/asio.hpp>

namespace lib {

    namespace network {

        const size_t PORT = 2022;
        const char* IP = "192.168.1.50";

        const boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(IP), PORT);

        class TcpSession {
        public:

            static TcpSession* GetInstance();
        private:
            TcpSession() = default;

            TcpSession(const TcpSession&) = delete;
            TcpSession(TcpSession&&) = delete;

        };

    }
}

#endif
