#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::SetupRendering() {
    /// Starting the window rendering timer
    this->startTimer(1000 / 60, Qt::PreciseTimer);

    /// Setting the application icon
    setWindowIcon(QIcon("Icons/WindowIcon.png"));

    /// Setting the tab icons
    ui->TabWidget->setTabIcon(0, QIcon("Icons/CameraIcon.png"));
    ui->TabWidget->setTabIcon(1, QIcon("Icons/RobotIcon.png"));
    ui->TabWidget->setTabIcon(2, QIcon("Icons/ClientIcon.png"));
    ui->TabWidget->setTabIcon(3, QIcon("Icons/CodeIcon.png"));

    /// Setting the button icons
    ui->FullScreenButton->setIcon(QIcon("Icons/FullScreenIcon.png"));
    ui->ShowTabBarButton->setIcon(QIcon("Icons/ShowTabBarIcon.png"));
    ui->HideTabBarButton->setIcon(QIcon("Icons/HideTabBarIcon.png"));
    ui->VideoStreamButton->setIcon(QIcon("Icons/PlayIcon.png"));
    ui->ScreenshotButton->setIcon(QIcon("Icons/ScreenshotIcon.png"));
    ui->VideoCaptureButton->setIcon(QIcon("Icons/WhiteVideoIcon.png"));
    ui->RefreshClientIPsButton->setIcon(QIcon("Icons/ReloadIcon.png"));
    ui->RefreshGamepadsButton->setIcon(QIcon("Icons/ReloadIcon.png"));
    ui->ReleaseCodeButton->setIcon(QIcon("Icons/PlayIcon.png"));
    ui->DebugCodeButton->setIcon(QIcon("Icons/BugIcon.png"));

    /// Setting a transparent background for some buttons
    ui->ShowTabBarButton->setStyleSheet("background-color: transparent");
    ui->VideoStreamButton->setStyleSheet("background-color: transparent");
    ui->ScreenshotButton->setStyleSheet("background-color: transparent");
    ui->VideoCaptureButton->setStyleSheet("background-color: transparent");

    /// Hiding the TabBar button
    ui->ShowTabBarButton->hide();

    /// Adding a shadow effect to roll label
    auto *rollShadowEffect = new QGraphicsDropShadowEffect(this);
    rollShadowEffect->setOffset(0, 0);
    rollShadowEffect->setBlurRadius(5.0);
    rollShadowEffect->setColor(Qt::black);
    ui->RollLabel->setGraphicsEffect(rollShadowEffect);

    /// Adding a shadow effect to compass label
    auto *compassShadowEffect = new QGraphicsDropShadowEffect(this);
    compassShadowEffect->setOffset(0, 0);
    compassShadowEffect->setBlurRadius(5.0);
    compassShadowEffect->setColor(Qt::black);
    ui->CompassLabel->setGraphicsEffect(compassShadowEffect);

    /// Adding a shadow effect to telemetry labels
    QLabel *telemetryLabels[26] = {
            ui->AccelerationLabel, ui->AccelerationXLabel, ui->AccelerationXValue, ui->AccelerationXUnits,
            ui->AccelerationYLabel, ui->AccelerationYValue, ui->AccelerationYUnits, ui->AccelerationZLabel,
            ui->AccelerationZValue, ui->AccelerationZUnits, ui->EulerLabel, ui->EulerXLabel, ui->EulerXValue,
            ui->EulerXUnits, ui->EulerYLabel, ui->EulerYValue, ui->EulerYUnits, ui->EulerZLabel, ui->EulerZValue,
            ui->EulerZUnits, ui->DepthLabel, ui->DepthValue, ui->DepthUnits, ui->VoltageLabel, ui->VoltageValue,
            ui->VoltageUnits
    };
    for (auto &telemetryLabel : telemetryLabels) {
        auto *shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setOffset(0, 0);
        shadowEffect->setBlurRadius(5.0);
        shadowEffect->setColor(Qt::black);
        telemetryLabel->setGraphicsEffect(shadowEffect);
    }

    /// Adding a shadow effect to tab_1 buttons
    QPushButton *buttons[4] = {
            ui->ShowTabBarButton, ui->VideoStreamButton, ui->ScreenshotButton, ui->VideoCaptureButton
    };
    for (auto &button : buttons) {
        auto *shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setOffset(0, 0);
        shadowEffect->setBlurRadius(5.0);
        shadowEffect->setColor(Qt::black);
        button->setGraphicsEffect(shadowEffect);
    }
}

void MainWindow::placeWidgets() {
    /// Changing the size of the TabWidget
    ui->TabWidget->setGeometry(ui->MainWidget->geometry());

    /// Changing the size of the CameraLabel
    ui->CameraLabel->setGeometry(ui->tab_1->geometry());

    /// Changing the size of the backgrounds
    ui->Tab2BackgroundLabel->setGeometry(ui->tab_2->geometry());
    ui->Tab3BackgroundLabel->setGeometry(ui->tab_3->geometry());
    ui->Tab4BackgroundLabel->setGeometry(ui->tab_4->geometry());

    /// Changing the size of the CodeEdit
    ui->CodeEdit->setFixedWidth(ui->tab_4->width() - 140);
    ui->CodeEdit->setFixedHeight(ui->tab_4->height() - ui->OutputEdit->height() - 140 - 10);

    /// Changing the size of the OutputEdit
    ui->OutputEdit->setFixedWidth(ui->tab_4->width() - 140);

    /// Moving the CommandsProtocol button
    int offset = 0; // Distance from the bottom edge of window
    int x = 0;
    ui->CommandsProtocolButton->move(x, ui->MainWidget->height() - ui->CommandsProtocolButton->height() - offset);

    /// Moving the FullScreen button
    offset = 10; // Vertical distance between buttons
    x = 0;
    int y = (ui->MainWidget->height() - (ui->FullScreenButton->height() + ui->HideTabBarButton->height() + offset)) / 2;
    ui->FullScreenButton->move(x, y);

    /// Moving the HideTabBar button
    y = ui->FullScreenButton->y() + ui->HideTabBarButton->height() + offset;
    ui->HideTabBarButton->move(x, y);

    /// Moving the ShowTabBar button
    ui->ShowTabBarButton->move(0, 0);

    /// Moving the roll label
    x = (ui->tab_1->width() - ui->RollLabel->width()) / 2;
    y = (ui->tab_1->height() - ui->RollLabel->height()) / 2;
    ui->RollLabel->move(x, y);

    /// Moving the compass label
    x = ui->tab_1->width() - ui->CompassLabel->width();
    y = ui->tab_1->height() - ui->CompassLabel->height();
    ui->CompassLabel->move(x, y);

    /// Moving the VideoStream button
    offset = 10; // Distance from the bottom edge of window
    x = (ui->tab_1->width() / 2) - (ui->VideoStreamButton->width() / 2);
    y = ui->tab_1->height() - ui->VideoStreamButton->height() - offset;
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

    /// Moving the MotorsSettings widget
    offset = 35; // Horizontal distance between widgets
    x = (ui->tab_2->width() - (ui->MotorsSettingsWidget->width() + ui->HandSettingsWidget->width() + offset)) / 2;
    y = (ui->tab_2->height() - ui->MotorsSettingsWidget->height()) / 2;
    ui->MotorsSettingsWidget->move(x, y);

    /// Moving the HandSettings widget
    x = ui->MotorsSettingsWidget->x() + ui->MotorsSettingsWidget->width() + offset;
    ui->HandSettingsWidget->move(x, y);

    /// Moving the KeyAssignments widget
    offset = 35; // Horizontal distance between widgets
    x = (ui->tab_3->width() - (ui->KeyAssignmentsWidget->width() + ui->ClientSettingsWidget->width() + offset)) / 2;
    y = (ui->tab_3->height() - ui->KeyAssignmentsWidget->height()) / 2;
    ui->KeyAssignmentsWidget->move(x, y);

    /// Moving the ClientSettings widget
    x = ui->KeyAssignmentsWidget->x() + ui->KeyAssignmentsWidget->width() + offset;
    ui->ClientSettingsWidget->move(x, y);

    /// Moving the Telemetry widget
    offset = 10; // Distance from the top edge of the window
    ui->TelemetryWidget->move(ui->tab_1->width() - ui->TelemetryWidget->width(), 0 + offset);

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

    /// Moving the ClientSettings label
    x = ui->ClientSettingsWidget->x() + ui->ClientSettingsWidget->width() / 2 - ui->ClientSettingsLabel->width() / 2;
    y = ui->ClientSettingsWidget->y() - ui->ClientSettingsLabel->height() / 2;
    ui->ClientSettingsLabel->move(x, y);

    /// Moving the CodeEdit Label
    x = ui->CodeEdit->x() + ui->CodeEdit->width() / 2 - ui->CodeEditLabel->width() / 2;
    y = ui->CodeEditLabel->y();
    ui->CodeEditLabel->move(x, y);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    /// Placing widgets if this is the first painting since the launch
    if (!this->_widgetsPlaced) this->placeWidgets();

    /// Painting a video frame or placeholder image
    if (this->_videoStream->IsStreamOnline()) {
        cv::Mat mat = this->_videoStream->GetMatrix();
        QPixmap videoFrame(cvMatToPixmap(mat));
        ui->CameraLabel->setPixmap(videoFrame);
        ui->Tab2BackgroundLabel->setPixmap(videoFrame);
        ui->Tab3BackgroundLabel->setPixmap(videoFrame);
        ui->Tab4BackgroundLabel->setPixmap(videoFrame);
    } else {
        QPixmap background("Icons/Background.png");
        ui->CameraLabel->setPixmap(background);
        ui->Tab2BackgroundLabel->setPixmap(background);
        ui->Tab3BackgroundLabel->setPixmap(background);
        ui->Tab4BackgroundLabel->setPixmap(background);
    }

    /// Selecting the color of the CommandsProtocol button
    if (this->_commandsProtocol->IsStreamOnline()) {
        ui->CommandsProtocolButton->setIcon(QIcon("Icons/GreenStartIcon.png"));
    } else {
        ui->CommandsProtocolButton->setIcon(QIcon("Icons/RedStartIcon.png"));
    }

    /// Selecting the color of the VideoStream button
    if (_videoStream->IsStreamOnline()) {
        ui->VideoStreamButton->setIcon(QIcon("Icons/PauseIcon.png"));
    } else {
        ui->VideoStreamButton->setIcon(QIcon("Icons/PlayIcon.png"));
    }
}

void MainWindow::timerEvent(QTimerEvent *event) {
    this->repaint();

    TelemetryStruct telemetry = this->_commandsProtocol->GetTelemetryStruct();

    ui->AccelerationXValue->setText(QString::number(telemetry.Acceleration[TelemetryStruct::X]));
    ui->AccelerationYValue->setText(QString::number(telemetry.Acceleration[TelemetryStruct::Y]));
    ui->AccelerationZValue->setText(QString::number(telemetry.Acceleration[TelemetryStruct::Z]));
    ui->EulerXValue->setText(QString::number(telemetry.Rotation[TelemetryStruct::X]));
    ui->EulerYValue->setText(QString::number(telemetry.Rotation[TelemetryStruct::Y]));
    ui->EulerZValue->setText(QString::number(telemetry.Rotation[TelemetryStruct::Z]));
    ui->DepthValue->setText(QString::number(telemetry.Depth));

    this->PaintRollIndicator(telemetry.Rotation[TelemetryStruct::X]);
    this->PaintCompass(telemetry.Rotation[TelemetryStruct::Z]);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    this->placeWidgets();
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
    int x = (ui->HandCoefficientsLabel->x() + (ui->HandCoefficientsLabel->width() / 2)) - (ui->HandTable->width() / 2);
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
}

QPixmap MainWindow::cvMatToPixmap(const cv::Mat &mat) {
    QImage image = cvMatToQImage(mat);
    image = std::move(image).rgbSwapped();
    return QPixmap::fromImage(image);
}

void MainWindow::PaintRollIndicator(float rollAngle) {
    QPixmap pixmap (ui->RollLabel->width(), ui->RollLabel->height());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::white, 3));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(pixmap.width() / 2, pixmap.height() / 2);

    /// Painting the first part of the main line
    painter.rotate(-rollAngle);
    painter.drawEllipse(QPoint(0,0),5,5);
    painter.drawArc(QRect(-15,-15,30,30),0,-180 * 16);
    painter.drawLine(16,-1,200,0);
    painter.drawLine(-16,-1,-200,0);

    ui->RollLabel->setPixmap(pixmap);
}

void MainWindow::PaintPitchIndicator(float pitchAngle) {

}

void MainWindow::PaintYawIndicator(float yawAngle) {

}

void MainWindow::PaintCompass(float angle) {
    QPixmap pixmap (ui->CompassLabel->width(), ui->CompassLabel->height());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::white, 3));
    painter.setFont(QFont("Times", 16));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(pixmap.width() / 2, pixmap.height() / 2);

    /// Painting the arrow
    painter.drawLine(QPointF(0, -0), QPointF(0, -80));

    /// Painting the north line
    painter.rotate(-angle);
    painter.drawLine(QPointF(0, -90), QPointF(0, -110));

    /// Painting the letters
    painter.drawText(-8, -120, "С");
    painter.drawText(-8, 140, "Ю");
    painter.drawText(-135, 10, "З");
    painter.drawText(120, 10, "В");

    /// Painting the other lines
    for (ssize_t i = 2; i <= 32; i++) {
        painter.rotate(11.25);
        if ((i == 9) || (i == 17) || (i == 25)) {
            painter.drawLine(QPointF(0, -90), QPointF(0, -110));
        } else if ((i == 5) || (i == 13) || (i == 21) || (i == 29)) {
            painter.drawLine(QPointF(0, -90), QPointF(0, -110));
        } else
            painter.drawLine(QPointF(0, -100), QPointF(0, -110));
    }

    ui->CompassLabel->setPixmap(pixmap);
}

void MainWindow::PaintEulerIndicators(float xAngle, float yAngle, float zAngle) {
    this->PaintRollIndicator(xAngle);
    this->PaintPitchIndicator(yAngle);
    this->PaintYawIndicator(zAngle);
    this->PaintCompass(zAngle);
}