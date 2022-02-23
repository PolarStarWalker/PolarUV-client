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
    displayWidget_ = CreateWidgetWithResources<DisplayWidget>(ui->Page1);
    moveSettingsWidget_ = CreateWidgetWithResources<MoveSettingsWidget>(ui->P2_1Widget);
    commandsSettingsWidget_ = CreateWidget<CommandsSettingsWidget>(ui->P2_2Widget);
    sensorsSettingsWidget_ = CreateWidget<SensorsSettingsWidget>(ui->P2_3Widget);
    //pythonIDEWidget_ = CreateWidgetWithResources<PythonEnvironmentWidget>(ui->Page3);
    commandsObject_ = CreateObjectWithResources<CommandsWidget>();
    sensorsObject_ = CreateObjectWithResources<SensorsWidget>();

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
    delete sensorsObject_;

    ///Note: this widget must be delete last
    delete authorizationWidget_;

    delete ui;
}
