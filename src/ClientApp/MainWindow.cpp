#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {

    ui->setupUi(this);

    /// Установка иконок
    ui->Page1Button->setIcon(QIcon("Icons/CameraIcon.png"));
    ui->Page2Button->setIcon(QIcon("Icons/SettingsIcon.png"));
    ui->Page3Button->setIcon(QIcon("Icons/CodeIcon.png"));
    ui->Page4Button->setIcon(QIcon("Icons/BugIcon.png"));

//    /// Создание виджетов индикаторов
//    _pitchIndicator = std::make_unique<PitchIndicator>(ui->MainTab, *_commandsProtocol);
//    _yawIndicator = std::make_unique<YawIndicator>(ui->MainTab, *_commandsProtocol);
//    _depthIndicator = std::make_unique<DepthIndicator>(ui->MainTab, *_commandsProtocol);

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

    commandsWidget_ = AddWidget<CommandsWidget>(ui->Page4);

    // ToDo: решить судьбу виджета (возможно убрать)
    ui->Page3Button->hide();

//    /// Создание таймера отрисовки
//    _updateTimer = std::make_unique<QTimer>(this);
//    connect(this->_updateTimer.get(), SIGNAL(timeout()), this, SLOT(UpdateWidgets()));
//    this->_updateTimer->start(1000 / 60);

    SetupSlots();
}

MainWindow::~MainWindow() {
    delete pythonIDEWidget_;
    delete controlSettingsWidget_;
    delete robotSettingsWidget_;
    delete displayWidget_;

    ///Note: this widget must be delete last
    delete authorizationWidget_;
}

inline AuthorizationWidget* MainWindow::CreateAuthorizationWidget(QWidget* dst) {
    auto widget = new AuthorizationWidget(this);
    dst->layout()->addWidget(widget);
    return  widget;
}
