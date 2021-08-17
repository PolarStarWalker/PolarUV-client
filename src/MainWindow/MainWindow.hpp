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
#include <QThread>
#include <QShortcut>

#include "./DataStructs/DataStructs.hpp"
#include "./Protocols/Protocols.hpp"
#include "./Gamepad/Gamepad.hpp"

#define SERVER_IP "169.254.154.5"
// 192.168.1.50 - motov.s
// 169.254.154.5 - shushkov.d
#define COMMANDS_PORT 1999
#define SETTINGS_PORT 14322


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

constexpr char pipeline[] = "tcpclientsrc host=169.254.154.5 port=5000 ! gdpdepay ! rtph264depay ! decodebin ! autovideoconvert  ! appsink sync=false";


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

    void setupRendering();
    void setupButtons();
    void setupShortcuts();

    void placeWidgets();

    static QImage cvMatToQImage(const cv::Mat &mat);
    static QPixmap cvMatToPixmap(const cv::Mat &mat);

private slots:
    void on_MotorsNumberSpinBox_valueChanged(int value);
    void on_HandFreedomSpinBox_valueChanged(int value);

    void switchSendingCommands();
    void switchVideoStream();
    void takeScreenshot();
    void switchVideoCapture();
    void receiveRobotSettings();
    void sendRobotSettings();
    void loadClientSettings();
    void saveClientSettings();
    void refreshGamepads();
    void switchFullScreen();
    void hideTabBar();
    void showTabBar();

    void shortcutEsc();
    void shortcutTab();
    void shortcutF11();
    void shortcutB();

private:
    Ui::MainWindow *ui;

    VideoProtocol *_videoStream;
    CommandsProtocol *_commandsProtocol;

    bool _widgetsPlaced = false;

    QShortcut *_keyEsc = nullptr;
    QShortcut *_keyTab = nullptr;
    QShortcut *_keyF11 = nullptr;
    QShortcut *_keyB = nullptr;

};
#endif

