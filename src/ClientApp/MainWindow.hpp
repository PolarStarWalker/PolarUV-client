#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./Widgets/Widgets.hpp"

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
#include <QResizeEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:

    void SetupRendering();

    void SetupSlots();

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

public slots:

    void Launch(const QString& robotIP, const QString& clientIP, int gamepadID);

    void LaunchDebug();

    void ShowSideBar();

private slots:

    void SwitchToPage1();
    void SwitchToPage2();
    void SwitchToPage2_1();
    void SwitchToPage2_2();
    void SwitchToPage2_3();
    void SwitchToPage3();
    void SwitchToPage4();

    void SwitchSideBarButton(int currentIndex);

    void HideSideBar();

private:

    Ui::MainWindow *ui;

//    std::unique_ptr<QTimer> _updateTimer;

//    std::unique_ptr<PitchIndicator> _pitchIndicator;
//    std::unique_ptr<YawIndicator> _yawIndicator;
//    std::unique_ptr<DepthIndicator> _depthIndicator;

    std::unique_ptr<AutorizationWidget> autorizationWidget_;
    std::unique_ptr<DisplayWidget> displayWidget_;
    std::unique_ptr<RobotSettingsWidget> robotSettingsWidget_;
    std::unique_ptr<ClientSettingsWidget> controlSettingsWidget_;
    std::unique_ptr<PythonEnvironmentWidget> pythonIDEWidget_;

    /// ToDo: shushkov.d переделать
//    bool _isVideoFrame = false;
//    bool _isGreen = false;
//    bool _isPause = false;
//    int32_t _oldEulerX = -1;
//    int32_t _oldEulerY = -1;
//    int32_t _oldEulerZ = -1;
//    float _oldDepth = -1;
//    float _oldVoltage = -1;
//    QPixmap _oldVideoFrame{};
//    int8_t _oldCalibrationArray[4]{};
//
//    int32_t _pitchY = 0;
//
//    std::chrono::time_point<std::chrono::system_clock> _oldTime{};
//    uint8_t _fps = 0;
};

#endif

