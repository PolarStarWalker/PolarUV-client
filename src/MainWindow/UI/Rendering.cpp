#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::setupRendering() {
    /// Запуск таймера отрисовки окна
    this->startTimer(1000 / 60, Qt::PreciseTimer);

    /// Устанавливаем иконку приложения
    setWindowIcon(QIcon("Icons/WindowIcon.png"));

    /// Устанавливаем иконки вкладок
    ui->TabWidget->setTabIcon(0, QIcon("Icons/CameraIcon"));
    ui->TabWidget->setTabIcon(1, QIcon("Icons/RobotIcon"));
    ui->TabWidget->setTabIcon(2, QIcon("Icons/ClientIcon"));

    /// Устанавливаем иконки кнопок
    ui->FullScreenButton->setIcon(QIcon("Icons/FullScreenIcon.png"));
    ui->ShowTabBarButton->setIcon(QIcon("Icons/ShowTabBarIcon.png"));
    ui->HideTabBarButton->setIcon(QIcon("Icons/HideTabBarIcon.png"));
    ui->VideoStreamButton->setIcon(QIcon("Icons/PlayIcon.png"));
    ui->ScreenshotButton->setIcon(QIcon("Icons/ScreenshotIcon.png"));
    ui->VideoCaptureButton->setIcon(QIcon("Icons/WhiteVideoIcon.png"));

    /// Устанавливаем прозрачный фон для некоторых кнопок
    ui->ShowTabBarButton->setStyleSheet("background-color: transparent");
    ui->VideoStreamButton->setStyleSheet("background-color: transparent");
    ui->ScreenshotButton->setStyleSheet("background-color: transparent");
    ui->VideoCaptureButton->setStyleSheet("background-color: transparent");

    /// Скрываем кнопку показа вкладок
    ui->ShowTabBarButton->hide();
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
    offset = 10; // Расстояние между виджетами по вертикали
    int x = 0;
    int y = (ui->MainWidget->height() - (ui->FullScreenButton->height() + ui->HideTabBarButton->height() + offset)) / 2;
    ui->FullScreenButton->move(x, y);

    /// Перемещаем кнопку скрытия вкладок
    y = ui->FullScreenButton->y() + ui->HideTabBarButton->height() + offset;
    ui->HideTabBarButton->move(x, y);

    /// Перемещаем кнопку показа вкладок
    ui->ShowTabBarButton->move(0, 0);

    /// Перемещаем кнопку управления трансляцией
    offset = 10; // Расстояние от нижнего края окна до кнопки
    x = (ui->tab_1->width() / 2) - (ui->VideoStreamButton->width() / 2);
    y = ui->tab_1->height() - ui->VideoStreamButton->height() - offset;
    ui->VideoStreamButton->move(x, y);

    /// Перемещаем кнопку записи видео
    offset = 50; // Расстояние от кнопки управления трансляцией
    x = ui->VideoStreamButton->x() + ui->VideoStreamButton->width() + offset;
    y = ui->VideoStreamButton->y();
    ui->VideoCaptureButton->move(x, y);

    /// Перемещаем кнопку скриншота
    offset = 50; // Расстояние от кнопки управления трансляцией
    x = ui->VideoStreamButton->x() - ui->ScreenshotButton->width() - offset;
    y = ui->VideoStreamButton->y();
    ui->ScreenshotButton->move(x, y);

    /// Перемещаем виджет настроек робота
    x = (ui->tab_2->width() / 2) - (ui->RobotSettingsWidget->width() / 2);
    y = (ui->tab_2->height() / 2) - (ui->RobotSettingsWidget->height() / 2);
    ui->RobotSettingsWidget->move(x, y);

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

    /// Рисуем кадр с трансляции или картинку-заглушку
    if (this->_videoStream->IsOnline()) {
        cv::Mat mat = this->_videoStream->GetMatrix();
        ui->CameraLabel->setPixmap(QPixmap(cvMatToPixmap(mat)));
    } else {
        ui->CameraLabel->setPixmap(QPixmap("Icons/CameraPlaceholder.png"));
    }

    /// Выбираем цвет иконки кнопки запуска
    if (this->_commandsProtocol->IsOnline()) {
        ui->CommandsProtocolButton->setIcon(QIcon("Icons/GreenStartIcon.png"));
    } else {
        ui->CommandsProtocolButton->setIcon(QIcon("Icons/RedStartIcon.png"));
    }

    /// Выбираем иконку кнопки трансляции
    if (_videoStream->IsOnline()) {
        ui->VideoStreamButton->setIcon(QIcon("Icons/PauseIcon.png"));
    } else {
        ui->VideoStreamButton->setIcon(QIcon("Icons/PlayIcon.png"));
    }
}

void MainWindow::timerEvent(QTimerEvent *event) {
    this->repaint();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    this->placeWidgets();
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