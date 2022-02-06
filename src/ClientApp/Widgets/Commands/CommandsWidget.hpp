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

    std::array<float, 6> Move{};
    std::array<float, 6> Hand{};
    std::array<float, 4> LowPWM{};
};

class CommandsWidget final : public QWidget {
Q_OBJECT

public slots:
    void StartWidget();
    void StopWidget();

private slots:
    void SendCommands();

public:

    CommandsWidget(QWidget *parent, WidgetResources& resources);


private:
    WidgetResources& resources_;
    QTimer timer_;
};


#endif
