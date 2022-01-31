#include "MainWindow.hpp"

#include <memory>
#include "./ui_mainwindow.h"
#include <Exceptions/ExceptionHandler.hpp>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {

    ui->setupUi(this);

    /// Установка иконок
    ui->Page1Button->setIcon(QIcon("Icons/CameraIcon.png"));
    ui->Page2Button->setIcon(QIcon("Icons/SettingsIcon.png"));
    ui->Page3Button->setIcon(QIcon("Icons/CodeIcon.png"));
    ui->Page4Button->setIcon(QIcon("Icons/BugIcon.png"));
    ui->SideBarButton->setIcon(QIcon("Icons/HamburgerIcon.png"));

//    /// Создание виджетов индикаторов
//    _pitchIndicator = std::make_unique<PitchIndicator>(ui->MainTab, *_commandsProtocol);
//    _yawIndicator = std::make_unique<YawIndicator>(ui->MainTab, *_commandsProtocol);
//    _depthIndicator = std::make_unique<DepthIndicator>(ui->MainTab, *_commandsProtocol);

    /// Создание виджета авторизации
    autorizationWidget_ = std::make_unique<AutorizationWidget>(this);
    ui->AutorizationPage->layout()->addWidget(autorizationWidget_.get());

    /// Создание виджета камеры/телеметрии
    displayWidget_ = std::make_unique<DisplayWidget>(this);
    ui->Page1->layout()->addWidget(displayWidget_.get());

    /// Создание виджета настроек робота
    robotSettingsWidget_ = std::make_unique<RobotSettingsWidget>();
    ui->Page2_1->layout()->addWidget(robotSettingsWidget_.get());

    /// Создание виджета настроек клиента
    // ToDo: а где

    /// Создание виджета настроек управления
    controlSettingsWidget_ = std::make_unique<ClientSettingsWidget>();
    ui->Page2_3->layout()->addWidget(controlSettingsWidget_.get());

    /// Создание виджета Python-среды
    pythonIDEWidget_ = std::make_unique<PythonEnvironmentWidget>();
    ui->Page3->layout()->addWidget(pythonIDEWidget_.get());
    // ToDo: решить судьбу виджета (возможно убрать)
    ui->Page3Button->hide();

//    /// Создание таймера отрисовки
//    _updateTimer = std::make_unique<QTimer>(this);
//    connect(this->_updateTimer.get(), SIGNAL(timeout()), this, SLOT(UpdateWidgets()));
//    this->_updateTimer->start(1000 / 60);

    SetupSlots();
}
