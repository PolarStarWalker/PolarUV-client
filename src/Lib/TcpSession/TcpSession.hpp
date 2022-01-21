#ifndef CLIENT_TCPSESSION_HPP
#define CLIENT_TCPSESSION_HPP

#include <queue>
#include <shared_mutex>

#include <boost/asio.hpp>
#include <QObject>

#include <Exceptions/Exceptions.hpp>
#include "Packet.hpp"

namespace lib::network {

    class TcpSession final : public QObject {
    Q_OBJECT
    public:

        TcpSession(const TcpSession &) = delete;

        TcpSession(TcpSession &&) = delete;

        static TcpSession &GetInstance();

        Response Send(std::string_view data, Request::TypeEnum, ssize_t endpointId) const;

        inline bool IsOnline() { return _status; }

    private:
        void Start();

        mutable std::queue<Request *> _requests{};
        mutable std::mutex _requestsMutex;
        mutable std::condition_variable _queueIsNotEmpty;
        mutable std::atomic<bool> _status{};
        std::atomic<bool> _isDone{};

        std::thread _thread;

        void AddTaskToQueue(Request &request) const;

        Request &GetTask();

        explicit TcpSession(QObject *parent = nullptr);

        ~TcpSession() final;

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
