#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <fstream>
#include <windows.h>
#include <thread>
#include <chrono>

#include <QMainWindow>

#include "./DataProtocol/DataProtocol.hpp"
#include "../DataStruct.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

constexpr char pipeline[] = "udpsrc port=5000 ! gdpdepay ! rtph264depay ! decodebin ! autovideoconvert  ! appsink sync=false";


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void StartVideoCapture();
    void StopVideoCapture();

private slots:
    void on_socketConnectButton_clicked();

private:
    Ui::MainWindow *ui;

    cv::VideoCapture _stream;
    DataProtocol _dataProtocol;
};
#endif

