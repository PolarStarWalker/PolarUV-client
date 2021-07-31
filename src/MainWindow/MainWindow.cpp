#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->_gamepad = new Control::Gamepad(0);

    //Создание DataProtocol для Gamepad
    this->_gamepadDataProtocol = new DataProtocol(this->_gamepad);
}

MainWindow::~MainWindow() {
    delete ui;
    delete this->_gamepadDataProtocol;
}

void MainWindow::on_GamepadButton_clicked() {

}

void MainWindow::on_VideoStreamButton_clicked() {
    this->_stream.Start(pipeline);

}

void MainWindow::on_CommandsProtocolButton_clicked() {
    if (!_gamepadDataProtocol->IsOnline())
        _gamepadDataProtocol->StartAsync(ui->IPEdit->text(), PORT);
    else
        _gamepadDataProtocol->Stop();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    /// Изменяем размеры TabWidget
    ui->TabWidget->setGeometry(ui->MainWidget->geometry());

    /// Перемещаем кнопку "Полный экран"
    ui->FullScreenButton->move(ui->MainWidget->width() - ui->FullScreenButton->width(),0);

    /// Перемещаем надпись "Статус подключения"
    int offset = 190; // Расстояние от правого края окна до надписи
    ui->StatusLabel->move(ui->MainWidget->width() - ui->StatusLabel->width() - offset, 0);

    /// Рисуем кружок статуса
    offset = 10; // Расстояние от надписи до центра окружности
    QPainter painter(this);
    QPoint point(ui->StatusLabel->x() + ui->StatusLabel->width() + offset, 13);
    painter.setPen(Qt::NoPen); // Не рисовать границы
    painter.setBrush(QBrush("#ff0000"));
    painter.drawEllipse(point, 7, 7);

    /// Перемещаем виджет настроек робота
    offset = 30; // Расстояние между виджетами по горизонтали
    int x = (ui->tab_3->width() - (ui->RobotSettingsWidget->width() + ui->ClientSettingsWidget->width() + offset)) / 2;
    int y = (ui->tab_3->height() - ui->RobotSettingsWidget->height()) / 2;
    ui->RobotSettingsWidget->move(x, y);

    /// Перемещаем виджет настроек клиента
    x = ui->RobotSettingsWidget->x() + ui->RobotSettingsWidget->width() + offset;
    ui->ClientSettingsWidget->move(x, y);

    /// Перемещаем заголовок виджета настроек робота
    x = ui->RobotSettingsWidget->x() + ui->RobotSettingsWidget->width() / 2 - ui->RobotSettingsLabel->width() / 2;
    y = ui->RobotSettingsWidget->y() - ui->RobotSettingsLabel->height() / 2;
    ui->RobotSettingsLabel->move(x, y);

    /// Перемещаем заголовок виджета настроек клиента
    x = ui->ClientSettingsWidget->x() + ui->ClientSettingsWidget->width() / 2 - ui->ClientSettingsLabel->width() / 2;
    y = ui->ClientSettingsWidget->y() - ui->ClientSettingsLabel->height() / 2;
    ui->ClientSettingsLabel->move(x, y);

    /// Перемещаем рамку заголовка виджета настроек робота
    ui->RobotSettingsLabelFrame->setGeometry(ui->RobotSettingsLabel->geometry());

    /// Перемещаем рамку заголовка виджета настроек клиента
    ui->ClientSettingsLabelFrame->setGeometry(ui->ClientSettingsLabel->geometry());
}

void MainWindow::on_FullScreenButton_clicked() {
    if (this->windowState() == Qt::WindowFullScreen) {
        this->setWindowState(Qt::WindowNoState);
    }
    else {
        this->setWindowState(Qt::WindowFullScreen);
    }
}

void MainWindow::on_MotorsQuantitySpinBox_valueChanged(int value) {
    /// Изменяем высоту таблицы
    ui->MotorsTable->setFixedHeight((value * 26) + ((int) (value * 0.5))); // 26 - высота одной строки

    /// Перемещаем нижние линии
    int x = ui->MotorsBottomLeftLine->x();
    int y = ui->MotorsTable->y() + ui->MotorsTable->height();
    ui->MotorsBottomLeftLine->move(x, y);
    x = ui->MotorsBottomRightLine->x();
    ui->MotorsBottomRightLine->move(x, y);

    /// Изменяем высоту боковых линий
    int height = ui->MotorsBottomLeftLine->y() - ui->MotorsTopLeftLine->y();
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
    ui->HandTable->move(x, y);

    /// Перемещаем боковые линии
    x = ui->HandTable->x() - 20;
    y = ui->HandLeftLine->y();
    ui->HandLeftLine->move(x, y);
    x = ui->HandTable->x() + ui->HandTable->width();
    ui->HandRightLine->move(x, y);

    /// Перемещаем верхние и нижние линии
    x = ui->HandLeftLine->x() + 9;
    y = ui->HandTopLeftLine->y();
    ui->HandTopLeftLine->move(x, y);
    y = ui->HandBottomLeftLine->y();
    ui->HandBottomLeftLine->move(x, y);
    x = ui->HandRightLine->x() - 9;
    y = ui->HandTopRightLine->y();
    ui->HandTopRightLine->move(x, y);
    y = ui->HandBottomRightLine->y();
    ui->HandBottomRightLine->move(x, y);

    /// Устанавливаем число столбцов таблицы
    ui->HandTable->setColumnCount(value);
}