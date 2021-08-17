#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    this->_commandsProtocol = new CommandsProtocol(0);
    this->_videoStream = new VideoProtocol();

    this->loadClientSettings();

    this->setupRendering();
    this->setupButtons();
    this->setupShortcuts();
}

MainWindow::~MainWindow() {
    delete this->ui;
    delete this->_commandsProtocol;
    delete this->_videoStream;
}
