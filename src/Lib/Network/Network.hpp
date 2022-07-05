#ifndef CLIENT_TCPSESSION_HPP
#define CLIENT_TCPSESSION_HPP

#include <queue>
#include <shared_mutex>

#include <boost/asio.hpp>
#include <QObject>

#include <Exceptions/Exceptions.hpp>
#include "Singleton.hpp"
#include "ThreadSafeQueue/ThreadSafeQueue.hpp"
#include "Packet.hpp"

#include <iostream>

namespace lib::network {

    class Network {
    public:

        static constexpr std::chrono::milliseconds CONNECTION_TIMEOUT = std::chrono::milliseconds(100);

        static constexpr auto TRANSFER_TIMEOUT =
#ifdef DEBUG
                std::chrono::milliseconds(2000);
#else
        std::chrono::milliseconds(2000);
#endif
        static constexpr size_t PORT = 2022;

        explicit Network();

        bool TryConnect(const std::string &ip);

        static std::vector<char> Compress(const std::string_view &);

        static std::vector<char> Decompress(const std::string &);

    private:
        Response TransferData(const Request &request);

        bool RunFor(std::chrono::steady_clock::duration timeout);

        std::mutex requestsMutex_;
        boost::asio::io_context ioContext_;
        boost::asio::ip::tcp::socket socket_;

    public:

        Response SendRequest(std::string_view data, Request::TypeEnum type, ssize_t endpointId);

        ///For non-containers objects
        template<typename Type>
        Response SendRequest(const Type &obj, Request::TypeEnum type, ssize_t endpointId) {
            return SendRequest(std::string_view((const char *) &obj, sizeof(obj)), type, endpointId);
        }

        ///For containers objects
        template<typename Type>
        Response SendRequest(const Type *obj, size_t size, Request::TypeEnum type, ssize_t endpointId) {
            return SendRequest(std::string_view((const char *) obj, size), type, endpointId);
        }

        ///For std::vector
        template<typename Type>
        Response SendRequest(const std::vector<Type> &data, Request::TypeEnum type, ssize_t endpointId) {
            return SendRequest(std::string_view((const char *) data.data(), data.size()), type, endpointId);
        }

        ///For std::strings
        Response SendRequest(const std::string &data, Request::TypeEnum type, ssize_t endpointId) {
            return SendRequest(std::string_view(data), type, endpointId);
        }

    public:
        template<Request::TypeEnum Type>
        requires (Type == Request::TypeEnum::W)
        Response NewSendRequest(ssize_t endpointId, const std::string_view &data);

        template<Request::TypeEnum Type>
        requires (Type == Request::TypeEnum::WR)
        Response NewSendRequest(ssize_t endpointId, const std::string_view &data);

        template<Request::TypeEnum Type>
        requires (Type == Request::TypeEnum::R)
        Response NewSendRequest(ssize_t endpointId);
    };

    template<Request::TypeEnum Type>
    requires (Type == Request::TypeEnum::W)
    Response Network::NewSendRequest(ssize_t endpointId, const std::string_view &data) {
        using TimePoint = std::chrono::steady_clock::time_point;

        auto compressed = Compress(data);

        std::unique_lock lock(requestsMutex_);

        TimePoint requestBegin = std::chrono::steady_clock::now();

        auto request = Request({compressed.data(), compressed.size()}, Request::TypeEnum::W, endpointId);

        auto response = TransferData(request);

        lock.unlock();

        TimePoint end = std::chrono::steady_clock::now();
        std::cout << request.Header
                  << "\nRequest Time = "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(end - requestBegin).count()
                  << "[ns]" << std::endl;

        return response;
    }

    template<Request::TypeEnum Type>
    requires (Type == Request::TypeEnum::R)
    Response Network::NewSendRequest(ssize_t endpointId) {
        using TimePoint = std::chrono::steady_clock::time_point;

        std::unique_lock lock(requestsMutex_);

        TimePoint requestBegin = std::chrono::steady_clock::now();

        auto request = Request("", Request::TypeEnum::W, endpointId);

        auto response = TransferData(request);

        lock.unlock();

        TimePoint end = std::chrono::steady_clock::now();
        std::cout << request.Header
                  << "\n[REQUEST TIME]\n"
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(end - requestBegin).count()
                  << "[ns]" << std::endl;

        return response;
    }

    template<lib::network::Request::TypeEnum RequestCode>
    requires (RequestCode == Request::TypeEnum::W)
    void StatusCodeCheck(enum lib::network::Response::CodeEnum responseCode) {

        Function function = [=]() {
            switch (responseCode) {
                case Response::Ok:
                    throw exceptions::InvalidOperationException("Неправильный код возврата");
                case Response::NoContent:
                    return;
                case Response::BadRequest:
                    throw exceptions::InvalidOperationException("Возникла ошибка на сервере");
                case Response::ConnectionError:
                    throw exceptions::ConnectionException("Не удалось подключиться к роботу");
                case Response::BufferOverflow:
                    throw exceptions::InvalidOperationException("Слишком большая посылка");
            }
        };

        ExceptionHandler(nullptr, nullptr, function);
    }

    template<lib::network::Request::TypeEnum RequestCode>
    requires (RequestCode == Request::TypeEnum::W)
    void StatusCodeCheck(enum lib::network::Response::CodeEnum responseCode, Function action) {

        Function function = [=]() {
            switch (responseCode) {
                case Response::Ok:
                    throw exceptions::InvalidOperationException("Неправильный код возврата");
                case Response::NoContent:
                    action();
                    return;
                case Response::BadRequest:
                    throw exceptions::InvalidOperationException("Возникла ошибка на сервере");
                case Response::ConnectionError:
                    throw exceptions::ConnectionException("Не удалось подключиться к роботу");
                case Response::BufferOverflow:
                    throw exceptions::InvalidOperationException("Слишком большая посылка");
            }
        };

        ExceptionHandler(nullptr, nullptr, function);
    }

    template<lib::network::Request::TypeEnum RequestCode>
    requires (RequestCode == Request::TypeEnum::R)
    void StatusCodeCheck(enum lib::network::Response::CodeEnum responseCode, Function action) {
        Function function = [=]() {
            switch (responseCode) {
                case Response::Ok:
                    action();
                    return;
                case Response::NoContent:
                    throw exceptions::InvalidOperationException("Нет данных");
                case Response::BadRequest:
                    throw exceptions::InvalidOperationException("Возникла ошибка на сервере");
                case Response::ConnectionError:
                    throw exceptions::ConnectionException("Не удалось подключиться к роботу");
                case Response::BufferOverflow:
                    throw exceptions::InvalidOperationException("Слишком большая посылка");
            }
        };

        ExceptionHandler(nullptr, nullptr, function);
    }


}

#endif
