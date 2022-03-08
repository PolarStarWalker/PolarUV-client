#ifndef CLIENT_DISPLAYWIDGET_HPP
#define CLIENT_DISPLAYWIDGET_HPP

#define WIN32_LEAN_AND_MEAN

#include "../WidgetResources.hpp"
#include <QWidget>
#include <QPainter>
#include <QOpenGLPaintDevice>
#include <QTimer>
#include <QMainWindow>

#include "./VideoStream/VideoStream.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class DisplayWidget; }
QT_END_NAMESPACE

class DisplayWidget : public QWidget {
Q_OBJECT

public:
    DisplayWidget(QMainWindow *mainWindow, WidgetResources &resources);

    ~DisplayWidget() override;

    void SetGamepadID(int id) { this->GamepadID = id; };

private:

    lib::processing::VideoStream stream_;

    WidgetResources &resources_;

    Ui::DisplayWidget *ui;

    std::unique_ptr<QTimer> updateTimer_;

    QOpenGLPaintDevice paintDevice_ = QOpenGLPaintDevice(1920, 1080);
    QPainter painter_;

    QImage placeholderImage_;
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
