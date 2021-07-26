#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

#define SERVER_IP "169.254.154.5" // 192.168.1.50 - motov.s
                                  // 169.254.154.5 - shushkov.d
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

void MainWindow::resizeEvent(QResizeEvent *event) {
    /// Изменяем размеры TabWidget
    ui->TabWidget->setGeometry(ui->MainWidget->geometry());

    /// Перемещаем кнопки закрытия и сворачивания программы
    ui->WindowCloseButton->move(ui->MainWidget->width() - ui->WindowCloseButton->width(),0);
    ui->WindowMinimizeButton->move(ui->WindowCloseButton->x() - ui->WindowMinimizeButton->width(),0);

    /// Перемещаем виджет настроек
    int x = ((ui->MainWidget->width() - ui->SettingsWidget->width()) / 2);
    int y = ((ui->MainWidget->height() - ui->SettingsWidget->height()) / 2);
    ui->SettingsWidget->move(x,y);
}

void MainWindow::changeEvent(QEvent *event) {
    /// Отлавливаем момент разворачивания окна и заставляем его развернуться на весь экран
    if (event->type() == QEvent::WindowStateChange) {
        auto* stateChangeEvent = dynamic_cast<QWindowStateChangeEvent*>(event);
        if (stateChangeEvent->oldState() == Qt::WindowMinimized) {
            this->setWindowState(Qt::WindowFullScreen);
        }
    }
}

void MainWindow::on_WindowCloseButton_clicked() {
    this->close();
}

void MainWindow::on_WindowMinimizeButton_clicked() {
    this->setWindowState(Qt::WindowMinimized);
}

void MainWindow::on_MotorsQuantitySpinBox_valueChanged(int value) {
    /// Изменяем высоту таблицы
    ui->MotorsTable->setFixedHeight((value * 26) + ((int)(value * 0.5))); // 26 - высота одной строки

    /// Перемещаем нижние линии
    int x = ui->MotorsBottomLeftLine->x();
    int y = ui->MotorsTable->y() + ui->MotorsTable->height();
    ui->MotorsBottomLeftLine->move(x,y);
    x = ui->MotorsBottomRightLine->x();
    ui->MotorsBottomRightLine->move(x,y);

    /// Изменяем высоту боковых линий
    int height = ui->MotorsBottomLeftLine->y() - ui->MotorsTopLeftLine->y();
    ui->MotorsLeftLine->setFixedHeight(height);
    ui->MotorsRightLine->setFixedHeight(height);

    /// Устанавливаем число строк таблицы
    ui->MotorsTable->setRowCount(value);
}

void MainWindow::on_HandFreedomSpinBox_valueChanged(int value) {
    /// Изменяем ширину таблицы
    ui->HandTable->setFixedWidth((value * 49) + ((int)(value * 0.5))); // 49 - ширина одного столбца;

    /// Перемещаем таблицу ровно под надпись "Коэффициенты"
    int x = (ui->HandCoefficientsLabel->x() + (ui->HandCoefficientsLabel->width() / 2)) - (ui->HandTable->width() / 2);
    int y = ui->HandTable->y();
    ui->HandTable->move(x,y);

    /// Перемещаем боковые линии
    x = ui->HandTable->x() - 20;
    y = ui->HandLeftLine->y();
    ui->HandLeftLine->move(x,y);
    x = ui->HandTable->x() + ui->HandTable->width();
    ui->HandRightLine->move(x,y);

    /// Перемещаем верхние и нижние линии
    x = ui->HandLeftLine->x() + 9;
    y = ui->HandTopLeftLine->y();
    ui->HandTopLeftLine->move(x,y);
    y = ui->HandBottomLeftLine->y();
    ui->HandBottomLeftLine->move(x,y);
    x = ui->HandRightLine->x() - 9;
    y = ui->HandTopRightLine->y();
    ui->HandTopRightLine->move(x,y);
    y = ui->HandBottomRightLine->y();
    ui->HandBottomRightLine->move(x,y);

    /// Устанавливаем число столбцов таблицы
    ui->HandTable->setColumnCount(value);
}