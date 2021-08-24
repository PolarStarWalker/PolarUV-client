#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::setupRendering() {
    /// Starting the window rendering timer
    this->startTimer(1000 / 60, Qt::PreciseTimer);

    /// Setting the application icon
    setWindowIcon(QIcon("Icons/WindowIcon.png"));

    /// Setting the tab icons
    ui->TabWidget->setTabIcon(0, QIcon("Icons/CameraIcon"));
    ui->TabWidget->setTabIcon(1, QIcon("Icons/RobotIcon"));
    ui->TabWidget->setTabIcon(2, QIcon("Icons/ClientIcon"));

    /// Setting the button icons
    ui->FullScreenButton->setIcon(QIcon("Icons/FullScreenIcon.png"));
    ui->ShowTabBarButton->setIcon(QIcon("Icons/ShowTabBarIcon.png"));
    ui->HideTabBarButton->setIcon(QIcon("Icons/HideTabBarIcon.png"));
    ui->VideoStreamButton->setIcon(QIcon("Icons/PlayIcon.png"));
    ui->ScreenshotButton->setIcon(QIcon("Icons/ScreenshotIcon.png"));
    ui->VideoCaptureButton->setIcon(QIcon("Icons/WhiteVideoIcon.png"));
    ui->RefreshClientIPsButton->setIcon(QIcon("Icons/ReloadIcon.png"));
    ui->RefreshGamepadsButton->setIcon(QIcon("Icons/ReloadIcon.png"));

    /// Setting a transparent background for some buttons
    ui->ShowTabBarButton->setStyleSheet("background-color: transparent");
    ui->VideoStreamButton->setStyleSheet("background-color: transparent");
    ui->ScreenshotButton->setStyleSheet("background-color: transparent");
    ui->VideoCaptureButton->setStyleSheet("background-color: transparent");

    /// Hiding the TabBar button
    ui->ShowTabBarButton->hide();

    /// Adding a shadow effect to telemetry labels
    QLabel *telemetryLabels[23] = {
            ui->AccelerationLabel, ui->AccelerationXLabel, ui->AccelerationXValue, ui->AccelerationXUnits,
            ui->AccelerationYLabel, ui->AccelerationYValue, ui->AccelerationYUnits, ui->AccelerationZLabel,
            ui->AccelerationZValue, ui->AccelerationZUnits, ui->EulerLabel, ui->EulerXLabel, ui->EulerXValue,
            ui->EulerXUnits, ui->EulerYLabel, ui->EulerYValue, ui->EulerYUnits, ui->EulerZLabel, ui->EulerZValue,
            ui->EulerZUnits, ui->DepthLabel, ui->PressureLabel, ui->VoltageLabel
    };
    for (auto &telemetryLabel : telemetryLabels) {
        auto *shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setOffset(2, 2);
        shadowEffect->setColor(Qt::black);
        telemetryLabel->setGraphicsEffect(shadowEffect);
    }

    /// Adding a shadow effect to tab_1 buttons
    QPushButton *buttons[4] = {
        ui->ShowTabBarButton, ui->VideoStreamButton, ui->ScreenshotButton, ui->VideoCaptureButton
    };
    for (auto &button : buttons) {
        auto *shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setOffset(2, 2);
        shadowEffect->setColor(Qt::black);
        button->setGraphicsEffect(shadowEffect);
    }
}

void MainWindow::placeWidgets() {
    /// Changing the size of the TabWidget
    ui->TabWidget->setGeometry(ui->MainWidget->geometry());

    /// Changing the size of the CameraLabel
    ui->CameraLabel->setGeometry(ui->tab_1->geometry());

    /// Moving the CommandsProtocol button
    int offset = 0; // Distance from the bottom edge of window
    ui->CommandsProtocolButton->move(0, ui->MainWidget->height() - ui->CommandsProtocolButton->height() - offset);

    /// Moving the FullScreen button
    offset = 10; // Vertical distance between widgets
    int x = 0;
    int y = (ui->MainWidget->height() - (ui->FullScreenButton->height() + ui->HideTabBarButton->height() + offset)) / 2;
    ui->FullScreenButton->move(x, y);

    /// Moving the HideTabBar button
    y = ui->FullScreenButton->y() + ui->HideTabBarButton->height() + offset;
    ui->HideTabBarButton->move(x, y);

    /// Moving the ShowTabBar button
    ui->ShowTabBarButton->move(0, 0);

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
////////////////////////////////////
    /// Moving the MotorsSettings widget
    offset = 30; // Horizontal distance between widgets
    x = (ui->tab_2->width() - (ui->MotorsSettingsWidget->width() + ui->HandSettingsWidget->width() + offset)) / 2;
    y = (ui->tab_2->height() - ui->MotorsSettingsWidget->height()) / 2;
    ui->MotorsSettingsWidget->move(x, y);

    /// Moving the HandSettings widget
    x = ui->MotorsSettingsWidget->x() + ui->MotorsSettingsWidget->width() + offset;
    ui->HandSettingsWidget->move(x, y);
////////////////////////////////////////
    /// Moving the KeyAssignments widget
    offset = 30; // Horizontal distance between widgets
    x = (ui->tab_3->width() - (ui->KeyAssignmentsWidget->width() + ui->ClientSettingsWidget->width() + offset)) / 2;
    y = (ui->tab_3->height() - ui->KeyAssignmentsWidget->height()) / 2;
    ui->KeyAssignmentsWidget->move(x, y);

    /// Moving the ClientSettings widget
    x = ui->KeyAssignmentsWidget->x() + ui->KeyAssignmentsWidget->width() + offset;
    ui->ClientSettingsWidget->move(x, y);

    /// Moving the Telemetry widget
    offset = 10; // Distance from the top edge of the window
    ui->TelemetryWidget->move(ui->tab_1->width() - ui->TelemetryWidget->width(), 0 + offset);

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
}

void MainWindow::paintEvent(QPaintEvent *event) {
    /// Placing widgets if this is the first painting since the launch
    if (!this->_widgetsPlaced) this->placeWidgets();

    /// Painting a video frame or placeholder image
    if (this->_videoStream->IsOnline()) {
        cv::Mat mat = this->_videoStream->GetMatrix();
        ui->CameraLabel->setPixmap(QPixmap(cvMatToPixmap(mat)));
    } else {
        ui->CameraLabel->setPixmap(QPixmap("Icons/CameraPlaceholder.png"));
    }

    /// Selecting the color of the CommandsProtocol button
    if (this->_commandsProtocol->IsOnline()) {
        ui->CommandsProtocolButton->setIcon(QIcon("Icons/GreenStartIcon.png"));
    } else {
        ui->CommandsProtocolButton->setIcon(QIcon("Icons/RedStartIcon.png"));
    }

    /// Selecting the color of the VideoStream button
    if (_videoStream->IsOnline()) {
        ui->VideoStreamButton->setIcon(QIcon("Icons/PauseIcon.png"));
    } else {
        ui->VideoStreamButton->setIcon(QIcon("Icons/PlayIcon.png"));
    }
}

void MainWindow::timerEvent(QTimerEvent *event) {
    this->repaint();
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
                ui->MotorsTable->setItem(i, j, new QTableWidgetItem("0"));
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
            ui->HandTable->setItem(0, j, new QTableWidgetItem("0"));
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