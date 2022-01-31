#ifndef CLIENT_COMMANDSWIDGET_HPP
#define CLIENT_COMMANDSWIDGET_HPP
#include <TcpSession/TcpSession.hpp>

#include <QObject>
#include <QTimer>

struct CommandsStruct {
    enum MoveDimensions : uint8_t {
        Fx = 0,
        Fy = 1,
        Fz = 2,
        Mx = 3,
        My = 4,
        Mz = 5
    };

    std::array<float, 6> Move{};
    std::array<float, 6> Hand{};
    std::array<float, 4> LowPWM{};
};

class Commands final : public QObject {
Q_OBJECT

public:

    Commands();
    void SendCommands();

private:
    lib::network::TcpSession& network_;
    QTimer timer_;
};


#endif
