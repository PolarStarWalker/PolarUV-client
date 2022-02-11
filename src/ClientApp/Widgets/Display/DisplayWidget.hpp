#ifndef CLIENT_DISPLAYWIDGET_HPP
#define CLIENT_DISPLAYWIDGET_HPP

#include "../WidgetResources.hpp"

#include <QWidget>
#include <QMainWindow>

#include "./VideoStream/VideoStream.hpp"
#include "./Protocols/Protocols.hpp"

#define COMMANDS_PORT 1999

QT_BEGIN_NAMESPACE
namespace Ui { class DisplayWidget; }
QT_END_NAMESPACE

class DisplayWidget : public QWidget {
Q_OBJECT

public:
    DisplayWidget(QMainWindow *mainWindow, WidgetResources& resources);

    ~DisplayWidget() override;

    void SetGamepadID(int id) {this->GamepadID = id;};

private:

    lib::processing::VideoStream stream_;

    WidgetResources& resources_;

    Ui::DisplayWidget *ui;

    std::unique_ptr<QTimer> updateTimer_;

    std::unique_ptr<CommandsProtocol> commandsProtocol_;

    QPixmap placeholderPixmap_;
    QPixmap pixmap_;
    QPalette palette_;

    int GamepadID{};

public slots:

    void UpdateBackgroundImage();

    void ShowSideBarButton();

    void StopWidget();
    void StartWidget();

private slots:

    void SwitchVideoStream();
    void SwitchVideoCapture();
    void TakeScreenshot();
    void SwitchSendingCommands();

    void HideSideBarButton();

};


#endif
