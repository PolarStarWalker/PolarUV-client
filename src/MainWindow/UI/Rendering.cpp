#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::SetupRendering() {
    /// Setting the application icon
    setWindowIcon(this->_mainWindowResources->GetMainWindowIcon());

    /// Setting the tab icons
    ui->TabWidget->setTabIcon(0, this->_mainWindowResources->GetCameraIcon());
    ui->TabWidget->setTabIcon(1, this->_mainWindowResources->GetSettingsIcon());
    ui->TabWidget->setTabIcon(2, this->_mainWindowResources->GetCodeIcon());

    /// Setting the button icons
    ui->CommandsProtocolButton->setIcon(this->_mainWindowResources->GetRedStartIcon());
    ui->ShowTabBarButton->setIcon(this->_mainWindowResources->GetHamburgerIcon());
    ui->HideTabBarButton->setIcon(this->_mainWindowResources->GetHamburgerIcon());
    ui->VideoStreamButton->setIcon(this->_mainWindowResources->GetPlayIcon());
    ui->ScreenshotButton->setIcon(this->_mainWindowResources->GetScreenshotIcon());
    ui->VideoCaptureButton->setIcon(this->_mainWindowResources->GetWhiteVideoIcon());
    ui->RefreshClientIPsButton->setIcon(this->_mainWindowResources->GetReloadIcon());
    ui->RefreshGamepadsButton->setIcon(this->_mainWindowResources->GetReloadIcon());
    ui->ReleaseCodeButton->setIcon(this->_mainWindowResources->GetPlayIcon());
    ui->DebugCodeButton->setIcon(this->_mainWindowResources->GetBugIcon());

    /// Setting the gamepad button icons
    ui->AButtonLabel->setPixmap(this->_mainWindowResources->GetAButtonIcon());
    ui->BButtonLabel->setPixmap(this->_mainWindowResources->GetBButtonIcon());
    ui->XButtonLabel->setPixmap(this->_mainWindowResources->GetXButtonIcon());
    ui->YButtonLabel->setPixmap(this->_mainWindowResources->GetYButtonIcon());
    ui->DPadHorizontalLabel->setPixmap(this->_mainWindowResources->GetDPadHorizontalIcon());
    ui->DPadVerticalLabel->setPixmap(this->_mainWindowResources->GetDPadVerticalIcon());
    ui->LSHorizontalLabel->setPixmap(this->_mainWindowResources->GetLSHorizontalIcon());
    ui->LSVerticalLabel->setPixmap(this->_mainWindowResources->GetLSVerticalIcon());
    ui->LSPressLabel->setPixmap(this->_mainWindowResources->GetLSPressIcon());
    ui->RSHorizontalLabel->setPixmap(this->_mainWindowResources->GetRSHorizontalIcon());
    ui->RSVerticalLabel->setPixmap(this->_mainWindowResources->GetRSVerticalIcon());
    ui->RSPressLabel->setPixmap(this->_mainWindowResources->GetRSPressIcon());
    ui->LBLTButtonLabel->setPixmap(this->_mainWindowResources->GetLBLTButtonIcon());
    ui->RBRTButtonLabel->setPixmap(this->_mainWindowResources->GetRBRTButtonIcon());
    ui->BackButtonLabel->setPixmap(this->_mainWindowResources->GetBackButtonIcon());
    ui->MenuButtonLabel->setPixmap(this->_mainWindowResources->GetMenuButtonIcon());

    /// Setting the background
    QPixmap pixmap(10, 10);
    pixmap.fill(QColor::fromRgb(50, 50, 50));
    ui->CameraLabel->setPixmap(this->_mainWindowResources->GetBackground());
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
            ui->FPSLabel, ui->RollLabel, ui->PitchLabel, ui->CompassLabel, ui->DepthLabel, ui->RoundPitchLabel,
            ui->YawLabel,
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
#if DEBUG
    QLabel *indicators[] = {
            ui->RollLabel, ui->PitchLabel, ui->YawLabel, ui->CompassLabel, ui->RoundPitchLabel, ui->DepthLabel,
    };
    for (auto &indicator : indicators) {
        indicator->setFrameShape(QFrame::Box);
    }
#endif

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

    /// Moving the yaw label
    x = (ui->MainTab->width() - ui->YawLabel->width()) / 2;
    ui->YawLabel->move(x, 0);

    /// Moving the depth label
    offset = 120;
    x = ui->RollLabel->x() + ui->RollLabel->width() - ui->DepthLabel->width() + offset;
    y = (ui->MainTab->height() - ui->DepthLabel->height()) / 2;
    ui->DepthLabel->move(x, y);

    /// Moving the compass label
    x = ui->MainTab->width() - ui->CompassLabel->width();
    y = ui->MainTab->height() - ui->CompassLabel->height();
    ui->CompassLabel->move(x, y);

    /// Moving the round pitch label
    x = ui->CompassLabel->x() - ui->RoundPitchLabel->width();
    y = ui->CompassLabel->y();
    ui->RoundPitchLabel->move(x, y);

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

    /// Moving the KeyAssignments widget
    offset = 35; // Horizontal distance between widgets
    x = (ui->SettingsStackedWidget->width() - (ui->KeyAssignmentsWidget->width()
                                               + ui->GamepadTestWidget->width() + offset)) / 2;
    y = (ui->SettingsStackedWidget->height() - ui->KeyAssignmentsWidget->height()) / 2;
    ui->KeyAssignmentsWidget->move(x, y);

    /// Moving the GamepadTest widget
    x = ui->KeyAssignmentsWidget->x() + ui->KeyAssignmentsWidget->width() + offset;
    ui->GamepadTestWidget->move(x, y);

    /// Moving the UISettings widget
    offset = 35; // Horizontal distance between widgets
    x = (ui->SettingsStackedWidget->width() - (ui->UISettingsWidget->width()
                                               + ui->OtherSettingsWidget->width() + offset)) / 2;
    y = (ui->SettingsStackedWidget->height() - ui->UISettingsWidget->height()) / 2;
    ui->UISettingsWidget->move(x, y);

    /// Moving the OtherSettings widget
    x = ui->UISettingsWidget->x() + ui->UISettingsWidget->width() + offset;
    ui->OtherSettingsWidget->move(x, y);

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

    /// Moving the GamepadTest label
    x = ui->GamepadTestWidget->x() + ui->GamepadTestWidget->width() / 2 - ui->GamepadTestLabel->width() / 2;
    y = ui->GamepadTestWidget->y() - ui->GamepadTestLabel->height() / 2;
    ui->GamepadTestLabel->move(x, y);

    /// Moving the UISettings label
    x = ui->UISettingsWidget->x() + ui->UISettingsWidget->width() / 2 - ui->UISettingsLabel->width() / 2;
    y = ui->UISettingsWidget->y() - ui->UISettingsLabel->height() / 2;
    ui->UISettingsLabel->move(x, y);

    /// Moving the OtherSettings label
    x = ui->OtherSettingsWidget->x() + ui->OtherSettingsWidget->width() / 2 - ui->OtherSettingsLabel->width() / 2;
    y = ui->OtherSettingsWidget->y() - ui->OtherSettingsLabel->height() / 2;
    ui->OtherSettingsLabel->move(x, y);

    /// Moving the CodeEdit Label
    x = ui->CodeEdit->x() + ui->CodeEdit->width() / 2 - ui->CodeEditLabel->width() / 2;
    y = ui->CodeEditLabel->y();
    ui->CodeEditLabel->move(x, y);
}

void MainWindow::UpdateWidgets() {

    this->MoveWidgets();

    /// Painting a video frame or placeholder image
    if (this->_videoStream->IsStreamOnline()) {
        cv::Mat mat = this->_videoStream->GetMatrix();
        QPixmap currentVideoFrame(cvMatToPixmap(mat));
        if (currentVideoFrame != this->_oldVideoFrame) {
            ui->CameraLabel->setPixmap(currentVideoFrame);
        }
        this->_isVideoFrame = true;
    } else if (!this->_videoStream->IsStreamOnline() && this->_isVideoFrame) {
        ui->CameraLabel->setPixmap(this->_mainWindowResources->GetBackground());
        this->_isVideoFrame = false;
    }

    /// Selecting the color of the CommandsProtocol button
    if (this->_commandsProtocol->IsStreamOnline() && !this->_isGreen) {
        ui->CommandsProtocolButton->setIcon(this->_mainWindowResources->GetGreenStartIcon());
        this->_isGreen = true;
    } else if (!this->_commandsProtocol->IsStreamOnline() && this->_isGreen) {
        ui->CommandsProtocolButton->setIcon(this->_mainWindowResources->GetRedStartIcon());
        this->_isGreen = false;
    }

    /// Selecting the color of the VideoStream button
    if (_videoStream->IsStreamOnline() && !this->_isPause) {
        ui->VideoStreamButton->setIcon(this->_mainWindowResources->GetPauseIcon());
        this->_isPause = true;
    } else if (!_videoStream->IsStreamOnline() && this->_isPause) {
        ui->VideoStreamButton->setIcon(this->_mainWindowResources->GetPlayIcon());
        this->_isPause = false;
    }

    TelemetryStruct telemetryStruct = this->_commandsProtocol->GetTelemetryStruct();

    /// Painting the roll indicator if angle changed
    float currentEulerX = telemetryStruct.Rotation[TelemetryStruct::X];
    if ((int32_t) currentEulerX != this->_oldEulerX) {
        this->PaintRollIndicator(currentEulerX, 1);
        this->_oldEulerX = (int32_t) currentEulerX;
    }

    /// Painting the pitch indicator if angle changed
    float currentEulerY = telemetryStruct.Rotation[TelemetryStruct::Y];
    if ((int32_t) currentEulerY != this->_oldEulerY) {
        this->PaintPitchIndicator(currentEulerY, 1);
        this->_oldEulerY = (int32_t) currentEulerY;
    }

    /// Painting the yaw indicator and compass if angle changed
    float currentEulerZ = telemetryStruct.Rotation[TelemetryStruct::Z];
    //float currentEulerZ = 212.0f;
    if ((int32_t) currentEulerZ != this->_oldEulerZ) {
        this->PaintYawIndicator(currentEulerZ, 1);
        this->PaintCompass(currentEulerZ, 1);
        this->_oldEulerZ = (int32_t) currentEulerZ;
    }

    /// Painting the depth indicator
    this->PaintDepthIndicator(telemetryStruct.Depth, 10, 1);

    /// Counting FPS - printing every 1 sec
    this->_fps++;
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() -
                                                         this->_oldTime) >= std::chrono::seconds{1}) {
        this->_oldTime = std::chrono::high_resolution_clock::now();
        ui->FPSLabel->setText(QString("FPS: ") + QString::number(this->_fps));
        this->_fps = 0;
    }
}

void MainWindow::on_MotorsNumberSpinBox_valueChanged(int value) {
    /// Changing the height of the table
    ui->MotorsTable->setFixedHeight((value * 26) + ((int) (value * 0.5))); // 26 - высота одной строки

    /// Moving the lower lines
    int x = ui->MotorsBottomLeftLine->x();
    int y = ui->MotorsTable->y() + ui->MotorsTable->height();
    ui->MotorsBottomLeftLine->move(x, y);
    x = ui->MotorsBottomRightLine->x();
    ui->MotorsBottomRightLine->move(x, y);

    /// Changing the height of the side lines
    int height = ui->MotorsBottomLeftLine->y() - ui->MotorsTopLeftLine->y();
    ui->MotorsLeftLine->setFixedHeight(height);
    ui->MotorsRightLine->setFixedHeight(height);

    /// Setting the number of rows in the table
    ui->MotorsTable->setRowCount(value);

    /// Filling the empty cells with zeros
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            if (ui->MotorsTable->item(i, j) == nullptr) {
                ui->MotorsTable->setItem(i, j, new QTableWidgetItem("0.0"));
            }
        }
    }
}

void MainWindow::on_HandFreedomSpinBox_valueChanged(int value) {
    /// Changing the width of the table
    ui->HandTable->setFixedWidth((value * 49) + ((int) (value * 0.5))); // 49 - width of one column

    /// Moving the table under the HandCoefficients label
    int x = (ui->HandCoefficientsLabel->x() + (ui->HandCoefficientsLabel->width() / 2)) -
            (ui->HandTable->width() / 2);
    int y = ui->HandTable->y();
    ui->HandTable->move(x, y);

    /// Moving the side lines
    x = ui->HandTable->x() - 20;
    y = ui->HandLeftLine->y();
    ui->HandLeftLine->move(x, y);
    x = ui->HandTable->x() + ui->HandTable->width();
    ui->HandRightLine->move(x, y);

    /// Moving the upper and lower lines
    x = ui->HandLeftLine->x() + 9;
    y = ui->HandTopLeftLine->y();
    ui->HandTopLeftLine->move(x, y);
    y = ui->HandBottomLeftLine->y();
    ui->HandBottomLeftLine->move(x, y);
    x = ui->HandRightLine->x() - 9;
    y = ui->HandTopRightLine->y();
    ui->HandTopRightLine->move(x, y);
    y = ui->HandBottomRightLine->y();
    ui->HandBottomRightLine->move(x, y);

    /// Setting the number of columns in the table
    ui->HandTable->setColumnCount(value);

    /// Filling the empty cells with zeros
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        if (ui->HandTable->item(0, j) == nullptr) {
            ui->HandTable->setItem(0, j, new QTableWidgetItem("0.0"));
        }
    }
}

QImage MainWindow::cvMatToQImage(const cv::Mat &mat) {
    switch (mat.type()) {
        case CV_8UC3: {
            QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
            return image;
        }
        case CV_8UC4: {
            QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_ARGB32);
            return image;
        }
    }

    return QImage();
}

QPixmap MainWindow::cvMatToPixmap(const cv::Mat &mat) {
    QImage image = cvMatToQImage(mat);
    image = std::move(image).rgbSwapped();
    return QPixmap::fromImage(image);
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

    painter.setPen(QPen(Qt::white, 3));
    painter.rotate(rollAngle);
    painter.drawEllipse(QPoint(0, 0), 5, 5);
    painter.drawArc(QRect(-15, -15, 30, 30), 0, -180 * 16);
    painter.drawLine(16, -1, 270, 0);
    painter.drawLine(-16, -1, -270, 0);

    ui->RollLabel->setPixmap(pixmap);
}

void MainWindow::PaintPitchIndicator(float pitchAngle, float sizeMultiplier) {
    QPixmap pixmap(ui->PitchLabel->width(), ui->PitchLabel->height());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::white, 3));
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawLine(50, 5, 119, 5);
    painter.drawLine(120, 6, 120,
                     ui->PitchLabel->height() - 6);
    painter.drawLine(50,
                     ui->PitchLabel->height() - 5,
                     119,
                     ui->PitchLabel->height() - 5);

    painter.translate(425, 320);
    auto y = ((int32_t) pitchAngle);
    if (y < -180) y = -180;
    else if ((-180 <= y) && (y < -90)) y = -(y + 180) * 3; // Смотрит назад, нижняя полусфера
    else if ((-90 <= y) && (y < 90)) y = y * 3;            // Смотрит вперед
    else if ((90 <= y) && (y <= 180)) y = -(y - 180) * 3;  // Смотрит назад, верхняя полусфера
    else if (y > 180) y = 180;

    painter.drawEllipse(QPoint(0, y), 5, 5);
    painter.setPen(QPen(Qt::white, 3, Qt::PenStyle::DashLine));
    if (y < 0) painter.drawLine(0, -5, 0, y + 5);
    else if (y > 0) painter.drawLine(0, 5, 0, y - 5);

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
    painter.drawText(boundingRect, Qt::AlignCenter, QString::number((int32_t) pitchAngle) + QString("°"));

    ui->PitchLabel->setPixmap(pixmap);
}

void MainWindow::PaintYawIndicator(float yawAngle, float sizeMultiplier) {
    QPixmap pixmap(ui->YawLabel->width(), ui->YawLabel->height());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::white, 3));
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawLine(5,
                     ui->YawLabel->height() / 2,
                     15,
                     ui->YawLabel->height() - 11);
    painter.drawLine(15,
                     ui->YawLabel->height() - 10,
                     ui->YawLabel->width() - 15,
                     ui->YawLabel->height() - 10);
    painter.drawLine(ui->YawLabel->width() - 15,
                     ui->YawLabel->height() - 10,
                     ui->YawLabel->width() - 5,
                     ui->YawLabel->height() / 2);

    painter.translate(ui->YawLabel->width() / 2, 0);
    painter.drawLine(0, ui->YawLabel->height() - 11, 0, ui->YawLabel->height() - 31);

    /// IMPORTANT VARIABLES
    int32_t valueRectWidth = 60;
    int32_t valueRectHeight = 30;
    int32_t step = 5;
    int32_t distance = 35;

    /// Painting center value
    int32_t valueOffset = ((int32_t) yawAngle) % step;
    int32_t scaleOffset = (valueOffset * (valueRectWidth + distance)) / step;
    painter.translate(-scaleOffset, 0);
    QRect boundingRect(-(valueRectWidth / 2), valueRectHeight / 2, valueRectWidth, valueRectHeight);
    painter.setFont(QFont("Times", 16));
    int32_t centerValue = ((int32_t) yawAngle) - valueOffset;
    switch (centerValue) {
        case 0:
            painter.drawText(boundingRect, Qt::AlignCenter, "С");
            break;
        case 45:
            painter.drawText(boundingRect, Qt::AlignCenter, "СВ");
            break;
        case 90:
            painter.drawText(boundingRect, Qt::AlignCenter, "В");
            break;
        case 135:
            painter.drawText(boundingRect, Qt::AlignCenter, "ЮВ");
            break;
        case 180:
            painter.drawText(boundingRect, Qt::AlignCenter, "Ю");
            break;
        case 225:
            painter.drawText(boundingRect, Qt::AlignCenter, "ЮЗ");
            break;
        case 270:
            painter.drawText(boundingRect, Qt::AlignCenter, "З");
            break;
        case 315:
            painter.drawText(boundingRect, Qt::AlignCenter, "СЗ");
            break;
        default:
            painter.drawText(boundingRect, Qt::AlignCenter, QString::number(centerValue));
    }

    /// Painting left values
    int32_t currentX = (ui->YawLabel->width() / 2) - scaleOffset;
    int8_t translationNumber = 1;
    while (currentX >= ((valueRectWidth + distance) * 2)) {
        painter.translate(-(valueRectWidth + distance), 0);
        QRect rect(-(valueRectWidth / 2), valueRectHeight / 2, valueRectWidth, valueRectHeight);
        int32_t value = (((int32_t) yawAngle) - valueOffset) - (step * translationNumber);
        if (value < 0) value = 360 + value;
        else if (value > 360) value = value - 360;
        switch (value) {
            case 0:
                painter.drawText(rect, Qt::AlignCenter, "С");
                break;
            case 45:
                painter.drawText(rect, Qt::AlignCenter, "СВ");
                break;
            case 90:
                painter.drawText(rect, Qt::AlignCenter, "В");
                break;
            case 135:
                painter.drawText(rect, Qt::AlignCenter, "ЮВ");
                break;
            case 180:
                painter.drawText(rect, Qt::AlignCenter, "Ю");
                break;
            case 225:
                painter.drawText(rect, Qt::AlignCenter, "ЮЗ");
                break;
            case 270:
                painter.drawText(rect, Qt::AlignCenter, "З");
                break;
            case 315:
                painter.drawText(rect, Qt::AlignCenter, "СЗ");
                break;
            default:
                painter.drawText(rect, Qt::AlignCenter, QString::number(value));
        }
        translationNumber++;
        currentX -= valueRectWidth;
    }

    /// Reset variables
    for (size_t i = 0; i < translationNumber - 1; i++) {
        painter.translate(valueRectWidth + distance, 0);
        currentX += valueRectWidth;
    }
    translationNumber = 1;

    /// Painting right values
    while (currentX <= (ui->YawLabel->width() - ((valueRectWidth + distance) * 2))) {
        painter.translate(valueRectWidth + distance, 0);
        QRect rect(-(valueRectWidth / 2), valueRectHeight / 2, valueRectWidth, valueRectHeight);
        int32_t value = (((int32_t) yawAngle) - valueOffset) + (step * translationNumber);
        if (value < 0) value = 360 - value;
        else if (value > 360) value = value - 360;
        switch (value) {
            case 0:
                painter.drawText(rect, Qt::AlignCenter, "С");
                break;
            case 45:
                painter.drawText(rect, Qt::AlignCenter, "СВ");
                break;
            case 90:
                painter.drawText(rect, Qt::AlignCenter, "В");
                break;
            case 135:
                painter.drawText(rect, Qt::AlignCenter, "ЮВ");
                break;
            case 180:
                painter.drawText(rect, Qt::AlignCenter, "Ю");
                break;
            case 225:
                painter.drawText(rect, Qt::AlignCenter, "ЮЗ");
                break;
            case 270:
                painter.drawText(rect, Qt::AlignCenter, "З");
                break;
            case 315:
                painter.drawText(rect, Qt::AlignCenter, "СЗ");
                break;
            default:
                painter.drawText(rect, Qt::AlignCenter, QString::number(value));
        }
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
    QRect boundingRect((int32_t) (-40 * sizeMultiplier),
                       (int32_t) (10 * sizeMultiplier),
                       (int32_t) (80 * sizeMultiplier),
                       (int32_t) (30 * sizeMultiplier));
    painter.setPen(QPen(Qt::white, 2));
    painter.drawRect(boundingRect);
    painter.setPen(QPen(Qt::white, 3));
    painter.drawText(boundingRect, Qt::AlignCenter, QString::number((int32_t) angle) + QString("°"));

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

    painter.drawLine(331, 5, 400, 5);
    painter.drawLine(330, 6, 330,
                     ui->DepthLabel->height() - 6);
    painter.drawLine(331,
                     ui->DepthLabel->height() - 5,
                     400,
                     ui->DepthLabel->height() - 5);

    painter.translate(25, 320);

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