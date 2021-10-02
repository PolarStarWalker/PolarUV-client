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

    /// Adding a shadow effect to tab_1 labels
    QLabel *labels[] = {
            ui->RollLabel, ui->PitchLabel, ui->CompassLabel, ui->DepthLabel, ui->RoundPitchLabel
    };
    for (auto &label : labels) {
        auto *shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setOffset(0, 0);
        shadowEffect->setBlurRadius(5.0);
        shadowEffect->setColor(Qt::black);
        label->setGraphicsEffect(shadowEffect);
    }

    /// Adding a shadow effect to tab_1 buttons
    QPushButton *buttons[] = {
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

    /// Moving the pitch label
    offset = 120;
    x = ui->RollLabel->x() - offset;
    y = (ui->tab_1->height() - ui->PitchLabel->height()) / 2;
    ui->PitchLabel->move(x, y);

    /// Moving the depth label
    offset = 120;
    x = ui->RollLabel->x() + ui->RollLabel->width() - ui->DepthLabel->width() + offset;
    y = (ui->tab_1->height() - ui->DepthLabel->height()) / 2;
    ui->DepthLabel->move(x, y);

    /// Moving the compass label
    x = ui->tab_1->width() - ui->CompassLabel->width();
    y = ui->tab_1->height() - ui->CompassLabel->height();
    ui->CompassLabel->move(x, y);

    /// Moving the round pitch label
    x = ui->CompassLabel->x() - ui->RoundPitchLabel->width();
    y = ui->CompassLabel->y();
    ui->RoundPitchLabel->move(x, y);

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

    this->PaintRollIndicator(telemetry.Rotation[TelemetryStruct::X], 1);
    this->PaintPitchIndicator(telemetry.Rotation[TelemetryStruct::Y], 1);
    this->PaintCompass(telemetry.Rotation[TelemetryStruct::Z], 1);
    this->PaintDepthIndicator(0, 10, 1);
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

void MainWindow::PaintEulerIndicators(float xAngle, float yAngle, float zAngle) {
    this->PaintRollIndicator(xAngle, 1);
    this->PaintPitchIndicator(yAngle, 1);
    this->PaintYawIndicator(zAngle, 1);
    this->PaintCompass(zAngle, 1);
}