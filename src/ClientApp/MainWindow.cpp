#include "MainWindow.hpp"

#include <memory>
#include "./ui_mainwindow.h"
#include <Exceptions/ExceptionHandler.hpp>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),

        _networkThread(std::make_unique<QThread>()),

        //signletones
        _mainWindowResources(MainWindowResources::GetInstance()),
        _network(lib::network::TcpSession::GetInstance()),

        //Protocols
        _commandsProtocol(std::make_unique<CommandsProtocol>(0, this)),
        _videoStream(std::make_unique<VideoProtocol>()),
        _updateTimer(std::make_unique<QTimer>(this)),

        /// Создание виджетов индикаторов
        _pitchIndicator(std::make_unique<PitchIndicator>(ui->MainTab, _commandsProtocol.get())),
        _yawIndicator(std::make_unique<YawIndicator>(ui->MainTab, _commandsProtocol.get())),
        _depthIndicator(std::make_unique<DepthIndicator>(ui->MainTab, this->_commandsProtocol.get())){


    ui->setupUi(this);

    /// Создание виджета настроек робота
    _robotSettingWidget = std::make_unique<RobotSettingsWidget>(ui->tab);

    _network.moveToThread(_networkThread.get());
    _networkThread->start();

    connect(this->_updateTimer.get(), SIGNAL(timeout()), this, SLOT(UpdateWidgets()));
    this->_updateTimer->start(1000 / 60);

    this->SetupRendering();
    this->SetupButtons();
    this->SetupAnimations();
    this->SetupShortcuts();

    ExceptionHandler(nullptr, nullptr, [&]() { this->RawLoadClientSettings(); });
}
