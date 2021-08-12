#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->_widgetsPlaced = false;

    //Создание CommandsProtocol для Gamepad
    this->_commandsProtocol = new CommandsProtocol(0);

    this->_settingsProtocol = new RobotSettingsProtocol();

    this->_videoStream = new VideoProtocol();

    //Запуск таймера отрисовки окна
    this->startTimer(1000 / 60, Qt::PreciseTimer);

    //Загрузка настроек клиента из файла
    loadClientSettings();

    /// Устанавливаем иконку приложения
    setWindowIcon(QIcon("Icons/WindowIcon.png"));

    /// Устанавливаем иконки вкладок
    ui->TabWidget->setTabIcon(0, QIcon("Icons/CameraIcon"));
    ui->TabWidget->setTabIcon(1, QIcon("Icons/RobotIcon"));
    ui->TabWidget->setTabIcon(2, QIcon("Icons/ClientIcon"));

    /// Устанавливаем иконку кнопки "Полный экран"
    ui->FullScreenButton->setIcon(QIcon("Icons/FullScreenIcon.png"));

    /// Устанавливаем иконку кнопки запуска трансляции
    ui->VideoStreamButton->setIcon(QIcon("Icons/PlayIcon.png"));
}

MainWindow::~MainWindow() {
    delete ui;
    delete this->_commandsProtocol;
    delete this->_settingsProtocol;
    delete this->_videoStream;
}

void MainWindow::on_GamepadButton_clicked() {

}

void MainWindow::on_VideoStreamButton_clicked() {
    if (!_videoStream->IsOnline()) {
        _videoStream->StartAsync(pipeline);
        QIcon videoStreamIcon("Icons/PauseIcon.png");
        ui->VideoStreamButton->setIcon(videoStreamIcon);
    } else {
        _videoStream->Stop();
        QIcon videoStreamIcon("Icons/PlayIcon.png");
        ui->VideoStreamButton->setIcon(videoStreamIcon);
    }
}

void MainWindow::on_CommandsProtocolButton_clicked() {
    if (!_commandsProtocol->IsOnline()) {
        _commandsProtocol->StartAsync(ui->IPEdit->text(), COMMANDS_PORT);
    } else {
        _commandsProtocol->Stop();
    }
}

void MainWindow::on_ReceiveSettingsButton_clicked() {
    /// Временные "входные" данные
    /// ToDo: заменить на прием структуры по протоколу
    std::vector<double> motorsVector = {1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1};
    std::vector<double> handVector = {1, 2, 3, 4, 5};
    int8_t motorsProtocol = 4;
    RobotSettingsStruct robotSettingsStruct(motorsVector, handVector);
    robotSettingsStruct.MotorsProtocol() = 4;
    robotSettingsStruct.MaxMotorsSpeed() = 3000;

    /// Выводим количество двигателей
    const double *moveCoefficientArray = robotSettingsStruct.GetThrusterCoefficientArray();
    int motorsNumber = robotSettingsStruct.ThrusterNumber();
    ui->MotorsNumberSpinBox->setValue(motorsNumber);

    /// Выводим коэффициенты двигателей
    for (int i = 0; i < motorsNumber; i++) {
        for (int j = 0; j < 6; j++) {
            QString itemText = QString::number(moveCoefficientArray[i * 6 + j]);
            ui->MotorsTable->setItem(i, j, new QTableWidgetItem(itemText));
        }
    }

    /// Выводим число степеней свободы манипулятора
    const double *handCoefficientArray = robotSettingsStruct.GetHandCoefficientArray();
    int handFreedom = robotSettingsStruct.HandFreedom();;
    ui->HandFreedomSpinBox->setValue(handFreedom);

    /// Выводим коэффициенты манипулятора
    for (int j = 0; j < handFreedom; j++) {
        QString itemText = QString::number(handCoefficientArray[j]);
        ui->HandTable->setItem(0, j, new QTableWidgetItem(itemText));
    }

    /// Выводим максимальную скорость двигателей
    ui->MaxSpeedEdit->setText(QString::number(robotSettingsStruct.MaxMotorsSpeed()));

    /// Выводим протокол двигателей
    switch (robotSettingsStruct.MotorsProtocol()) {
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

    /// Считываем коэффициенты двигателей
    std::vector<double> motorsVector(ui->MotorsTable->rowCount() * 6);
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            motorsVector[i * 6 + j] = ui->MotorsTable->item(i, j)->text().toDouble();
        }
    }

    /// Считываем коэффициенты манипулятора
    std::vector<double> handVector(ui->HandTable->columnCount());
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        handVector[j] = ui->HandTable->item(0, j)->text().toDouble();
    }

    RobotSettingsStruct robotSettingsStruct(motorsVector, handVector);

    /// Считываем максимальную скорость двигателей
    robotSettingsStruct.MaxMotorsSpeed() = ui->MaxSpeedEdit->text().toInt();

    /// Считываем протокол двигателей
    switch (ui->MotorsProtocolComboBox->currentIndex()) {
        case 0:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot150;
            break;
        case 1:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot300;
            break;
        case 2:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot600;
            break;
        case 3:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot1200;
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

    std::memcpy(settings.serverIP, ui->IPEdit->text().begin(), sizeof(settings.serverIP));

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

    settings.leftShoulderInverted = ui->LeftShoulderCheckBox->isChecked();
    settings.rightShoulderInverted = ui->RightShoulderCheckBox->isChecked();
    settings.leftStickXInverted = ui->LeftStickXCheckBox->isChecked();
    settings.leftStickYInverted = ui->LeftStickYCheckBox->isChecked();
    settings.rightStickXInverted = ui->RightStickXCheckBox->isChecked();
    settings.rightStickYInverted = ui->RightStickYCheckBox->isChecked();
    settings.dPadXInverted = ui->DPadXCheckBox->isChecked();
    settings.dPadYInverted = ui->DPadYCheckBox->isChecked();

    settings.Save();

    QMessageBox::information(this, "Сообщение", "Настройки успешно сохранены");
}

void MainWindow::loadClientSettings() {
    ClientSettingsStruct settings;
    settings.Load();

    ui->IPEdit->setText(QString(settings.serverIP));

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

    ui->LeftShoulderCheckBox->setChecked(settings.leftShoulderInverted);
    ui->RightShoulderCheckBox->setChecked(settings.rightShoulderInverted);
    ui->LeftStickXCheckBox->setChecked(settings.leftStickXInverted);
    ui->LeftStickYCheckBox->setChecked(settings.leftStickYInverted);
    ui->RightStickXCheckBox->setChecked(settings.rightStickXInverted);
    ui->RightStickYCheckBox->setChecked(settings.rightStickYInverted);
    ui->DPadXCheckBox->setChecked(settings.dPadXInverted);
    ui->DPadYCheckBox->setChecked(settings.dPadYInverted);
}

void MainWindow::on_LoadClientSettingsButton_clicked() {
    loadClientSettings();
    QMessageBox::information(this, "Сообщение", "Настройки успешно восстановлены");
}

void MainWindow::placeWidgets() {
    /// Изменяем размеры TabWidget
    ui->TabWidget->setGeometry(ui->MainWidget->geometry());

    /// Изменяем размеры окна камеры
    ui->CameraLabel->setGeometry(ui->tab_1->geometry());

    /// Перемещаем кнопку "Начать работу"
    int offset = 0; // Расстояние от нижнего края окна
    ui->CommandsProtocolButton->move(0, ui->MainWidget->height() - ui->CommandsProtocolButton->height() - offset);

    /// Перемещаем кнопку "Полный экран"
    offset = 10; // Расстояние от кнопки "Начать работу"
    ui->FullScreenButton->move(0, ui->CommandsProtocolButton->y() - ui->FullScreenButton->height() - offset);

    /// Перемещаем кнопку управления трансляцией
    offset = 10; // Расстояние от нижнего края окна до кнопки
    int x = (ui->tab_1->width() / 2) - (ui->VideoStreamButton->width() / 2);
    int y = ui->tab_1->height() - ui->VideoStreamButton->height() - offset;
    ui->VideoStreamButton->move(x, y);

    /// Перемещаем виджет настроек робота
    offset = 30; // Расстояние между виджетами по горизонтали
    x = (ui->tab_2->width() - (ui->RobotSettingsWidget->width() + ui->RobotCommandsWidget->width() + offset)) / 2;
    y = (ui->tab_2->height() - ui->RobotSettingsWidget->height()) / 2;
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

QImage MainWindow::cvMatToQImage(const cv::Mat &mat) {
    switch (mat.type()) {
        case CV_8UC3: {
            QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
            return image;
        }
        case CV_8UC4: {
            QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_ARGB32);
            return image;
        }
    }
}

QPixmap MainWindow::cvMatToPixmap(const cv::Mat &mat) {
    QImage image = cvMatToQImage(mat);
    image = std::move(image).rgbSwapped();
    return QPixmap::fromImage(image);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    /// Если это первая отрисовка с момента запуска программы, то размещаем виджеты
    if (!this->_widgetsPlaced) this->placeWidgets();

    /// Выбираем цвет иконки кнопки запуска
    if (this->_commandsProtocol->IsOnline())
        ui->CommandsProtocolButton->setIcon(QIcon("Icons/GreenStartIcon.png"));
    else
        ui->CommandsProtocolButton->setIcon(QIcon("Icons/RedStartIcon.png"));

    if (this->_videoStream->IsOnline()) {
        cv::Mat mat = this->_videoStream->GetMatrix();
        ui->CameraLabel->setPixmap(QPixmap(cvMatToPixmap(mat)));
    } else {
        ui->CameraLabel->setPixmap(QPixmap("Icons/CameraPlaceholder.png"));
    }
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

void MainWindow::mouseMoveEvent(QMouseEvent *event) {

}
