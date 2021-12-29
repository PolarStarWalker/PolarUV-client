#include "MainWindow.hpp"

#include <memory>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    this->_mainWindowResources = MainWindowResources::GetInstance();

    this->_commandsProtocol = std::make_unique<CommandsProtocol>(0, this);
    this->_videoStream = std::make_unique<VideoProtocol>();

    this->_updateTimer = std::make_unique<QTimer>(this);

    connect(this->_updateTimer.get(), SIGNAL(timeout()), this, SLOT(UpdateWidgets()));
    this->_updateTimer->start(1000 / 60);

    this->_pitchIndicator = std::make_unique<PitchIndicator>(ui->MainTab, this->_commandsProtocol.get());
    this->_yawIndicator = std::make_unique<YawIndicator>(ui->MainTab, this->_commandsProtocol.get());
    this->_depthIndicator = std::make_unique<DepthIndicator>(ui->MainTab, this->_commandsProtocol.get());

    this->SetupRendering();
    this->SetupButtons();
    this->SetupAnimations();
    this->SetupShortcuts();

    this->LoadClientSettings();
}
