#include "MainWindow.hpp"
#include "./ui_mainwindow.h"
#include "Gamepad/Gamepad.hpp"

#define SERVER_IP "192.168.1.50" \
// 192.168.1.50 - motov.s
// 169.254.154.5 - shushkov.d
#define PORT 1999

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //Создание DataProtocol для Gamepad
    this->_gamepadDataProtocol = new DataProtocol(new Gamepad(0));
}

MainWindow::~MainWindow() {
    delete ui;
    delete this->_gamepadDataProtocol;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    /// Перемещаем виджет настроек
    int x = ((ui->centralwidget->width() - ui->SettingsWidget->width()) / 2) - 13;
    int y = ((ui->centralwidget->height() - ui->SettingsWidget->height()) / 2) - 29;
    int width = ui->SettingsWidget->width();
    int height = ui->SettingsWidget->height();
    ui->SettingsWidget->setGeometry(x, y, width, height);

    /// Место для перемещения еще чего-нибудь
}

void MainWindow::on_GamepadButton_clicked() {

}

void MainWindow::on_VideoStreamButton_clicked() {
    this->_stream.Start(pipeline);

}

void MainWindow::on_CommandsProtocolButton_clicked() {
    if (!_gamepadDataProtocol->IsOnline())
        _gamepadDataProtocol->StartAsync(SERVER_IP, PORT);
    else
        _gamepadDataProtocol->Stop();
}

void MainWindow::on_MotorsQuantitySpinBox_valueChanged(int value) {
    /// Изменяем высоту таблицы
    ui->MotorsTable->setFixedHeight((value * 26) + ((int) (value * 0.5))); // 26 - высота одной строки

    /// Перемещаем нижние линии
    int x = ui->MotorsBottomLeftLine->x();
    int y = ui->MotorsTable->y() + ui->MotorsTable->height();
    int width = ui->MotorsBottomLeftLine->width();
    int height = ui->MotorsBottomLeftLine->height();
    ui->MotorsBottomLeftLine->setGeometry(x, y, width, height);
    x = ui->MotorsBottomRightLine->x();
    ui->MotorsBottomRightLine->setGeometry(x, y, width, height);

    /// Изменяем высоту боковых линий
    height = ui->MotorsBottomLeftLine->y() - ui->MotorsTopLeftLine->y();
    ui->MotorsLeftLine->setFixedHeight(height);
    ui->MotorsRightLine->setFixedHeight(height);

    /// Устанавливаем число строк таблицы
    ui->MotorsTable->setRowCount(value);
}

void MainWindow::on_HandFreedomSpinBox_valueChanged(int value) {
    /// Изменяем ширину таблицы
    ui->HandTable->setFixedWidth((value * 49) + ((int) (value * 0.5))); // 49 - ширина одного столбца;

    /// Перемещаем таблицу ровно под надпись "Коэффициенты"
    int x = (ui->HandCoefficientsLabel->x() + (ui->HandCoefficientsLabel->width() / 2)) - (ui->HandTable->width() / 2);
    int y = ui->HandTable->y();
    int width = ui->HandTable->width();
    int height = ui->HandTable->height();
    ui->HandTable->setGeometry(x, y, width, height);

    /// Перемещаем боковые линии
    x = ui->HandTable->x() - 20;
    y = ui->HandLeftLine->y();
    width = ui->HandLeftLine->width();
    height = ui->HandLeftLine->height();
    ui->HandLeftLine->setGeometry(x, y, width, height);
    x = ui->HandTable->x() + ui->HandTable->width();
    ui->HandRightLine->setGeometry(x, y, width, height);

    /// Перемещаем верхние и нижние линии
    x = ui->HandLeftLine->x() + 9;
    y = ui->HandTopLeftLine->y();
    width = ui->HandTopLeftLine->width();
    height = ui->HandTopLeftLine->height();
    ui->HandTopLeftLine->setGeometry(x, y, width, height);
    y = ui->HandBottomLeftLine->y();
    ui->HandBottomLeftLine->setGeometry(x, y, width, height);
    x = ui->HandRightLine->x() - 9;
    y = ui->HandTopRightLine->y();
    ui->HandTopRightLine->setGeometry(x, y, width, height);
    y = ui->HandBottomRightLine->y();
    ui->HandBottomRightLine->setGeometry(x, y, width, height);

    /// Устанавливаем число столбцов таблицы
    ui->HandTable->setColumnCount(value);
}