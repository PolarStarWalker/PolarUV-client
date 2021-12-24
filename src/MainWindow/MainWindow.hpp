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

#include <QOpenGLWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QThread>
#include <QShortcut>
#include <QGraphicsDropShadowEffect>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QGridLayout>

#include "./UI/Resources/MainWindowResources.hpp"

#include "./UI/Indicators/PitchIndicator.hpp"
#include "./UI/Indicators/YawIndicator.hpp"
#include "./UI/Indicators/DepthIndicator.hpp"

#include "./DataStructs/DataStructs.hpp"
#include "./Protocols/Protocols.hpp"
#include "./Gamepad/Gamepad.hpp"

#define COMMANDS_PORT 1999
#define SETTINGS_PORT 14322

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:

    void SetupRendering();

    void SetupButtons();

    void SetupAnimations();

    void SetupShortcuts();

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

private
    slots:
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

    void UpdateMotorsTable(int value);

    void UpdateHandTable(int value);

    void UpdateMaxSpeedSlider(const QString &string);

    void UpdateMaxSpeedEdit(int value);

    void shortcutEsc();

    void shortcutTab();

    void shortcutF11();

    void shortcutB();

private:
    Ui::MainWindow *ui;

    /// Singleton
    const MainWindowResources* _mainWindowResources;

    std::unique_ptr<QTimer> _updateTimer;

    std::unique_ptr<VideoProtocol> _videoStream;
    std::unique_ptr<CommandsProtocol> _commandsProtocol;

    std::unique_ptr<PitchIndicator> _pitchIndicator;
    std::unique_ptr<YawIndicator> _yawIndicator;
    std::unique_ptr<DepthIndicator> _depthIndicator;

    bool _isVideoFrame = false;       // For UpdateWidgets() function
    bool _isGreen = false;            // in order not to draw the same
    bool _isPause = false;            // images or text
    int32_t _oldEulerX = -1;          //
    int32_t _oldEulerY = -1;          //
    int32_t _oldEulerZ = -1;          //
    float _oldDepth = -1;             //
    float _oldVoltage = -1;           //
    QPixmap _oldVideoFrame{};         //
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

