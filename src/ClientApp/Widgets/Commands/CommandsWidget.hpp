#ifndef CLIENT_COMMANDSWIDGET_HPP
#define CLIENT_COMMANDSWIDGET_HPP
#include "../WidgetResources.hpp"

#include <QWidget>
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

    enum StabilizationType : int8_t {
        None = 0,
        Rotation = 1,
        Absolute = 2
    };

    std::array<float, 6> Move{};
    std::array<float, 6> Hand{};
    std::array<float, 4> LowPWM{};

    StabilizationType Stabilization = None;
};

class CommandsWidget final : public QWidget {
Q_OBJECT

public:

    CommandsWidget(QWidget *parent, WidgetResources& resources);

public slots:
    void StartWidget();
    void StopWidget();

private slots:
    void SendCommands();

private:
    WidgetResources& resources_;
    QTimer timer_;
};


#endif
