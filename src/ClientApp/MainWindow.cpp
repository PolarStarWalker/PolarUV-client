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
    authorizationWidget_ = CreateAuthorizationWidget(ui->AuthorizationPage);
    displayWidget_ = AddWidget<DisplayWidget>(ui->Page1);
    moveSettingsWidget_ = AddWidget<MoveSettingsWidget>(ui->P2_1Widget);
    commandsSettingsWidget_ = AddWidget<CommandsSettingsWidget>(ui->P2_2Widget);
    sensorsSettingsWidget_ = AddWidget<SensorsSettingsWidget>(ui->P2_3Widget);
    //pythonIDEWidget_ = AddWidget<PythonEnvironmentWidget>(ui->Page3);
    //commandsWidget_ = AddWidget<CommandsWidget>(ui->Page4);
    //sensorsWidget_ = AddWidget<SensorsWidget>(ui->Page4);

    /// Прячем пустые вкладки ToDo: заполнить вкладки
    ui->Page3Button->hide();
    ui->Page4Button->hide();

    SetupSlots();
}

MainWindow::~MainWindow() {
    delete displayWidget_;
    delete moveSettingsWidget_;
    delete commandsSettingsWidget_;
    delete sensorsSettingsWidget_;
    delete pythonIDEWidget_;
    delete sensorsWidget_;

    ///Note: this widget must be delete last
    delete authorizationWidget_;

    delete ui;
}
