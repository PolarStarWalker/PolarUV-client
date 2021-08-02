#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <fstream>
#include <windows.h>
#include <thread>
#include <chrono>

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QWindowStateChangeEvent>
#include <QThread>

#include "./Protocols/Protocols.hpp"
#include "./Gamepad/Gamepad.hpp"

#define SERVER_IP "169.254.154.5"
// 192.168.1.50 - motov.s
// 169.254.154.5 - shushkov.d
#define PORT 1999

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

constexpr char pipeline[] = "tcpclientsrc host=192.168.1.50 port=5000 ! gdpdepay ! rtph264depay ! decodebin ! autovideoconvert  ! appsink sync=false";


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void placeWidgets();

private slots:
    void on_CommandsProtocolButton_clicked();
    void on_GamepadButton_clicked();
    void on_VideoStreamButton_clicked();

    void on_FullScreenButton_clicked();

    void on_MotorsQuantitySpinBox_valueChanged(int value);
    void on_HandFreedomSpinBox_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    bool _widgetsPlaced;

    VideoProtocol _video;
    CommandsProtocol *_commandsProtocol;
    Control::Gamepad *_gamepad;
};
#endif

