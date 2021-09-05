#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"
#include "../ExceptionHandler/ExceptionHandler.hpp"

void MainWindow::SetupButtons() {
    this->connect(ui->VideoStreamButton, SIGNAL(clicked(bool)), SLOT(SwitchVideoStream()));
    this->connect(ui->ScreenshotButton, SIGNAL(clicked(bool)), SLOT(TakeScreenshot()));
    this->connect(ui->VideoCaptureButton, SIGNAL(clicked(bool)), SLOT(SwitchVideoCapture()));
    this->connect(ui->CommandsProtocolButton, SIGNAL(clicked(bool)), SLOT(SwitchSendingCommands()));
    this->connect(ui->ReceiveSettingsButton, SIGNAL(clicked(bool)), SLOT(ReceiveRobotSettings()));
    this->connect(ui->SendSettingsButton, SIGNAL(clicked(bool)), SLOT(SendRobotSettings()));
    this->connect(ui->SaveClientSettingsButton, SIGNAL(clicked(bool)), SLOT(SaveClientSettings()));
    this->connect(ui->LoadClientSettingsButton, SIGNAL(clicked(bool)), SLOT(LoadClientSettings()));
    this->connect(ui->RefreshGamepadsButton, SIGNAL(clicked(bool)), SLOT(RefreshGamepads()));
    this->connect(ui->RefreshClientIPsButton, SIGNAL(clicked(bool)), SLOT(RefreshClientIps()));
    this->connect(ui->FullScreenButton, SIGNAL(clicked(bool)), SLOT(SwitchFullScreen()));
    this->connect(ui->ShowTabBarButton, SIGNAL(clicked(bool)), SLOT(ShowTabBar()));
    this->connect(ui->HideTabBarButton, SIGNAL(clicked(bool)), SLOT(HideTabBar()));
    this->connect(ui->DebugCodeButton, SIGNAL(clicked(bool)), SLOT(DebugCode()));
    this->connect(ui->ReleaseCodeButton, SIGNAL(clicked(bool)), SLOT(ReleaseCode()));
}

void MainWindow::SwitchVideoStream() {
    std::function<void(MainWindow *)> function = &MainWindow::RawSwitchVideoStream;
    ExceptionHandler(this, function, nullptr, nullptr);
}

void MainWindow::SwitchVideoCapture() {
    std::function<void(MainWindow *)> function = &MainWindow::RawSwitchVideoCapture;
    ExceptionHandler(this, function, nullptr, nullptr);
}

void MainWindow::TakeScreenshot() {
    std::function<void(MainWindow *)> function = &MainWindow::RawTakeScreenshot;
    ExceptionHandler(this, function, nullptr, nullptr);
}

void MainWindow::SwitchSendingCommands() {
    std::function<void(MainWindow *)> function = &MainWindow::RawSwitchSendingCommands;
    ExceptionHandler(this, function, nullptr, nullptr);
}

void MainWindow::ReceiveRobotSettings() {
    std::function<void(MainWindow *)> function = &MainWindow::RawReceiveRobotSettings;
    ExceptionHandler(this, function, "Успех", "Настройки успешно приняты");
}

void MainWindow::SendRobotSettings() {
    std::function<void(MainWindow *)> function = &MainWindow::RawSendRobotSettings;
    ExceptionHandler(this, function, "Успех", "Настройки успешно отправлены");
}

void MainWindow::SaveClientSettings() {
    RawSaveClientSettings();
    QMessageBox::information(this, "Сообщение", "Настройки успешно сохранены");
}

void MainWindow::LoadClientSettings() {
    RawLoadClientSettings();
    //QMessageBox::information(this, "Сообщение", "Настройки успешно восстановлены");
}

void MainWindow::RefreshGamepads() {
    std::list<int> gamepads = Control::GetGamepadsIds();
    ui->GamepadComboBox->clear();
    for (int id : gamepads) {
        ui->GamepadComboBox->addItem(QString::number(id));
    }

    std::list<std::string> ips = GetClientIps();

    // The path to get the selected ID:
    // int id = ui->GamepadComboBox->itemText(ui->GamepadComboBox->currentIndex()).toInt()
}

void MainWindow::RefreshClientIps() {
    std::list<std::string> addresses = GetClientIps();
    ui->ClientIPComboBox->clear();
    for (std::string address : addresses) {
        ui->ClientIPComboBox->addItem(QString::fromStdString(address));
    }

    std::list<std::string> ips = GetClientIps();

    // The path to get the selected IP:
    // QString ip = ui->ClientIPComboBox->itemText(ui->ClientIPComboBox->currentIndex());

}

void MainWindow::SwitchFullScreen() {
    this->windowState() == Qt::WindowFullScreen ?
    this->setWindowState(Qt::WindowNoState) :
    this->setWindowState(Qt::WindowFullScreen);
}

void MainWindow::ShowTabBar() {
    /// Showing the TabBar
    ui->TabWidget->tabBar()->show();

    /// Showing all the buttons on the TabBar
    ui->FullScreenButton->show();
    ui->HideTabBarButton->show();
    ui->CommandsProtocolButton->show();

    /// Hiding ShowTabBar button
    ui->ShowTabBarButton->hide();
}

void MainWindow::HideTabBar() {
    /// Hiding the TabBar
    ui->TabWidget->tabBar()->hide();

    /// Hiding all the buttons on the TabBar
    ui->FullScreenButton->hide();
    ui->HideTabBarButton->hide();
    ui->CommandsProtocolButton->hide();

    /// Showing ShowTabBar button
    ui->ShowTabBarButton->show();
}

void MainWindow::ReleaseCode() {
    Py_Initialize();
    const char *str = qPrintable(ui->CodeEdit->toPlainText());
    PyRun_SimpleString(str);
    Py_Finalize();
}

void MainWindow::DebugCode() {
    Py_Initialize();
    const char *str = qPrintable(ui->CodeEdit->toPlainText());
    PyRun_SimpleString(str);
    Py_Finalize();
}