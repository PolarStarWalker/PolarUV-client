#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->_widgetsPlaced = false;

    //Создание CommandsProtocol для Gamepad
    this->_commandsProtocol = new CommandsProtocol(0);

    this->_settingsProtocol = new SettingsProtocol();

    //Запуск таймера отрисовки окна
    this->startTimer(1000 / 60, Qt::PreciseTimer);

    //Загрузка настроек клиента из файла
    loadClientSettings();
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
        _commandsProtocol->StartAsync(ui->IPEdit->text(), COMMANDS_PORT);
    else
        _commandsProtocol->Stop();
}

void MainWindow::on_ReceiveSettingsButton_clicked() {
    /// Временные "входные" данные
    /// ToDo: заменить на прием структуры по протоколу
    std::vector<double> motorsVector = {1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1};
    std::vector<double> handVector = {1, 2, 3, 4, 5};
    int32_t maxMotorSpeed = 3000;
    int8_t motorsProtocol = 4;
    RobotSettingsStruct robotSettingsStruct;
    robotSettingsStruct.SetMoveCoefficientArray(motorsVector);
    robotSettingsStruct.SetHandCoefficientArray(handVector);
    robotSettingsStruct.MaxMotorSpeed = maxMotorSpeed;
    robotSettingsStruct.MotorsProtocol = motorsProtocol;

    /// Выводим количество двигателей
    std::vector<double> moveCoefficientVector = robotSettingsStruct.GetMoveCoefficientVector();
    int motorsNumber = (int) (moveCoefficientVector.size() / 6);
    ui->MotorsNumberSpinBox->setValue(motorsNumber);

    /// Выводим коэффициенты двигателей
    for (int i = 0; i < motorsNumber; i++) {
        for (int j = 0; j < 6; j++) {
            QString itemText = QString::number(moveCoefficientVector[i * 6 + j]);
            ui->MotorsTable->setItem(i, j, new QTableWidgetItem(itemText));
        }
    }

    /// Выводим число степеней свободы манипулятора
    std::vector<double> handCoefficientVector = robotSettingsStruct.GetHandCoefficientVector();
    int handFreedom = (int) (handCoefficientVector.size());
    ui->HandFreedomSpinBox->setValue(handFreedom);

    /// Выводим коэффициенты манипулятора
    for (int j = 0; j < handFreedom; j++) {
        QString itemText = QString::number(handCoefficientVector[j]);
        ui->HandTable->setItem(0, j, new QTableWidgetItem(itemText));
    }

    /// Выводим максимальную скорость двигателей
    ui->MaxSpeedEdit->setText(QString::number(robotSettingsStruct.MaxMotorSpeed));

    /// Выводим протокол двигателей
    switch (robotSettingsStruct.MotorsProtocol) {
        case 1:
            ui->MotorsProtocolComboBox->setCurrentIndex(0);
            break;
        case 2:
            ui->MotorsProtocolComboBox->setCurrentIndex(1);
            break;
        case 4:
            ui->MotorsProtocolComboBox->setCurrentIndex(2);
            break;
        case 8:
            ui->MotorsProtocolComboBox->setCurrentIndex(3);
            break;
    }

    QMessageBox::information(this, "Сообщение", "Настройки успешно получены");
}

void MainWindow::on_SendSettingsButton_clicked() {
    RobotSettingsStruct robotSettingsStruct;

    /// Считываем коэффициенты двигателей
    std::vector<double> motorsVector(ui->MotorsTable->rowCount() * 6);
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            motorsVector[i * 6 + j] = ui->MotorsTable->item(i, j)->text().toDouble();
        }
    }
    robotSettingsStruct.SetMoveCoefficientArray(motorsVector);

    /// Считываем коэффициенты манипулятора
    std::vector<double> handVector(ui->HandTable->columnCount());
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        handVector[j] = ui->MotorsTable->item(0, j)->text().toDouble();
    }
    robotSettingsStruct.SetHandCoefficientArray(handVector);

    /// Считываем максимальную скорость двигателей
    robotSettingsStruct.MaxMotorSpeed = ui->MaxSpeedEdit->text().toInt();

    /// Считываем протокол двигателей
    switch (ui->MotorsProtocolComboBox->currentIndex()) {
        case 0:
            robotSettingsStruct.MotorsProtocol = DShotMode::DShot150;
            break;
        case 1:
            robotSettingsStruct.MotorsProtocol = DShotMode::DShot300;
            break;
        case 2:
            robotSettingsStruct.MotorsProtocol = DShotMode::DShot600;
            break;
        case 3:
            robotSettingsStruct.MotorsProtocol = DShotMode::DShot1200;
            break;
    }

    //Временный вывод настроек в консоль
    std::cout << robotSettingsStruct;

    /// Отправка настроек роботу
    this->_settingsProtocol->SendAsync(ui->IPEdit->text(), SETTINGS_PORT, std::move(robotSettingsStruct));

    QMessageBox::information(this, "Сообщение", "Настройки успешно отправлены");
}

void MainWindow::on_SaveClientSettingsButton_clicked() {
    ClientSettingsStruct settings;

    settings.leftShoulderActionID = ui->LeftShoulderComboBox->currentIndex();
    settings.rightShoulderActionID = ui->RightShoulderComboBox->currentIndex();
    settings.leftStickXActionID = ui->LeftStickXComboBox->currentIndex();
    settings.leftStickYActionID = ui->LeftStickYComboBox->currentIndex();
    settings.leftStickPressActionID = ui->LeftStickPressComboBox->currentIndex();
    settings.rightStickXActionID = ui->RightStickXComboBox->currentIndex();
    settings.rightStickYActionID = ui->RightStickYComboBox->currentIndex();
    settings.rightStickPressActionID = ui->RightStickPressComboBox->currentIndex();
    settings.dPadXActionID = ui->DPadXComboBox->currentIndex();
    settings.dPadYActionID = ui->DPadYComboBox->currentIndex();
    settings.triangleActionID = ui->TriangleComboBox->currentIndex();
    settings.crossActionID = ui->CrossComboBox->currentIndex();
    settings.rectangleActionID = ui->RectangleComboBox->currentIndex();
    settings.circleActionID = ui->CircleComboBox->currentIndex();
    settings.startActionID = ui->StartComboBox->currentIndex();
    settings.backActionID = ui->BackComboBox->currentIndex();

    settings.Save();

    QMessageBox::information(this,"Сообщение","Настройки успешно сохранены");
}

void MainWindow::loadClientSettings() {
    ClientSettingsStruct settings;

    settings.Load();

    ui->LeftShoulderComboBox->setCurrentIndex(settings.leftShoulderActionID);
    ui->RightShoulderComboBox->setCurrentIndex(settings.rightShoulderActionID);
    ui->LeftStickXComboBox->setCurrentIndex(settings.leftStickXActionID);
    ui->LeftStickYComboBox->setCurrentIndex(settings.leftStickYActionID);
    ui->LeftStickPressComboBox->setCurrentIndex(settings.leftStickPressActionID);
    ui->RightStickXComboBox->setCurrentIndex(settings.rightStickXActionID);
    ui->RightStickYComboBox->setCurrentIndex(settings.rightStickYActionID);
    ui->RightStickPressComboBox->setCurrentIndex(settings.rightStickPressActionID);
    ui->DPadXComboBox->setCurrentIndex(settings.dPadXActionID);
    ui->DPadYComboBox->setCurrentIndex(settings.dPadYActionID);
    ui->TriangleComboBox->setCurrentIndex(settings.triangleActionID);
    ui->CrossComboBox->setCurrentIndex(settings.crossActionID);
    ui->RectangleComboBox->setCurrentIndex(settings.rectangleActionID);
    ui->CircleComboBox->setCurrentIndex(settings.circleActionID);
    ui->StartComboBox->setCurrentIndex(settings.startActionID);
    ui->BackComboBox->setCurrentIndex(settings.backActionID);
}

void MainWindow::on_LoadClientSettingsButton_clicked() {
    loadClientSettings();
    QMessageBox::information(this,"Сообщение","Настройки успешно восстановлены");
}

void MainWindow::placeWidgets() {
    /// Изменяем размеры TabWidget
    ui->TabWidget->setGeometry(ui->MainWidget->geometry());

    /// Перемещаем кнопку "Полный экран"
    ui->FullScreenButton->move(ui->MainWidget->width() - ui->FullScreenButton->width(), 0);

    /// Перемещаем надпись "Статус подключения"
    int offset = 190; // Расстояние от правого края окна до надписи
    ui->StatusLabel->move(ui->MainWidget->width() - ui->StatusLabel->width() - offset, 0);

    /// Перемещаем виджет настроек робота
    offset = 30; // Расстояние между виджетами по горизонтали
    int x = (ui->tab_2->width() - (ui->RobotSettingsWidget->width() + ui->RobotCommandsWidget->width() + offset)) / 2;
    int y = (ui->tab_2->height() - ui->RobotSettingsWidget->height()) / 2;
    ui->RobotSettingsWidget->move(x, y);

    /// Перемещаем виджет команд робота
    x = ui->RobotSettingsWidget->x() + ui->RobotSettingsWidget->width() + offset;
    ui->RobotCommandsWidget->move(x, y);

    /// Перемещаем виджет назначения кнопок
    offset = 30; // Расстояние между виджетами по горизонтали
    x = (ui->tab_3->width() - (ui->KeyAssignmentsWidget->width() + ui->ClientSettingsWidget->width() + offset)) / 2;
    y = (ui->tab_3->height() - ui->KeyAssignmentsWidget->height()) / 2;
    ui->KeyAssignmentsWidget->move(x, y);

    /// Перемещаем виджет настроек клиента
    x = ui->KeyAssignmentsWidget->x() + ui->KeyAssignmentsWidget->width() + offset;
    ui->ClientSettingsWidget->move(x, y);

    /// Перемещаем заголовок виджета настроек робота
    x = ui->RobotSettingsWidget->x() + ui->RobotSettingsWidget->width() / 2 - ui->RobotSettingsLabel->width() / 2;
    y = ui->RobotSettingsWidget->y() - ui->RobotSettingsLabel->height() / 2;
    ui->RobotSettingsLabel->move(x, y);

    /// Перемещаем заголовок виджета команд робота
    x = ui->RobotCommandsWidget->x() + ui->RobotCommandsWidget->width() / 2 - ui->RobotCommandsLabel->width() / 2;
    y = ui->RobotCommandsWidget->y() - ui->ClientSettingsLabel->height() / 2;
    ui->RobotCommandsLabel->move(x, y);

    /// Перемещаем заголовок виджета назначения кнопок
    x = ui->KeyAssignmentsWidget->x() + ui->KeyAssignmentsWidget->width() / 2 - ui->KeyAssignmentsLabel->width() / 2;
    y = ui->KeyAssignmentsWidget->y() - ui->KeyAssignmentsLabel->height() / 2;
    ui->KeyAssignmentsLabel->move(x, y);

    /// Перемещаем заголовок виджета настроек клиента
    x = ui->ClientSettingsWidget->x() + ui->ClientSettingsWidget->width() / 2 - ui->ClientSettingsLabel->width() / 2;
    y = ui->ClientSettingsWidget->y() - ui->ClientSettingsLabel->height() / 2;
    ui->ClientSettingsLabel->move(x, y);
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
    } else {
        this->setWindowState(Qt::WindowFullScreen);
    }
}

void MainWindow::on_MotorsNumberSpinBox_valueChanged(int value) {
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
            if (ui->MotorsTable->item(i, j) == nullptr) {
                ui->MotorsTable->setItem(i, j, new QTableWidgetItem("0"));
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
        if (ui->HandTable->item(0, j) == nullptr) {
            ui->HandTable->setItem(0, j, new QTableWidgetItem("0"));
        }
    }
}