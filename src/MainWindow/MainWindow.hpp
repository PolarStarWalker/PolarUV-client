#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

#include <iostream>
#include <fstream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <iphlpapi.h>

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QThread>
#include <QShortcut>
#include <QGraphicsDropShadowEffect>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>

#include "./UI/Resources/MainWindowResources.hpp"

#include "./DataStructs/DataStructs.hpp"
#include "./Protocols/Protocols.hpp"
#include "./Gamepad/Gamepad.hpp"

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

    void SetupRendering();
    void SetupLocalization();
    void SetupButtons();
    void SetupShortcuts();

    static QImage cvMatToQImage(const cv::Mat &mat);
    static QPixmap cvMatToPixmap(const cv::Mat &mat);

    void PaintRollIndicator(float rollAngle, float sizeMultiplier); // Angle in degrees
    void PaintPitchIndicator(float pitchAngle, float sizeMultiplier);
    void PaintYawIndicator(float yawAngle, float sizeMultiplier);
    void PaintCompass(float angle, float sizeMultiplier);
    void PaintDepthIndicator(float depth, int32_t valueRange, float sizeMultiplier);

    void RawSwitchVideoStream();
    void RawSwitchVideoCapture();
    void RawTakeScreenshot();
    void RawSwitchSendingCommands();
    void RawSendRobotSettings();
    void RawReceiveRobotSettings();
    void RawSaveClientSettings();
    void RawLoadClientSettings();

private slots:
    void on_MotorsNumberSpinBox_valueChanged(int value);
    void on_HandFreedomSpinBox_valueChanged(int value);

    void MoveWidgets();
    void UpdateWidgets();

    void SwitchSendingCommands();
    void SwitchVideoStream();
    void TakeScreenshot();
    void SwitchVideoCapture();
    void SwitchToPage1();
    void SwitchToPage2();
    void SwitchToPage3();
    void ReceiveRobotSettings();
    void SendRobotSettings();
    void LoadClientSettings();
    void SaveClientSettings();
    void RefreshGamepads();
    void RefreshClientIps();
    void HideTabBar();
    void ShowTabBar();
    void ReleaseCode();
    void DebugCode();

    void shortcutEsc();
    void shortcutTab();
    void shortcutF11();
    void shortcutB();

private:
    Ui::MainWindow *ui;

    const MainWindowResources *_mainWindowResources;

    QTimer *_updateTimer;

    VideoProtocol *_videoStream;
    CommandsProtocol *_commandsProtocol;

    bool _isVideoFrame = false;   // For UpdateWidgets() function
    bool _isGreen = false;        // in order not to draw the same
    bool _isPause = false;        // images or text
    int32_t _oldEulerX = -1;      //
    int32_t _oldEulerY = -1;      //
    int32_t _oldEulerZ = -1;      //
    int32_t _oldDepth = -1;       //
    float oldVoltage = -1;        //
    QPixmap _oldVideoFrame{};     //
    int8_t _oldCalibrationArray[4]{}; //

    int32_t _pitchY = 0;

    std::chrono::time_point<std::chrono::system_clock> _oldTime{};
    uint8_t _fps = 0;

    QShortcut *_keyEsc = nullptr;
    QShortcut *_keyTab = nullptr;
    QShortcut *_keyF11 = nullptr;
    QShortcut *_keyB = nullptr;
};

std::list<std::string> GetClientIps();

#endif

