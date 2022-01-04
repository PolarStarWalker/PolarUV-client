#ifndef CLIENT_TCPSESSION_HPP
#define CLIENT_TCPSESSION_HPP

#include <queue>
#include <shared_mutex>
#include <future>

#include <boost/asio.hpp>

#include <QObject>

namespace lib {
    namespace network {

        struct Response{

        };

        struct Packet{

        };

        struct Request{

            Request(std::promise<Response*>& response, const Packet& packet) : Response(&response), Packet(&packet){};

            std::promise<Response*>* Response;

            const Packet* Packet;
        };

        const size_t PORT = 2022;
        const char* IP = "192.168.1.50";

        const boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(IP), PORT);

        class TcpSession {
        public:

            TcpSession(const TcpSession&) = delete;
            TcpSession(TcpSession&&) = delete;

            static TcpSession* GetInstance();

            Response Send(const Packet& packet);

        private:

            std::queue<Request*> _requests;
            std::shared_mutex _requestsMutex;

            TcpSession() = default;

            ~TcpSession() = default;
        };

    }
}

#endif
