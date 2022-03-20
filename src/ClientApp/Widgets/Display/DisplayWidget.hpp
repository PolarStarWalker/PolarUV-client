#ifndef CLIENT_DISPLAYWIDGET_HPP
#define CLIENT_DISPLAYWIDGET_HPP

#define WIN32_LEAN_AND_MEAN

#include "../WidgetResources.hpp"
#include <QOpenGLWidget>
#include <QPainter>
#include <QOpenGLPaintDevice>
#include <QTimer>
#include <QMainWindow>

#include "./VideoStream/VideoStream.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class DisplayWidget; }
QT_END_NAMESPACE

class DisplayWidget : public QOpenGLWidget {
Q_OBJECT

public:
    DisplayWidget(QMainWindow *mainWindow, WidgetResources &resources);

    ~DisplayWidget() override;

private:
    void initializeGL() override;

    void paintGL() override;

    void resizeGL(int w, int h) override;

    static void PaintYawIndicator(QPainter &painter, int width, int height, float yawAngle);

    static void PaintCentralIndicator(QPainter &painter, int width, int height, float rollAngle, float pitchAngle);

    static void PaintDepthIndicator(QPainter &painter, int width, int height, float depth, int valueRange);

    static void PaintTextInfo(QPainter &painter, int width, int height, std::array<int8_t, 4> calibration);

private:

    lib::processing::VideoStream stream_;

    WidgetResources &resources_;

    Ui::DisplayWidget *ui;

    std::unique_ptr<QTimer> updateTimer_;

    QPainter painter_;

    QImage placeholderImage_;

    QImage videoFrame_;

public slots:

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
