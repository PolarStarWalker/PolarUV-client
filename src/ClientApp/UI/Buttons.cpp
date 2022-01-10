#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"
#include "../ExceptionHandler/ExceptionHandler.hpp"

void MainWindow::SetupButtons() {
    this->connect(ui->VideoStreamButton, SIGNAL(clicked(bool)), SLOT(SwitchVideoStream()));
    this->connect(ui->ScreenshotButton, SIGNAL(clicked(bool)), SLOT(TakeScreenshot()));
    this->connect(ui->VideoCaptureButton, SIGNAL(clicked(bool)), SLOT(SwitchVideoCapture()));
    this->connect(ui->CommandsProtocolButton, SIGNAL(clicked(bool)), SLOT(SwitchSendingCommands()));
    this->connect(ui->SettingsPage1Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage1()));
    this->connect(ui->SettingsPage2Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage2()));
    this->connect(ui->SettingsPage3Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage3()));
    this->connect(ui->ReceiveSettingsButton, SIGNAL(clicked(bool)), SLOT(ReceiveRobotSettings()));
    this->connect(ui->SendSettingsButton, SIGNAL(clicked(bool)), SLOT(SendRobotSettings()));
    this->connect(ui->SaveClientSettingsButton, SIGNAL(clicked(bool)), SLOT(SaveClientSettings()));
    this->connect(ui->LoadClientSettingsButton, SIGNAL(clicked(bool)), SLOT(LoadClientSettings()));
    this->connect(ui->RefreshGamepadsButton, SIGNAL(clicked(bool)), SLOT(RefreshGamepads()));
    this->connect(ui->RefreshClientIPsButton, SIGNAL(clicked(bool)), SLOT(RefreshClientIps()));
    this->connect(ui->ShowTabBarButton, SIGNAL(clicked(bool)), SLOT(ShowTabBar()));
    this->connect(ui->HideTabBarButton, SIGNAL(clicked(bool)), SLOT(HideTabBar()));
    this->connect(ui->DebugCodeButton, SIGNAL(clicked(bool)), SLOT(DebugCode()));
    this->connect(ui->ReleaseCodeButton, SIGNAL(clicked(bool)), SLOT(ReleaseCode()));
}

void MainWindow::SwitchVideoStream() {
    auto method = Function([&]() { this->RawSwitchVideoStream(); });
    ExceptionHandler(method, nullptr, nullptr);
}

void MainWindow::SwitchVideoCapture() {
    auto method = Function([&]() { this->RawSwitchVideoCapture(); });
    ExceptionHandler(method, nullptr, nullptr);
}

void MainWindow::TakeScreenshot() {
    auto method = Function([&]() { this->RawTakeScreenshot(); });
    ExceptionHandler(method, nullptr, nullptr);
}

void MainWindow::SwitchSendingCommands() {
    auto method = Function([&]() { this->RawSwitchSendingCommands(); });
    ExceptionHandler(method, nullptr, nullptr);
}

void MainWindow::SwitchToPage1() {
    ui->SettingsStackedWidget->setCurrentIndex(0);

    ui->SettingsPage1Button->setStyleSheet("color:rgb(255,255,255);\n"
                                           "\n"
                                           "background-color:rgb(60,60,60);\n"
                                           "\n"
                                           "border-width:1px;\n"
                                           "border-color :rgb(100,100,100);\n"
                                           "border-radius:5px;\n"
                                           "border-style:solid;");

    ui->SettingsPage2Button->setStyleSheet("color:rgb(255,255,255);\n"
                                           "\n"
                                           "background-color:rgb(45,45,45);\n"
                                           "\n"
                                           "border-width:1px;\n"
                                           "border-color :rgb(100,100,100);\n"
                                           "border-radius:5px;\n"
                                           "border-style:solid;");

    ui->SettingsPage3Button->setStyleSheet("color:rgb(255,255,255);\n"
                                           "\n"
                                           "background-color:rgb(45,45,45);\n"
                                           "\n"
                                           "border-width:1px;\n"
                                           "border-color :rgb(100,100,100);\n"
                                           "border-radius:5px;\n"
                                           "border-style:solid;");
}

void MainWindow::SwitchToPage2() {
    ui->SettingsStackedWidget->setCurrentIndex(1);

    ui->SettingsPage1Button->setStyleSheet("color:rgb(255,255,255);\n"
                                           "\n"
                                           "background-color:rgb(45,45,45);\n"
                                           "\n"
                                           "border-width:1px;\n"
                                           "border-color :rgb(100,100,100);\n"
                                           "border-radius:5px;\n"
                                           "border-style:solid;");

    ui->SettingsPage2Button->setStyleSheet("color:rgb(255,255,255);\n"
                                           "\n"
                                           "background-color:rgb(60,60,60);\n"
                                           "\n"
                                           "border-width:1px;\n"
                                           "border-color :rgb(100,100,100);\n"
                                           "border-radius:5px;\n"
                                           "border-style:solid;");

    ui->SettingsPage3Button->setStyleSheet("color:rgb(255,255,255);\n"
                                           "\n"
                                           "background-color:rgb(45,45,45);\n"
                                           "\n"
                                           "border-width:1px;\n"
                                           "border-color :rgb(100,100,100);\n"
                                           "border-radius:5px;\n"
                                           "border-style:solid;");
}

void MainWindow::SwitchToPage3() {
    ui->SettingsStackedWidget->setCurrentIndex(2);

    ui->SettingsPage1Button->setStyleSheet("color:rgb(255,255,255);\n"
                                           "\n"
                                           "background-color:rgb(45,45,45);\n"
                                           "\n"
                                           "border-width:1px;\n"
                                           "border-color :rgb(100,100,100);\n"
                                           "border-radius:5px;\n"
                                           "border-style:solid;");

    ui->SettingsPage2Button->setStyleSheet("color:rgb(255,255,255);\n"
                                           "\n"
                                           "background-color:rgb(45,45,45);\n"
                                           "\n"
                                           "border-width:1px;\n"
                                           "border-color :rgb(100,100,100);\n"
                                           "border-radius:5px;\n"
                                           "border-style:solid;");

    ui->SettingsPage3Button->setStyleSheet("color:rgb(255,255,255);\n"
                                           "\n"
                                           "background-color:rgb(60,60,60);\n"
                                           "\n"
                                           "border-width:1px;\n"
                                           "border-color :rgb(100,100,100);\n"
                                           "border-radius:5px;\n"
                                           "border-style:solid;");
}

void MainWindow::ReceiveRobotSettings() {
    auto method = Function([&]() { this->RawReceiveRobotSettings(); });
    ExceptionHandler(method, "Успех", "Настройки успешно приняты");
}

void MainWindow::SendRobotSettings() {
    auto method = Function([&]() { this->RawSendRobotSettings(); });
    ExceptionHandler(method, "Успех", "Настройки успешно отправлены");
}

void MainWindow::SaveClientSettings() {
    auto method = Function([&]() { this->RawSaveClientSettings(); });
    ExceptionHandler(method, "Сообщение", "Настройки успешно сохранены");
}

void MainWindow::LoadClientSettings() {
    auto method = Function([&]() { this->RawLoadClientSettings(); });
    ExceptionHandler(method, "Успех", "Настройки успешно загружены");
}

void MainWindow::RefreshGamepads() {
    auto gamepads = Control::GetGamepadsIds();
    ui->GamepadComboBox->clear();

    for (auto &&id: gamepads)
        ui->GamepadComboBox->addItem(QString::number(id));

    // The path to get the selected ID:
    // int id = ui->GamepadComboBox->itemText(ui->GamepadComboBox->currentIndex()).toInt()
}

void MainWindow::RefreshClientIps() {
    auto addresses = GetClientIps();
    ui->ClientIPComboBox->clear();
    for (auto &&address: addresses)
        ui->ClientIPComboBox->addItem(QString::fromStdString(address));

    // The path to get the selected IP:
    // QString ip = ui->ClientIPComboBox->itemText(ui->ClientIPComboBox->currentIndex());

}

void MainWindow::ShowTabBar() {
    /// Showing the TabBar
    ui->TabWidget->tabBar()->show();

    /// Showing all the buttons on the TabBar
    ui->HideTabBarButton->show();
    ui->CommandsProtocolButton->show();

    /// Hiding ShowTabBar button
    ui->ShowTabBarButton->hide();
}

void MainWindow::HideTabBar() {
    /// Hiding the TabBar
    ui->TabWidget->tabBar()->hide();

    /// Hiding all the buttons on the TabBar
    ui->HideTabBarButton->hide();
    ui->CommandsProtocolButton->hide();

    /// Showing ShowTabBar button
    ui->ShowTabBarButton->show();
}

void MainWindow::ReleaseCode() {
    Py_Initialize();

    ui->ProgressBar->setValue(25);

    PyObject *pyModule = PyImport_AddModule("__main__");

    std::string stdOutErr =
            "import sys\n"
            "class CatchOutErr:\n"
            "\tdef __init__(self):\n"
            "\t\tself.value = ''\n"
            "\tdef write(self, txt):\n"
            "\t\tself.value += txt\n"
            "catchOutErr = CatchOutErr()\n"
            "sys.stdout = catchOutErr\n"
            "sys.stderr = catchOutErr\n";

    PyRun_SimpleString(stdOutErr.c_str());

    const char *str = qPrintable(ui->CodeEdit->toPlainText());
    PyRun_SimpleString(str);

    ui->ProgressBar->setValue(50);

    PyObject *pyCatcher = PyObject_GetAttrString(pyModule, "catchOutErr");

    PyErr_Print();

    PyObject *pyOutput = PyObject_GetAttrString(pyCatcher, "value");

    ui->ProgressBar->setValue(75);

    PyObject *temp_bytes = PyUnicode_AsEncodedString(pyOutput, "UTF-8", "strict");
    std::string output = PyBytes_AS_STRING(temp_bytes);
    if (!output.empty()) {
        ui->OutputEdit->setText(output.c_str());
    }

    ui->ProgressBar->setValue(100);

    Py_Finalize();

    ui->ProgressBar->setValue(0);
}

void MainWindow::DebugCode() {
    Py_Initialize();

    ui->ProgressBar->setValue(25);

    const char *str = qPrintable(ui->CodeEdit->toPlainText());
    PyRun_SimpleString(str);

    ui->ProgressBar->setValue(100);

    Py_Finalize();

    ui->ProgressBar->setValue(0);
}