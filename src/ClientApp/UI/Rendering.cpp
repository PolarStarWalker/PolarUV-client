#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::SetupRendering() {
    /// Setting the application icon
    setWindowIcon(this->_mainWindowResources.GetMainWindowIcon());

    /// Setting the tab icons
    ui->TabWidget->setTabIcon(0, _mainWindowResources.GetCameraIcon());
    ui->TabWidget->setTabIcon(1, _mainWindowResources.GetSettingsIcon());
    ui->TabWidget->setTabIcon(2, _mainWindowResources.GetCodeIcon());

    /// Setting the button icons
    ui->CommandsProtocolButton->setIcon(_mainWindowResources.GetRedStartIcon());
    ui->ShowTabBarButton->setIcon(_mainWindowResources.GetHamburgerIcon());
    ui->HideTabBarButton->setIcon(_mainWindowResources.GetHamburgerIcon());
    ui->VideoStreamButton->setIcon(_mainWindowResources.GetPlayIcon());
    ui->ScreenshotButton->setIcon(_mainWindowResources.GetScreenshotIcon());
    ui->VideoCaptureButton->setIcon(_mainWindowResources.GetWhiteVideoIcon());
    ui->RefreshClientIPsButton->setIcon(_mainWindowResources.GetReloadIcon());
    ui->RefreshGamepadsButton->setIcon(_mainWindowResources.GetReloadIcon());
    ui->ReleaseCodeButton->setIcon(_mainWindowResources.GetPlayIcon());
    ui->DebugCodeButton->setIcon(_mainWindowResources.GetBugIcon());

    /// Setting the gamepad button icons
    ui->AButtonLabel->setPixmap(_mainWindowResources.GetAButtonIcon());
    ui->BButtonLabel->setPixmap(_mainWindowResources.GetBButtonIcon());
    ui->XButtonLabel->setPixmap(_mainWindowResources.GetXButtonIcon());
    ui->YButtonLabel->setPixmap(_mainWindowResources.GetYButtonIcon());
    ui->DPadHorizontalLabel->setPixmap(_mainWindowResources.GetDPadHorizontalIcon());
    ui->DPadVerticalLabel->setPixmap(_mainWindowResources.GetDPadVerticalIcon());
    ui->LSHorizontalLabel->setPixmap(_mainWindowResources.GetLSHorizontalIcon());
    ui->LSVerticalLabel->setPixmap(_mainWindowResources.GetLSVerticalIcon());
    ui->LSPressLabel->setPixmap(_mainWindowResources.GetLSPressIcon());
    ui->RSHorizontalLabel->setPixmap(_mainWindowResources.GetRSHorizontalIcon());
    ui->RSVerticalLabel->setPixmap(_mainWindowResources.GetRSVerticalIcon());
    ui->RSPressLabel->setPixmap(_mainWindowResources.GetRSPressIcon());
    ui->LBLTButtonLabel->setPixmap(_mainWindowResources.GetLBLTButtonIcon());
    ui->RBRTButtonLabel->setPixmap(_mainWindowResources.GetRBRTButtonIcon());
    ui->BackButtonLabel->setPixmap(_mainWindowResources.GetBackButtonIcon());
    ui->MenuButtonLabel->setPixmap(_mainWindowResources.GetMenuButtonIcon());

    /// Setting the background
    QPixmap pixmap(10, 10);
    pixmap.fill(QColor::fromRgb(40, 40, 40));
    ui->CameraLabel->setPixmap(_mainWindowResources.GetBackground());
    ui->SettingsTabBackgroundLabel->setPixmap(pixmap);
    ui->CodeTabBackgroundLabel->setPixmap(pixmap);

    /// Setting a transparent background for some buttons
    ui->ShowTabBarButton->setStyleSheet("background-color: transparent");
    ui->HideTabBarButton->setStyleSheet("background-color: transparent");
    ui->VideoStreamButton->setStyleSheet("background-color: transparent");
    ui->ScreenshotButton->setStyleSheet("background-color: transparent");
    ui->VideoCaptureButton->setStyleSheet("background-color: transparent");

    /// Hiding the TabBar button
    ui->ShowTabBarButton->hide();

    /// Adding a shadow effect to some elements
    QWidget *elements[] = {
            // Labels
            ui->FPSLabel, ui->RollLabel, ui->PitchLabel, ui->CompassLabel, ui->DepthLabel, ui->YawLabel,
            ui->CalibrationLabel, ui->VoltageLabel, ui->ChargeLabel,
            // Buttons
            ui->ShowTabBarButton, ui->HideTabBarButton, ui->VideoStreamButton, ui->ScreenshotButton,
    };
    for (auto &element : elements) {
        auto *shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setOffset(0, 0);
        shadowEffect->setBlurRadius(5.0);
        shadowEffect->setColor(Qt::black);
        element->setGraphicsEffect(shadowEffect);
    }

    /// Adding a frames to indicators
/*#if DEBUG
    QLabel *indicators[] = {
            ui->RollLabel, ui->PitchLabel, ui->YawLabel, ui->CompassLabel, ui->DepthLabel,
    };
    for (auto &indicator : indicators) {
        indicator->setFrameShape(QFrame::Box);
    }
#endif*/

}

void MainWindow::MoveWidgets() {
    /// Changing the size of the TabWidget
    ui->TabWidget->setGeometry(ui->MainWidget->geometry());

    /// Changing the size of the SettingsStackedWidget
    ui->SettingsStackedWidget->setFixedWidth(ui->SettingsTab->width());
    ui->SettingsStackedWidget->setFixedHeight(ui->SettingsTab->height() - 100);

    /// Changing the size of the CameraLabel
    ui->CameraLabel->setGeometry(ui->MainTab->geometry());

    /// Changing the size of the backgrounds
    ui->SettingsTabBackgroundLabel->setGeometry(ui->SettingsTab->geometry());
    ui->CodeTabBackgroundLabel->setGeometry(ui->CodeTab->geometry());

    /// Changing the size of the CodeEdit
    ui->CodeEdit->setFixedWidth(ui->CodeTab->width() - 140);
    ui->CodeEdit->setFixedHeight(ui->CodeTab->height() - ui->OutputEdit->height() - 140 - 10);

    /// Changing the size of the OutputEdit
    ui->OutputEdit->setFixedWidth(ui->CodeTab->width() - 140);

    /// Moving the CommandsProtocol button
    int offset = 0; // Distance from the bottom edge of window
    int x = 0;
    ui->CommandsProtocolButton->move(x, ui->MainWidget->height() - ui->CommandsProtocolButton->height() - offset);

    /// Moving the HideTabBar button
    offset = 70; // Horizontal distance from the left edge of window
    ui->HideTabBarButton->move(offset, 0);

    /// Moving the ShowTabBar button
    ui->ShowTabBarButton->move(0, 0);

    /// Moving the roll label
    x = (ui->MainTab->width() - ui->RollLabel->width()) / 2;
    int y = (ui->MainTab->height() - ui->RollLabel->height()) / 2;
    ui->RollLabel->move(x, y);

    /// Moving the pitch label
    offset = 120;
    x = ui->RollLabel->x() - offset;
    y = (ui->MainTab->height() - ui->PitchLabel->height()) / 2;
    ui->PitchLabel->move(x, y);
    this->_pitchIndicator->move(x,y);

    /// Moving the yaw label
    x = (ui->MainTab->width() - ui->YawLabel->width()) / 2;
    ui->YawLabel->move(x, 0);
    this->_yawIndicator->move(x, 0);

    /// Moving the depth label
    offset = 120;
    x = ui->RollLabel->x() + ui->RollLabel->width() - ui->DepthLabel->width() + offset;
    y = (ui->MainTab->height() - ui->DepthLabel->height()) / 2;
    ui->DepthLabel->move(x, y);
    this->_depthIndicator->move(x, y);

    /// Moving the compass label
    x = ui->MainTab->width() - ui->CompassLabel->width();
    y = ui->MainTab->height() - ui->CompassLabel->height();
    ui->CompassLabel->move(x, y);

    /// Moving the calibration label
    offset = 5; // Distance from the left edge of window
    y = ui->MainTab->height() - ui->CalibrationLabel->height();
    ui->CalibrationLabel->move(offset, y - offset);

    /// Moving the voltage label
    y = ui->CalibrationLabel->y() - ui->VoltageLabel->height();
    ui->VoltageLabel->move(offset, y);

    /// Moving the charge label
    y = ui->VoltageLabel->y() - ui->ChargeLabel->height();
    ui->ChargeLabel->move(offset, y);

    /// Moving the VideoStream button
    offset = 10; // Distance from the bottom edge of window
    x = (ui->MainTab->width() / 2) - (ui->VideoStreamButton->width() / 2);
    y = ui->MainTab->height() - ui->VideoStreamButton->height() - offset;
    ui->VideoStreamButton->move(x, y);

    /// Moving the VideoCapture button
    offset = 50; // Distance from the VideoStream button
    x = ui->VideoStreamButton->x() + ui->VideoStreamButton->width() + offset;
    y = ui->VideoStreamButton->y();
    ui->VideoCaptureButton->move(x, y);

    /// Moving the Screenshot button
    offset = 50; // Distance from the VideoStream button
    x = ui->VideoStreamButton->x() - ui->ScreenshotButton->width() - offset;
    y = ui->VideoStreamButton->y();
    ui->ScreenshotButton->move(x, y);

    /// Moving the fps label
    x = ui->MainTab->width() - ui->FPSLabel->width();
    ui->FPSLabel->move(x, 0);

    /// Moving the ReleaseCode button
    offset = 10; // Vertical distance from the OutputEdit
    x = ui->OutputEdit->x() + ui->OutputEdit->width() - ui->ReleaseCodeButton->width();
    y = ui->OutputEdit->y() + ui->OutputEdit->height() + offset;
    ui->ReleaseCodeButton->move(x, y);

    /// Moving the DebugCode button
    offset = 10; // Horizontal distance from the ReleaseCode button
    x = ui->ReleaseCodeButton->x() - ui->DebugCodeButton->width() - offset;
    y = ui->ReleaseCodeButton->y();
    ui->DebugCodeButton->move(x, y);

    /// Moving the ProgressBar frame
    offset = 10; // Horizontal distance from the DebugCode button
    x = ui->DebugCodeButton->x() - ui->ProgressBarFrame->width() - offset;
    y = ui->DebugCodeButton->y();
    ui->ProgressBarFrame->move(x, y);

    /// Moving the ProgressBar
    x = ui->ProgressBarFrame->x() + ui->ProgressBarFrame->width() / 2 - ui->ProgressBar->width() / 2;
    y = ui->ProgressBarFrame->y() + ui->ProgressBarFrame->height() / 2 - ui->ProgressBar->height() / 2;
    ui->ProgressBar->move(x, y);

    /// Moving the SettingsPageSelector widget
    offset = 20; // Vertical distance from the top edge of window
    x = (ui->SettingsTab->width() / 2) - (ui->SettingsPageSelectorWidget->width() / 2);
    y = offset;
    ui->SettingsPageSelectorWidget->move(x, y);

    /// Moving the MotorsSettings widget
    offset = 35; // Horizontal distance between widgets
    x = (ui->SettingsStackedWidget->width() - (ui->MotorsSettingsWidget->width()
                                               + ui->HandSettingsWidget->width() + offset)) / 2;
    y = (ui->SettingsStackedWidget->height() - ui->MotorsSettingsWidget->height()) / 2;
    ui->MotorsSettingsWidget->move(x, y);

    /// Moving the HandSettings widget
    x = ui->MotorsSettingsWidget->x() + ui->MotorsSettingsWidget->width() + offset;
    ui->HandSettingsWidget->move(x, y);

    /// Moving the RobotSettings widget
    x = (ui->tab->width() - this->_robotSettingWidget->width()) / 2;
    y = (ui->tab->height() - this->_robotSettingWidget->height()) / 2;
    this->_robotSettingWidget->move(x, y);

    /// Moving the KeyAssignments widget
    offset = 35; // Horizontal distance between widgets
    x = (ui->SettingsStackedWidget->width() - (ui->KeyAssignmentsWidget->width()
                                               + ui->ConnectionSettingsWidget->width() + offset)) / 2;
    y = (ui->SettingsStackedWidget->height() - ui->KeyAssignmentsWidget->height()) / 2;
    ui->KeyAssignmentsWidget->move(x, y);

    /// Moving the GamepadTest widget
    x = ui->KeyAssignmentsWidget->x() + ui->KeyAssignmentsWidget->width() + offset;
    ui->ConnectionSettingsWidget->move(x, y);

    /// Moving the UISettings widget
    x = (ui->SettingsStackedWidget->width() - ui->UISettingsWidget->width()) / 2;
    y = (ui->SettingsStackedWidget->height() - ui->UISettingsWidget->height()) / 2;
    ui->UISettingsWidget->move(x, y);

    /// Moving the OutputEdit
    offset = 10; // Vertical distance from the CodeEdit
    ui->OutputEdit->move(ui->OutputEdit->x(), ui->CodeEdit->y() + ui->CodeEdit->height() + offset);

    /// Moving the MotorsSettings label
    x = ui->MotorsSettingsWidget->x() + ui->MotorsSettingsWidget->width() / 2 - ui->MotorsSettingsLabel->width() / 2;
    y = ui->MotorsSettingsWidget->y() - ui->MotorsSettingsLabel->height() / 2;
    ui->MotorsSettingsLabel->move(x, y);

    /// Moving the HandSettings label
    x = ui->HandSettingsWidget->x() + ui->HandSettingsWidget->width() / 2 - ui->HandSettingsLabel->width() / 2;
    y = ui->HandSettingsWidget->y() - ui->HandSettingsLabel->height() / 2;
    ui->HandSettingsLabel->move(x, y);

    /// Moving the KeyAssignments label
    x = ui->KeyAssignmentsWidget->x() + ui->KeyAssignmentsWidget->width() / 2 - ui->KeyAssignmentsLabel->width() / 2;
    y = ui->KeyAssignmentsWidget->y() - ui->KeyAssignmentsLabel->height() / 2;
    ui->KeyAssignmentsLabel->move(x, y);

    /// Moving the ConnectionSettings label
    x = ui->ConnectionSettingsWidget->x() + ui->ConnectionSettingsWidget->width() / 2 - ui->ConnectionSettingsLabel->width() / 2;
    y = ui->ConnectionSettingsWidget->y() - ui->ConnectionSettingsLabel->height() / 2;
    ui->ConnectionSettingsLabel->move(x, y);

    /// Moving the UISettings label
    x = ui->UISettingsWidget->x() + ui->UISettingsWidget->width() / 2 - ui->UISettingsLabel->width() / 2;
    y = ui->UISettingsWidget->y() - ui->UISettingsLabel->height() / 2;
    ui->UISettingsLabel->move(x, y);

    /// Moving the CodeEdit Label
    x = ui->CodeEdit->x() + ui->CodeEdit->width() / 2 - ui->CodeEditLabel->width() / 2;
    y = ui->CodeEditLabel->y();
    ui->CodeEditLabel->move(x, y);
}

void MainWindow::UpdateWidgets() {

    this->MoveWidgets();

    /// Painting a video frame or placeholder image
    if (this->_videoStream->IsStreamOnline()) {
        QPixmap currentVideoFrame(_videoStream->GetPixmap());
        if (currentVideoFrame != this->_oldVideoFrame) {
            ui->CameraLabel->setPixmap(currentVideoFrame);
        }
        this->_isVideoFrame = true;
    } else if (!this->_videoStream->IsStreamOnline() && _isVideoFrame) {
        ui->CameraLabel->setPixmap(_mainWindowResources.GetBackground());
        this->_isVideoFrame = false;
    }

    /// Selecting the color of the CommandsProtocol button
    if (this->_commandsProtocol->IsStreamOnline() && !this->_isGreen) {
        ui->CommandsProtocolButton->setIcon(_mainWindowResources.GetGreenStartIcon());
        this->_isGreen = true;
    } else if (!this->_commandsProtocol->IsStreamOnline() && this->_isGreen) {
        ui->CommandsProtocolButton->setIcon(_mainWindowResources.GetRedStartIcon());
        this->_isGreen = false;
    }

    /// Selecting the color of the VideoStream button
    if (_videoStream->IsStreamOnline() && !this->_isPause) {
        ui->VideoStreamButton->setIcon(_mainWindowResources.GetPauseIcon());
        this->_isPause = true;
    } else if (!_videoStream->IsStreamOnline() && this->_isPause) {
        ui->VideoStreamButton->setIcon(_mainWindowResources.GetPlayIcon());
        this->_isPause = false;
    }

    TelemetryStruct telemetryStruct = this->_commandsProtocol->GetTelemetryStruct();

    /// Painting the pitch indicator if angle changed
    float currentEulerY = telemetryStruct.Rotation[TelemetryStruct::Y];
    if ((int32_t) currentEulerY != this->_oldEulerY) {
        //this->PaintPitchIndicator(currentEulerY, 1);
        this->_pitchIndicator->update();
        this->_oldEulerY = (int32_t) currentEulerY;
    }

    /// Painting the roll indicator if angle changed (pitch must be painted before)
    float currentEulerX = telemetryStruct.Rotation[TelemetryStruct::X];
    if ((int32_t) currentEulerX != this->_oldEulerX) {
        this->PaintRollIndicator(currentEulerX, 1);
        this->_oldEulerX = (int32_t) currentEulerX;
    }

    /// Painting the yaw indicator and compass if angle changed
    float currentEulerZ = telemetryStruct.Rotation[TelemetryStruct::Z];
    if ((int32_t) currentEulerZ != this->_oldEulerZ) {
        //this->PaintYawIndicator(currentEulerZ, 1);
        this->_yawIndicator->update();
        this->PaintCompass(currentEulerZ, 1);
        this->_oldEulerZ = (int32_t) currentEulerZ;
    }

    /// Painting the depth indicator
    float currentDepth = telemetryStruct.Depth;
    if (currentDepth != this->_oldDepth) {
        //this->PaintDepthIndicator(currentDepth, 10, 1);
        this->_depthIndicator->update();
        this->_oldDepth = currentDepth;
    }

    /// Printing calibration data
    int8_t currentCalibrationArray[4]{
            telemetryStruct.MotionCalibration[0],
            telemetryStruct.MotionCalibration[1],
            telemetryStruct.MotionCalibration[2],
            telemetryStruct.MotionCalibration[3]
    };
    if ((currentCalibrationArray[0] != this->_oldCalibrationArray[0]) ||
        (currentCalibrationArray[1] != this->_oldCalibrationArray[1]) ||
        (currentCalibrationArray[2] != this->_oldCalibrationArray[2]) ||
        (currentCalibrationArray[3] != this->_oldCalibrationArray[3])) {
        ui->CalibrationLabel->setText(QString("Калибровка: [") +
                                      QString::number(telemetryStruct.MotionCalibration[0]) + QString(", ") +
                                      QString::number(telemetryStruct.MotionCalibration[1]) + QString(", ") +
                                      QString::number(telemetryStruct.MotionCalibration[2]) + QString(", ") +
                                      QString::number(telemetryStruct.MotionCalibration[3]) + QString("]"));
        this->_oldCalibrationArray[0] = currentCalibrationArray[0];
        this->_oldCalibrationArray[1] = currentCalibrationArray[1];
        this->_oldCalibrationArray[2] = currentCalibrationArray[2];
        this->_oldCalibrationArray[3] = currentCalibrationArray[3];
    }

    /// Printing voltage data
    float currentVoltage = telemetryStruct.BatteryVoltage;
    if (currentVoltage != this->_oldVoltage) {
        ui->VoltageLabel->setText(QString("Напряжение: ") + QString::number(currentVoltage) + QString(" В"));
    }

    /// Counting FPS - printing every 1 sec
    ++_fps;
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() -
                                                         this->_oldTime) >= std::chrono::seconds{1}) {
        this->_oldTime = std::chrono::high_resolution_clock::now();
        ui->FPSLabel->setText(QString("FPS: ") + QString::number(this->_fps));
        this->_fps = 0;
    }
}

void MainWindow::PaintRollIndicator(float rollAngle, float sizeMultiplier) {
    QPixmap pixmap(ui->RollLabel->width(), ui->RollLabel->height());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::white, 3));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(pixmap.width() / 2, pixmap.height() / 2);

    QRect boundingRect(-40,
                       (ui->RollLabel->height() / 2) - 35,
                       80,
                       30);
    painter.setPen(QPen(Qt::white, 2));
    painter.setFont(QFont("Times", 16));
    painter.drawRect(boundingRect);
    painter.drawText(boundingRect, Qt::AlignCenter, QString::number((int32_t) rollAngle) + QString("°"));

    /// Painting static indicator
    painter.setPen(QPen(Qt::white, 3));
    painter.drawEllipse(QPoint(0, 0), 5, 5);
    painter.drawArc(QRect(-15, -15, 30, 30), 0, -180 * 16);
    painter.drawLine(16, -1, 270, 0);
    painter.drawLine(-16, -1, -270, 0);

    /// Painting dynamic indicator
    painter.rotate(rollAngle);
    painter.setPen(QPen(Qt::white, 3));
    painter.drawEllipse(QPoint(0, this->_pitchY), 5, 5);
    painter.setPen(QPen(Qt::white, 3, Qt::PenStyle::DashLine));
    painter.drawArc(QRect(-15, this->_pitchY - 15, 30, 30), 0, -180 * 16);
    // Vertical line
    if (this->_pitchY < 0) painter.drawLine(0, -5, 0, this->_pitchY + 5);
    else if (this->_pitchY > 0) painter.drawLine(0, 5, 0, this->_pitchY - 5);
    // Horizontal lines
    painter.drawLine(-270, this->_pitchY, -15, this->_pitchY);
    painter.drawLine(15, this->_pitchY, 270, this->_pitchY);

    ui->RollLabel->setPixmap(pixmap);
}

void MainWindow::PaintPitchIndicator(float pitchAngle, float sizeMultiplier) {
    QPixmap pixmap(ui->PitchLabel->width(), ui->PitchLabel->height());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::white, 3));
    painter.setRenderHint(QPainter::Antialiasing);

    // Scale
    painter.drawLine(50, 5, 103, 5);
    painter.drawLine(105, 6, 119, 20);
    painter.drawLine(120, 22, 120,
                     ui->PitchLabel->height() - 22);
    painter.drawLine(119,
                     ui->PitchLabel->height() - 20,
                     105,
                     ui->PitchLabel->height() - 6);
    painter.drawLine(103,
                     ui->PitchLabel->height() - 5,
                     50,
                     ui->PitchLabel->height() - 5);

    painter.translate(425, 320); // Center of screen
    auto y = ((int32_t) pitchAngle);
    if (y < 0) y = 0;
    else if ((0 <= y) && (y < 90)) y = y * 3; // Смотрит вперед, верхняя полусфера
    else if ((90 <= y) && (y < 180)) y = (y - 180) * 3; // Смотрит назад, верхняя полусфера
    else if ((180 <= y) && (y < 270)) y = (y - 180) * 3; // Смотрит назад, нижняя полусфера
    else if ((270 <= y) && (y <= 360)) y = (y - 360) * 3; // Смотрит вперед, нижняя полусфера
    else if (y > 360) y = 360;

    painter.setPen(QPen(Qt::white, 2));
    painter.setFont(QFont("Times", 16));

    /// Painting the scale and its values
    for (int32_t i = 270; i >= -270; i -= 90) {
        painter.drawLine(-330, i, -310, i);
        if (abs(y - i) >= 30) { // If the arrow is far enough from current scale value
            QRect boundingRect(-395, i - 15, 60, 30);
            painter.drawText(boundingRect, Qt::AlignCenter, QString::number(i / 3) + QString("°"));
        }
    }

    /// Painting the arrow
    painter.drawLine(-341, y, -359, y - 15);
    painter.drawLine(-341, y, -359, y + 15);

    /// Painting the bounding rect
    QRect boundingRect(-420, y - 15, 60, 30);
    painter.setPen(QPen(Qt::white, 2));
    painter.drawLine(-420, y - 15, -360, y - 15);
    painter.drawLine(-420, y + 15, -360, y + 15);
    painter.drawLine(-420, y - 15, -420, y + 15);
    painter.drawText(boundingRect, Qt::AlignCenter, QString::number((int32_t) y / 3) + QString("°"));

    this->_pitchY = y;

    ui->PitchLabel->setPixmap(pixmap);
}

void MainWindow::PaintYawIndicator(float yawAngle, float sizeMultiplier) {
    QPixmap pixmap(ui->YawLabel->width(), ui->YawLabel->height());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::white, 3));
    painter.setRenderHint(QPainter::Antialiasing);

    /// NON-MAGIC NUMBERS
    constexpr int32_t borderOffsetX = 15;
    constexpr int32_t borderOffsetY1 = 45;
    constexpr int32_t borderOffsetY2 = 60;
    constexpr int32_t valueRectWidth = 60;
    constexpr int32_t valueRectHeight = 30;
    constexpr int32_t step = 15;
    constexpr int32_t distance = 60;

    painter.drawLine(1,
                     0,
                     1,
                     ui->YawLabel->height() - borderOffsetY2);
    painter.drawLine(0,
                     ui->YawLabel->height() - borderOffsetY2,
                     borderOffsetX - 1,
                     ui->YawLabel->height() - borderOffsetY1 - 1);
    painter.drawLine(borderOffsetX,
                     ui->YawLabel->height() - borderOffsetY1,
                     ui->YawLabel->width() - borderOffsetX,
                     ui->YawLabel->height() - borderOffsetY1);
    painter.drawLine(ui->YawLabel->width() - borderOffsetX + 1,
                     ui->YawLabel->height() - borderOffsetY1 - 1,
                     ui->YawLabel->width(),
                     ui->YawLabel->height() - borderOffsetY2);
    painter.drawLine(ui->YawLabel->width() - 1,
                     ui->YawLabel->height() - borderOffsetY2,
                     ui->YawLabel->width() - 1,
                     0);

    /// Painting center line
    painter.translate(ui->YawLabel->width() / 2, 0);
    painter.drawLine(0, ui->YawLabel->height() - borderOffsetY1 - 1, 0, ui->YawLabel->height() - borderOffsetY2);

    /// Painting angle
    QRect angleRect(-40,
                    ui->YawLabel->height() - 35,
                    80,
                    30);
    painter.setPen(QPen(Qt::white, 2));
    painter.drawRect(angleRect);
    painter.setPen(QPen(Qt::white, 3));
    painter.setFont(QFont("Times", 16));
    painter.drawText(angleRect, Qt::AlignCenter, QString::number((int32_t) yawAngle) + QString("°"));

    /// Painting center value
    int32_t valueOffset = ((int32_t) yawAngle) % step;
    int32_t scaleOffset = (valueOffset * (valueRectWidth + distance)) / step;
    painter.translate(-scaleOffset, 0);
    QRect boundingRect(-(valueRectWidth / 2),
                       (ui->YawLabel->height() - borderOffsetY2 - valueRectHeight) / 2,
                       valueRectWidth,
                       valueRectHeight);
    int32_t centerValue = ((int32_t) yawAngle) - valueOffset;
    painter.drawText(boundingRect, Qt::AlignCenter, QString::number(centerValue));

    /// Painting left values
    int32_t currentX = (ui->YawLabel->width() / 2) - scaleOffset;
    int8_t translationNumber = 1;
    while (currentX >= ((valueRectWidth + distance))) {
        painter.translate(-(valueRectWidth + distance), 0);
        QRect rect(-(valueRectWidth / 2),
                   (ui->YawLabel->height() - borderOffsetY2 - valueRectHeight) / 2,
                   valueRectWidth,
                   valueRectHeight);
        int32_t value = (((int32_t) yawAngle) - valueOffset) - (step * translationNumber);
        if (value < 0) value = 360 + value;
        else if (value > 360) value = value - 360;
        painter.drawText(rect, Qt::AlignCenter, QString::number(value));
        translationNumber++;
        currentX -= valueRectWidth;
    }

    /// Translating back to the center
    for (size_t i = 0; i < translationNumber - 1; i++) {
        painter.translate(valueRectWidth + distance, 0);
        currentX += valueRectWidth;
    }
    translationNumber = 1;

    /// Painting right values
    while (currentX <= (ui->YawLabel->width() - ((valueRectWidth + distance)))) {
        painter.translate(valueRectWidth + distance, 0);
        QRect rect(-(valueRectWidth / 2),
                   (ui->YawLabel->height() - borderOffsetY2 - valueRectHeight) / 2,
                   valueRectWidth,
                   valueRectHeight);
        int32_t value = (((int32_t) yawAngle) - valueOffset) + (step * translationNumber);
        if (value < 0) value = 360 - value;
        else if (value == 360) value = 0;
        else if (value > 360) value = value - 360;
        painter.drawText(rect, Qt::AlignCenter, QString::number(value));
        translationNumber++;
        currentX += valueRectWidth;
    }

    ui->YawLabel->setPixmap(pixmap);
}

void MainWindow::PaintCompass(float angle, float sizeMultiplier) {
    ui->CompassLabel->setGeometry(ui->CompassLabel->x(),
                                  ui->CompassLabel->y(),
                                  (int32_t) (300.0f * sizeMultiplier),
                                  (int32_t) (300.0f * sizeMultiplier));
    QPixmap pixmap(ui->CompassLabel->width(), ui->CompassLabel->height());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::white, 3));
    painter.setFont(QFont("Times", (int32_t) (16 * sizeMultiplier)));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(pixmap.width() / 2, pixmap.height() / 2);

    /// Painting the arrow
    painter.drawLine(QPointF(0, -0), QPointF(0, (int32_t) (-70 * sizeMultiplier)));

    /// Painting the angle
//    QRect boundingRect((int32_t) (-40 * sizeMultiplier),
//                       (int32_t) (10 * sizeMultiplier),
//                       (int32_t) (80 * sizeMultiplier),
//                       (int32_t) (30 * sizeMultiplier));
//    painter.setPen(QPen(Qt::white, 2));
//    painter.drawRect(boundingRect);
//    painter.setPen(QPen(Qt::white, 3));
//    painter.drawText(boundingRect, Qt::AlignCenter, QString::number((int32_t) angle) + QString("°"));

    /// Painting the circle
    painter.drawEllipse(QPoint(0, 0),
                        (int32_t) (110 * sizeMultiplier),
                        (int32_t) (110 * sizeMultiplier));

    /// Painting the north line
    painter.rotate(-angle);
    painter.drawLine(QPointF(0, (int32_t) (-80 * sizeMultiplier)),
                     QPointF(0, (int32_t) (-110 * sizeMultiplier)));

    /// Painting the letters
    painter.drawText((int32_t) (-8 * sizeMultiplier), (int32_t) (-120 * sizeMultiplier), "С");
    painter.drawText((int32_t) (-8 * sizeMultiplier), (int32_t) (140 * sizeMultiplier), "Ю");
    painter.drawText((int32_t) (-135 * sizeMultiplier), (int32_t) (10 * sizeMultiplier), "З");
    painter.drawText((int32_t) (120 * sizeMultiplier), (int32_t) (10 * sizeMultiplier), "В");

    /// Painting the other lines
    for (ssize_t i = 1; i < 16; i++) {
        painter.rotate(22.5);
        if (i % 2 == 0) {
            painter.setPen(QPen(Qt::white, 3));
            painter.drawLine(QPointF(0, (int32_t) (-80 * sizeMultiplier)),
                             QPointF(0, (int32_t) (-110 * sizeMultiplier)));
        } else {
            painter.setPen(QPen(Qt::white, 2));
            painter.drawLine(QPointF(0, (int32_t) (-90 * sizeMultiplier)),
                             QPointF(0, (int32_t) (-110 * sizeMultiplier)));
        }
    }

    ui->CompassLabel->setPixmap(pixmap);
}

void MainWindow::PaintDepthIndicator(float depth, int32_t valueRange, float sizeMultiplier) {
    QPixmap pixmap(ui->DepthLabel->width(), ui->DepthLabel->height());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::white, 3));
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawLine(680, 5, 627, 5);
    painter.drawLine(625, 6, 611, 20);
    painter.drawLine(610, 22, 610,
                     ui->DepthLabel->height() - 22);
    painter.drawLine(611,
                     ui->DepthLabel->height() - 20,
                     625,
                     ui->DepthLabel->height() - 6);
    painter.drawLine(627,
                     ui->DepthLabel->height() - 5,
                     680,
                     ui->DepthLabel->height() - 5);

    painter.translate(305, 320);

    painter.setPen(QPen(Qt::white, 2));
    painter.setFont(QFont("Times", 16));

    /// Painting the scale and its values
    int32_t j = 0;
    for (int32_t i = -270; i <= 270; i += 108) {
        painter.drawLine(310, i, 330, i);
        if (abs((int32_t) depth - i) >= 30) { // if the arrow is far enough from current scale value
            QRect boundingRect(335, i - 15, 60, 30);
            painter.drawText(boundingRect, Qt::AlignCenter, QString::number(j) + QString("м"));
        }
        j = j + (valueRange / 5);
    }

    ui->DepthLabel->setPixmap(pixmap);
}