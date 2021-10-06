#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    this->_resources = new Resources();

    this->_commandsProtocol = new CommandsProtocol(0);
    this->_videoStream = new VideoProtocol();

    this->_updateTimer = new QTimer(this);
    connect(this->_updateTimer,SIGNAL(timeout()),this,SLOT(UpdateWidgets()));
    this->_updateTimer->start(1000/60);

    this->LoadClientSettings();

    this->SetupRendering();
    this->SetupButtons();
    this->SetupShortcuts();
}

MainWindow::~MainWindow() {
    delete this->ui;
    delete this->_commandsProtocol;
    delete this->_videoStream;
}
