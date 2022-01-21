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
            ConnectionError,
            BufferOverflow,
        };

        struct HeaderType {
            CodeEnum Code{};
            ssize_t EndpointId{};
            size_t Length{};

            HeaderType(CodeEnum code, ssize_t endpoint, size_t length) :
                    Code(code),
                    EndpointId(endpoint),
                    Length(length) {}

            HeaderType() = default;
        };

        Response(std::string &&data, enum CodeEnum code, ssize_t endpointId) :
                Data(std::move(data)),
                Header(code, endpointId, Data.length()) {};

        Response(Response &&response) noexcept:
                Data(std::move(response.Data)),
                Header(response.Header) {}

        explicit operator bool() const { return Header.Code == Ok || Header.Code == NoContent; }

        std::string Data;
        const HeaderType Header;
    };

    struct Request {

        enum class TypeEnum : size_t {
            R,
            W,
            RW
        };

        struct HeaderType {
            TypeEnum Type;
            ssize_t EndpointId;
            size_t Length;
        };

        Request(std::string_view data, TypeEnum type, ssize_t endpointId, std::promise<Response> &response) :
                Header({type, endpointId, type == TypeEnum::R ? 0 : (data.size())}),
                Data(data),
                Response(response) {};

        Request(Request &&) = delete;

        Request(const Request &) = delete;

        std::promise<Response> &Response;
        const std::string_view Data;
        const HeaderType Header;
    };
}
#endif