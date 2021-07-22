#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

#include <QMainWindow>
#include <QThread>

#include "./DataProtocol/DataProtocol.hpp"
#include "./VideoProcessing/VideoProcessing.hpp"
#include "../DataStruct.hpp"

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

private slots:
    void on_CommandsProtocolButton_clicked();
    void on_GamepadButton_clicked();
    void on_VideoStreamButton_clicked();

private:
    Ui::MainWindow *ui;

    VideoProcessing _stream;
    DataProtocol *_dataProtocol;
    QThread *_dataProtocolThread;
};
#endif

