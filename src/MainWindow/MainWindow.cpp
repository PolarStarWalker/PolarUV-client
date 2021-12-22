#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    this->_mainWindowResources = MainWindowResources::GetInstance();

    this->_commandsProtocol = new CommandsProtocol(0, this);
    this->_videoStream = new VideoProtocol();

    this->_updateTimer = new QTimer(this);
    connect(this->_updateTimer, SIGNAL(timeout()), this, SLOT(UpdateWidgets()));
    this->_updateTimer->start(1000 / 60);

    this->_pitchIndicator = new PitchIndicator(ui->MainTab, this->_commandsProtocol);
    this->_yawIndicator = new YawIndicator(ui->MainTab, this->_commandsProtocol);
    this->_depthIndicator = new DepthIndicator(ui->MainTab, this->_commandsProtocol);

    this->SetupRendering();
    this->SetupButtons();
    this->SetupAnimations();
    this->SetupShortcuts();

    this->LoadClientSettings();
}

MainWindow::~MainWindow() {
    delete this->ui;
    delete this->_commandsProtocol;
    delete this->_videoStream;
}
