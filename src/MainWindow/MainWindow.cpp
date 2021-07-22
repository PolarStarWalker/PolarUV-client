#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

#define SERVER_IP "192.168.1.50"
#define PORT 1999

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->_dataProtocolThread = new QThread(this);

    //connect(this, SIGNAL(destroyed()), this->_dataProtocolThread, SLOT(quit()));


    this->_dataProtocol = new DataProtocol;

   //this->_dataProtocol->moveToThread(this->_dataProtocolThread);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->_dataProtocol;
}

void MainWindow::on_GamepadButton_clicked() {

}

void MainWindow::on_VideoStreamButton_clicked() {
    this->_stream.Start(pipeline);

}

void MainWindow::on_CommandsProtocolButton_clicked() {
    if (!_dataProtocol->IsOnline())
        _dataProtocol->StartAsync(SERVER_IP, PORT);
    else
        _dataProtocol->Stop();
}