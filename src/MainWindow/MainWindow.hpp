#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <fstream>
#include <windows.h>
#include <thread>
#include <chrono>

#include <QMainWindow>
#include <QMessageBox>
#include <QWindowStateChangeEvent>
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

protected:
    void resizeEvent(QResizeEvent *event); // Вызывается при изменении размеров окна
    void changeEvent(QEvent *event); // Вызывается при любом изменении свойств окна

private slots:
    /// Функциональные кнопки
    void on_CommandsProtocolButton_clicked();
    void on_GamepadButton_clicked();
    void on_VideoStreamButton_clicked();

    /// Интерфейсные кнопки
    void on_WindowCloseButton_clicked();
    void on_WindowMinimizeButton_clicked();

    /// Интерфейсные функции
    void on_MotorsQuantitySpinBox_valueChanged(int value);
    void on_HandFreedomSpinBox_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    VideoProcessing _stream;
    DataProtocol *_dataProtocol;
    QThread *_dataProtocolThread;
};
#endif

