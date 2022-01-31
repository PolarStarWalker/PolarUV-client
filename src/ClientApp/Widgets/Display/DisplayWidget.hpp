#ifndef CLIENT_DISPLAYWIDGET_HPP
#define CLIENT_DISPLAYWIDGET_HPP

#include <QWidget>
#include <QMainWindow>

#include "./Protocols/Protocols.hpp"

#define COMMANDS_PORT 1999

QT_BEGIN_NAMESPACE
namespace Ui { class DisplayWidget; }
QT_END_NAMESPACE

class DisplayWidget : public QWidget {
Q_OBJECT

public:
    explicit DisplayWidget(QMainWindow *mainWindow, QWidget *parent = nullptr);

    ~DisplayWidget() override;

    void SetRobotIP(const QString& ip) {this->RobotIP = ip;};
    void SetClientIP(const QString& ip) {this->ClientIP = ip;};
    void SetGamepadID(int id) {this->GamepadID = id;};

private:
    Ui::DisplayWidget *ui;

    std::unique_ptr<VideoProtocol> videoProtocol_;
    std::unique_ptr<CommandsProtocol> commandsProtocol_;

    QString RobotIP{};
    QString ClientIP{};

    int GamepadID{};

public slots:

    void ShowSideBarButton();

private slots:

    void SwitchVideoStream();
    void SwitchVideoCapture();
    void TakeScreenshot();
    void SwitchSendingCommands();

    void HideSideBarButton();
};


#endif //CLIENT_DISPLAYWIDGET_HPP