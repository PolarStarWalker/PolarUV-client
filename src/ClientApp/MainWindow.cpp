#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        isDebug_(false),
        ui(new Ui::MainWindow) {

    ui->setupUi(this);

    /// Установка иконки приложения
    setWindowIcon(QIcon("Icons/WindowIcon.png"));

    /// Установка иконок страниц
    ui->Page1Button->setIcon(QIcon("Icons/CameraIcon.png"));
    ui->Page2Button->setIcon(QIcon("Icons/SettingsIcon.png"));
    ui->Page3Button->setIcon(QIcon("Icons/CodeIcon.png"));
    ui->Page4Button->setIcon(QIcon("Icons/BugIcon.png"));

    /// Создание виджетов
    authorizationWidget_ = CreateAuthorizationWidget(ui->AutorizationPage);
    displayWidget_ = AddWidget<DisplayWidget>(ui->Page1);
    moveSettingsWidget_ = AddWidget<MoveSettingsWidget>(ui->P2_1_Widget_1);
    sensorsSettingsWidget_ = AddWidget<SensorsSettingsWidget>(ui->P2_1_Widget_2);
    commandsSettingsWidget_ = AddWidget<CommandsSettingsWidget>(ui->Page2_3);
    pythonIDEWidget_ = AddWidget<PythonEnvironmentWidget>(ui->Page3);
    //commandsWidget_ = AddWidget<CommandsWidget>(ui->Page4);
    sensorsWidget_ = AddWidget<SensorsWidget>(ui->Page4);

    SetupSlots();
}

MainWindow::~MainWindow() {
    delete pythonIDEWidget_;
    delete commandsSettingsWidget_;
    delete moveSettingsWidget_;
    delete displayWidget_;
    delete sensorsWidget_;

    ///Note: this widget must be delete last
    delete authorizationWidget_;

    delete ui;
}
