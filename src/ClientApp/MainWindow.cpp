#include "MainWindow.hpp"

#include <memory>
#include "./ui_mainwindow.h"
#include <Exceptions/ExceptionHandler.hpp>


void foo(int a, int b){
    std::clog << a + b<<std::endl;
    throw lib::exceptions::InvalidOperationException("");
}


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),

        //signletones
        _mainWindowResources(MainWindowResources::GetInstance()),
        _network(lib::network::TcpSession::GetInstance()) {

    ui->setupUi(this);

    /// Установка фильтра событий
    this->installEventFilter(this);

    ///Protocols
    _commandsProtocol = std::make_unique<CommandsProtocol>(0, this);
    _videoStream = std::make_unique<VideoProtocol>();

    /// Создание виджетов индикаторов
    _pitchIndicator = std::make_unique<PitchIndicator>(ui->MainTab, *_commandsProtocol);
    _yawIndicator = std::make_unique<YawIndicator>(ui->MainTab, *_commandsProtocol);
    _depthIndicator = std::make_unique<DepthIndicator>(ui->MainTab, *_commandsProtocol);

    /// Создание виджета настроек робота
    _robotSettingsWidget = std::make_unique<RobotSettingsWidget>(ui->TestTab1);
    connect(this, SIGNAL(SizeChanged(QSize)),
            this->_robotSettingsWidget.get(),SLOT(UpdateGeometry(QSize)));

    /// Создание виджета настроек клиента
    _clientSettingsWidget = std::make_unique<ClientSettingsWidget>(ui->TestTab2);
    connect(this, SIGNAL(SizeChanged(QSize)),
            this->_clientSettingsWidget.get(),SLOT(UpdateGeometry(QSize)));

    /// Создание виджета Python-среды
    _pythonEnvironmentWidget = std::make_unique<PythonEnvironmentWidget>(ui->PythonTab);
    connect(this, SIGNAL(SizeChanged(QSize)),
            this->_pythonEnvironmentWidget.get(),SLOT(UpdateGeometry(QSize)));

    this->resize(this->width(),this->height());

    /// Создание таймера отрисовки
    _updateTimer = std::make_unique<QTimer>(this);
    connect(this->_updateTimer.get(), SIGNAL(timeout()), this, SLOT(UpdateWidgets()));
    this->_updateTimer->start(1000 / 60);

    this->SetupRendering();
    this->SetupButtons();
    this->SetupAnimations();
    this->SetupShortcuts();

    ExceptionHandler(nullptr, nullptr, [&]() { this->RawLoadClientSettings(); });
}
