#ifndef CLIENT_PACKET_HPP
#define CLIENT_PACKET_HPP

#include <future>
#include <string>

namespace lib::network {

    struct Response {
        enum CodeEnum : size_t {
            Ok,
            NoContent,
            BadRequest,
            ConnectionError
        };

        std::string Data;
        const CodeEnum Code;

        Response(std::string &&data, enum CodeEnum code) : Data(std::move(data)), Code(code) {};

        explicit operator bool() const { return Code == Ok || Code == NoContent; }
    };

    struct Packet {

        enum class TypeEnum : size_t {
            R,
            W,
            RW
        };

        const TypeEnum Type;
        const ssize_t EndpointId;
        const std::string_view Data;

        Packet(enum TypeEnum type, const std::string_view data, ssize_t endpointId) :
                Type(type),
                Data(data),
                EndpointId(endpointId) {}
    };

    struct TcpRequest {

        TcpRequest(std::promise<Response *> &response, const Packet &packet) : Response(&response), Packet(packet) {};

        TcpRequest(TcpRequest&&) = delete;
        TcpRequest(const TcpRequest&) = delete;

        std::promise<Response *> *Response;

        const Packet &Packet;
    };
}
#endif