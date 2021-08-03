#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->_widgetsPlaced = false;

    //Создание CommandsProtocol для Gamepad
    this->_commandsProtocol = new CommandsProtocol(0);

    //Запуск таймера отрисовки окна
    this->startTimer(1000/60,Qt::PreciseTimer);
}

MainWindow::~MainWindow() {
    delete ui;
    delete this->_commandsProtocol;
}

void MainWindow::on_GamepadButton_clicked() {

}

void MainWindow::on_VideoStreamButton_clicked() {
    this->_video.Start(pipeline);

}

void MainWindow::on_CommandsProtocolButton_clicked() {
    if (!_commandsProtocol->IsOnline())
        _commandsProtocol->StartAsync(ui->IPEdit->text(), PORT);
    else
        _commandsProtocol->Stop();
}

void  MainWindow::on_ReceiveSettingsButton_clicked() {

}

void  MainWindow::on_SendSettingsButton_clicked() {
    SettingsStruct settingsStruct;

    /// Считываем коэффициенты двигателей
    std::vector<double> motorsVector(ui->MotorsTable->rowCount() * 6);
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            motorsVector[i * 6 + j] = ui->MotorsTable->item(i,j)->text().toDouble();
        }
    }
    settingsStruct.SetMoveCoefficientArray(motorsVector);

    /// Считываем коэффициенты манипулятора
    std::vector<double> handVector(ui->HandTable->columnCount());
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        handVector[j] = ui->MotorsTable->item(0,j)->text().toDouble();
    }
    settingsStruct.SetHandCoefficientArray(handVector);

    /// Считываем максимальную скорость двигателей
    settingsStruct.MaxMotorSpeed = ui->MaxSpeedEdit->text().toInt();

    /// Считываем протокол двигателей
    switch (ui->MotorsProtocolComboBox->currentIndex()) {
        case 0: settingsStruct.MotorsProtocol = DShotMode::DShot150; break;
        case 1: settingsStruct.MotorsProtocol = DShotMode::DShot300; break;
        case 2: settingsStruct.MotorsProtocol = DShotMode::DShot600; break;
        case 3: settingsStruct.MotorsProtocol = DShotMode::DShot1200; break;
    }

    //Временный вывод настроек в консоль
    std::cout << settingsStruct;

    /// ToDo: отправка настроек роботу

    QMessageBox::information(this,"Сообщение","Настройки успешно отправлены");
}

void MainWindow::placeWidgets() {
    /// Изменяем размеры TabWidget
    ui->TabWidget->setGeometry(ui->MainWidget->geometry());

    /// Перемещаем кнопку "Полный экран"
    ui->FullScreenButton->move(ui->MainWidget->width() - ui->FullScreenButton->width(),0);

    /// Перемещаем надпись "Статус подключения"
    int offset = 190; // Расстояние от правого края окна до надписи
    ui->StatusLabel->move(ui->MainWidget->width() - ui->StatusLabel->width() - offset, 0);

    /// Перемещаем виджет настроек робота
    offset = 30; // Расстояние между виджетами по горизонтали
    int x = (ui->tab_3->width() - (ui->RobotSettingsWidget->width() + ui->ClientSettingsWidget->width() + offset)) / 2;
    int y = (ui->tab_3->height() - ui->RobotSettingsWidget->height()) / 2;
    ui->RobotSettingsWidget->move(x, y);

    /// Перемещаем виджет настроек клиента
    x = ui->RobotSettingsWidget->x() + ui->RobotSettingsWidget->width() + offset;
    ui->ClientSettingsWidget->move(x, y);

    /// Перемещаем виджет назначения кнопок
    x = (ui->tab_4->width() - ui->KeyAssignmentsWidget->width()) / 2;
    y = (ui->tab_4->height() - ui->KeyAssignmentsWidget->height()) / 2;
    ui->KeyAssignmentsWidget->move(x, y);

    /// Перемещаем заголовок виджета настроек робота
    x = ui->RobotSettingsWidget->x() + ui->RobotSettingsWidget->width() / 2 - ui->RobotSettingsLabel->width() / 2;
    y = ui->RobotSettingsWidget->y() - ui->RobotSettingsLabel->height() / 2;
    ui->RobotSettingsLabel->move(x, y);

    /// Перемещаем заголовок виджета настроек клиента
    x = ui->ClientSettingsWidget->x() + ui->ClientSettingsWidget->width() / 2 - ui->ClientSettingsLabel->width() / 2;
    y = ui->ClientSettingsWidget->y() - ui->ClientSettingsLabel->height() / 2;
    ui->ClientSettingsLabel->move(x, y);

    /// Перемещаем заголовок виджета назначения кнопок
    x = ui->KeyAssignmentsWidget->x() + ui->KeyAssignmentsWidget->width() / 2 - ui->KeyAssignmentsLabel->width() / 2;
    y = ui->KeyAssignmentsWidget->y() - ui->KeyAssignmentsLabel->height() / 2;
    ui->KeyAssignmentsLabel->move(x, y);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    /// Если это первая отрисовка с момента запуска программы, то размещаем виджеты
    if (!this->_widgetsPlaced) this->placeWidgets();

    /// Рисуем кружок статуса
    int offset = 10; // Расстояние от надписи до центра окружности
    QPainter painter(this);
    QPoint point(ui->StatusLabel->x() + ui->StatusLabel->width() + offset, 13);
    painter.setPen(Qt::NoPen); // Не рисовать границы
    if (this->_commandsProtocol->IsOnline())
        painter.setBrush(QBrush("#008000")); // Зеленый
    else
        painter.setBrush(QBrush("#ff0000")); // Красный
    painter.drawEllipse(point, 7, 7);
}

void MainWindow::timerEvent(QTimerEvent *event) {
    this->repaint();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    this->placeWidgets();
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

    /// Заполняем пустые ячейки нулями
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            if (ui->MotorsTable->item(i,j) == nullptr) {
                ui->MotorsTable->setItem(i,j,new QTableWidgetItem("0"));
            }
        }
    }
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

    /// Заполняем пустые ячейки нулями
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        if (ui->HandTable->item(0,j) == nullptr) {
            ui->HandTable->setItem(0,j,new QTableWidgetItem("0"));
        }
    }
}