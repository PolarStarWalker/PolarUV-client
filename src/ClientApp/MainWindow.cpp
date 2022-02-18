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

    /// Создание виджета авторизации
     authorizationWidget_ = CreateAuthorizationWidget(ui->AutorizationPage);

    /// Создание виджета камеры/телеметрии
    displayWidget_ = AddWidget<DisplayWidget>(ui->Page1);

    /// Создание виджета настроек робота
    robotSettingsWidget_ = AddWidget<RobotSettingsWidget>(ui->Page2_1);

    /// Создание виджета настроек клиента
    // ToDo: а где

    /// Создание виджета настроек управления
    controlSettingsWidget_ = AddWidget<ClientSettingsWidget>(ui->Page2_3);

    /// Создание виджета Python-среды
    pythonIDEWidget_ = AddWidget<PythonEnvironmentWidget>(ui->Page3);

    ///Создание виджета
    //commandsWidget_ = AddWidget<CommandsWidget>(ui->Page4);
    ///Создание виджета датчиков
    sensorsWidget_ = AddWidget<SensorsWidget>(ui->Page4);

    SetupSlots();
}

MainWindow::~MainWindow() {
    delete pythonIDEWidget_;
    delete controlSettingsWidget_;
    delete robotSettingsWidget_;
    delete displayWidget_;
    delete sensorsWidget_;

    ///Note: this widget must be delete last
    delete authorizationWidget_;

    delete ui;
}
