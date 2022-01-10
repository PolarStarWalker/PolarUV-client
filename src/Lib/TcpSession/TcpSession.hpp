#ifndef CLIENT_TCPSESSION_HPP
#define CLIENT_TCPSESSION_HPP

#include <queue>
#include <shared_mutex>
#include <future>
#include <string>

#include <boost/asio.hpp>

#include <QObject>

namespace lib::network {

    struct Response {
        enum Code : size_t {
            Ok,
            NoContent,
            BadRequest,
            ConnectionError
        };

        std::string Data;
        const Code Code;

        Response(std::string &&data, enum Code code) : Data(std::move(data)), Code(code) {};

        explicit operator bool() const { return Code == Ok || Code == NoContent; }
    };

    struct Packet {

        enum Type : size_t {
            R,
            W,
            RW
        };

        const Type Type;
        const ssize_t EndpointId;
        const std::string_view Data;

        Packet(enum Type type, const std::string_view data, ssize_t endpointId) :
                Type(type),
                Data(data),
                EndpointId(endpointId) {}
    };

    struct TcpRequest {

        TcpRequest(std::promise<Response *> &response, const Packet &packet) : Response(&response), Packet(packet) {};

        std::promise<Response *> *Response;

        const Packet &Packet;
    };


    static constexpr size_t PORT = 2022;
    static constexpr char IP[13] = "192.168.1.50";
    static const boost::asio::ip::tcp::endpoint ENDPOINT(boost::asio::ip::make_address(IP), PORT);

    class TcpSession {
    public:

        TcpSession(const TcpSession &) = delete;
        TcpSession(TcpSession &&) = delete;

        static TcpSession &GetInstance();
        Response Send(const Packet &packet) const;

    private:

        mutable std::queue<TcpRequest *> _requests{};
        mutable std::shared_mutex _requestsMutex;

        TcpSession() = default;
        ~TcpSession() = default;
    };

}

#endif
