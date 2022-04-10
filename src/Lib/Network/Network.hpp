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

namespace lib::network {

    class Network {
    public:

        static constexpr std::chrono::milliseconds CONNECTION_TIMEOUT = std::chrono::milliseconds(100);

        static constexpr auto TRANSFER_TIMEOUT =
#ifdef DEBUG
         std::chrono::milliseconds(200);
#else
        std::chrono::milliseconds(20);
#endif
        static constexpr size_t PORT = 2022;

        explicit Network();

        bool TryConnect(const std::string &ip);

        static std::vector<char> Compress(const std::string_view&);

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
        Response SendRequest(const Type& obj, Request::TypeEnum type, ssize_t endpointId){
            return SendRequest(std::string_view((char*) &obj, sizeof(obj)), type, endpointId);
        }

        ///For containers objects
        template<typename Type>
        Response SendRequest(const Type* obj, size_t size, Request::TypeEnum type, ssize_t endpointId){
            return SendRequest(std::string_view((char*) obj, size), type, endpointId);
        }

        ///For std::vector
        template<typename Type>
        Response SendRequest(const std::vector<Type>& data, Request::TypeEnum type, ssize_t endpointId){
            return SendRequest(std::string_view((char*) data.data(), data.size()), type, endpointId);
        }

        ///For std::strings
        Response SendRequest(const std::string& data, Request::TypeEnum type, ssize_t endpointId){
            return SendRequest(std::string_view(data), type, endpointId);
        }


    public:

        template <lib::network::Request::TypeEnum RequestCode>
        requires (RequestCode == Request::TypeEnum::W)
        void CheckStatusCode(){

        }

    };



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
