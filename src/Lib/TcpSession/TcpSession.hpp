#ifndef CLIENT_TCPSESSION_HPP
#define CLIENT_TCPSESSION_HPP

#include <queue>
#include <shared_mutex>

#include <boost/asio.hpp>
#include <QObject>

#include <Exceptions/Exceptions.hpp>
#include "Packet.hpp"

namespace lib::network {

    static constexpr size_t PORT = 2022;
    static constexpr char IP[13] = "192.168.1.50";
    static const boost::asio::ip::tcp::endpoint ENDPOINT(boost::asio::ip::make_address(IP), PORT);

    class TcpSession final : public QObject {
    Q_OBJECT
    public:

        TcpSession(const TcpSession &) = delete;

        TcpSession(TcpSession &&) = delete;

        static TcpSession &GetInstance();

        Response Send(const Packet &packet) const;
        Response Send(Packet &&packet) const;

        inline bool IsOnline() { return _status; }

    public slots:

        [[noreturn]] void Start();

    private:

        mutable std::queue<const TcpRequest *> _requests{};
        mutable std::mutex _requestsMutex;
        mutable std::condition_variable _queueIsNotEmpty;
        mutable std::atomic<bool> _status{};

        void AddToQueue(const TcpRequest &request) const;

        explicit TcpSession(QObject *parent = nullptr);

        ~TcpSession() final = default;

    };

    template<lib::network::Packet::TypeEnum RequestCode>
    requires(RequestCode == Packet::TypeEnum::W)
    void StatusCodeCheck(enum lib::network::Response::CodeEnum responseCode) {

        Function function = [=]() {
                switch (responseCode) {
                    case Response::Ok:
                        throw Exception::InvalidOperationException("Неправильный код возврата");
                    case Response::NoContent:
                        return;
                    case Response::BadRequest:
                        throw Exception::InvalidOperationException("Возникла ошибка на сервере");
                    case Response::ConnectionError:
                        throw Exception::ConnectionException("Не удалось подключиться к роботу");
                }
            };

        ExceptionHandler(nullptr, nullptr, function);
    }

    template<lib::network::Packet::TypeEnum RequestCode>
    requires(RequestCode == Packet::TypeEnum::W)
    void StatusCodeCheck(enum lib::network::Response::CodeEnum responseCode, Function action) {

        Function function = [=]() {
            switch (responseCode) {
                case Response::Ok:
                    throw Exception::InvalidOperationException("Неправильный код возврата");
                case Response::NoContent:
                    action();
                    return;
                case Response::BadRequest:
                    throw Exception::InvalidOperationException("Возникла ошибка на сервере");
                case Response::ConnectionError:
                    throw Exception::ConnectionException("Не удалось подключиться к роботу");
            }
        };

        ExceptionHandler(nullptr, nullptr, function);
    }

    template<lib::network::Packet::TypeEnum RequestCode>
    requires (RequestCode == Packet::TypeEnum::R)
    void StatusCodeCheck(enum lib::network::Response::CodeEnum responseCode, Function action){
        Function function = [=]() { switch (responseCode) {
                    case Response::Ok:
                        action();
                        return;
                    case Response::NoContent:
                        throw Exception::InvalidOperationException("Нет данных");
                    case Response::BadRequest:
                        throw Exception::InvalidOperationException("Возникла ошибка на сервере");
                    case Response::ConnectionError:
                        throw Exception::ConnectionException("Не удалось подключиться к роботу");
                }
            };

        ExceptionHandler(nullptr, nullptr, function);
    }
}

#endif
