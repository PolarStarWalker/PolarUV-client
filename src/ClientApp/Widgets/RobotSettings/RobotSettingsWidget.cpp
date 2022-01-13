#include "RobotSettingsWidget.hpp"
// Строчка работает, но среда не видит файл в процессе написания кода
//#include "ui_RobotSettingsWidget.h"
// shushkov.d
#include "../../../../cmake-build-debug-msys-gcc/src/ClientApp/Widgets/Widgets_autogen/include/ui_RobotSettingsWidget.h"

#include "../ExceptionHandler/ExceptionHandler.hpp"
#include "./DataStructs/DataStructs.hpp"
#include "./Protocols/Protocols.hpp"


RobotSettingsWidget::RobotSettingsWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::RobotSettingsWidget) {
    ui->setupUi(this);

    /// Buttons
    this->connect(ui->ReceiveSettingsButton, SIGNAL(clicked(bool)), SLOT(ReceiveSettings()));
    this->connect(ui->SendSettingsButton, SIGNAL(clicked(bool)), SLOT(SendSettings()));

    /// Animations
    this->connect(ui->MotorsNumberSpinBox,SIGNAL(valueChanged(int)),SLOT(UpdateMotorsTable(int)));
    this->connect(ui->HandFreedomSpinBox,SIGNAL(valueChanged(int)),SLOT(UpdateHandTable(int)));
    this->connect(ui->MaxSpeedSlider,SIGNAL(valueChanged(int)),SLOT(UpdateMaxSpeedEdit(int)));
    this->connect(ui->MaxSpeedEdit,SIGNAL(textChanged(QString)),SLOT(UpdateMaxSpeedSlider(QString)));
}

RobotSettingsWidget::~RobotSettingsWidget() {
    delete ui;
}

void RobotSettingsWidget::SendSettings() const {
    auto method = Function([&]() {
        using namespace data_structs;

        data_structs::BaseRobotSettingsDto baseRobotSettingsStruct{};
        baseRobotSettingsStruct.ThrusterNumber = ui->MotorsTable->rowCount();
        baseRobotSettingsStruct.HandFreedom = ui->HandTable->columnCount();

        data_structs::OldRobotSettingsDto robotSettingsStruct(baseRobotSettingsStruct);

        /// Reading motor coefficients
        float *moveCoefficientArray = robotSettingsStruct.ThrusterCoefficientArray();
        for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
            for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
                bool isConverted;
                double value = ui->MotorsTable->item(i, j)->text().toFloat(&isConverted);
                if (isConverted) {
                    moveCoefficientArray[i * 6 + j] = value;
                } else {
                    throw Exception::InvalidOperationException("Матрица коэффициентов двигателей\n"
                                                               "содержит некорректный символ");
                }
            }
        }

        /// Reading hand coefficients
        float *handCoefficientArray = robotSettingsStruct.HandCoefficientArray();
        for (int j = 0; j < ui->HandTable->columnCount(); j++) {
            bool isConverted;
            double value = ui->HandTable->item(0, j)->text().toFloat(&isConverted);
            if (isConverted) {
                handCoefficientArray[j] = value;
            } else {
                throw Exception::InvalidOperationException("Матрица коэффициентов манипулятора\n"
                                                           "содержит некорректный символ");
            }
        }

        /// Reading max motor speed
        robotSettingsStruct.MaxMotorsSpeed() = (int16_t) ui->MaxSpeedEdit->text().toInt();

        /// Reading motors protocol
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

        #if DEBUG
                std::cout << robotSettingsStruct;
        #endif

        /// Sending settings to robot
//        RobotSettingsProtocol().Send(ui->RobotIPEdit->text(), SETTINGS_PORT, std::move(robotSettingsStruct));
    });
    ExceptionHandler(method, "Успех", "Настройки успешно отправлены");
}

void RobotSettingsWidget::ReceiveSettings() {
    auto method = Function([&]() {
        //data_structs::OldRobotSettingsDto robotSettingsStruct = RobotSettingsProtocol().Recv(ui->RobotIPEdit->text(), SETTINGS_PORT);
        QString ip{};
        uint16_t port{};
        data_structs::OldRobotSettingsDto robotSettingsStruct = RobotSettingsProtocol().Recv(ip, port);

        /// Writing motors number
        const float *moveCoefficientArray = robotSettingsStruct.ThrusterCoefficientArray();
        int motorsNumber = robotSettingsStruct.ThrusterNumber();
        ui->MotorsNumberSpinBox->setValue(motorsNumber);

        /// Writing motor coefficients
        for (int i = 0; i < motorsNumber; i++) {
            for (int j = 0; j < 6; j++) {
                QString itemText = QString::number(moveCoefficientArray[i * 6 + j]);
                ui->MotorsTable->setItem(i, j, new QTableWidgetItem(itemText));
            }
        }

        /// Writing the number of degrees of freedom of the hand
        const float *handCoefficientArray = robotSettingsStruct.HandCoefficientArray();
        int handFreedom = robotSettingsStruct.HandFreedom();
        ui->HandFreedomSpinBox->setValue(handFreedom);

        /// Writing hand coefficients
        for (int j = 0; j < handFreedom; j++) {
            QString itemText = QString::number(handCoefficientArray[j]);
            ui->HandTable->setItem(0, j, new QTableWidgetItem(itemText));
        }

        /// Writing max motor speed
        ui->MaxSpeedEdit->setText(QString::number(robotSettingsStruct.MaxMotorsSpeed()));

        /// Writing motors protocol
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
    });

    ExceptionHandler(method, "Сообщение", "Настройки успешно сохранены");
}

void RobotSettingsWidget::UpdateMotorsTable(int value) {
    /// Changing the height of the table
    ui->MotorsTable->setFixedHeight((value * 26) + ((int) (value * 0.5))); // 26 - высота одной строки
    /// Moving the lower lines
    int x = ui->MotorsBottomLeftLine->x();
    int y = ui->MotorsTable->y() + ui->MotorsTable->height();
    ui->MotorsBottomLeftLine->move(x, y);
    x = ui->MotorsBottomRightLine->x();
    ui->MotorsBottomRightLine->move(x, y);

    /// Changing the height of the side lines
    int height = ui->MotorsBottomLeftLine->y() - ui->MotorsTopLeftLine->y();
    ui->MotorsLeftLine->setFixedHeight(height);
    ui->MotorsRightLine->setFixedHeight(height);

    /// Setting the number of rows in the table
    ui->MotorsTable->setRowCount(value);

    /// Filling the empty cells with zeros
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            if (ui->MotorsTable->item(i, j) == nullptr) {
                ui->MotorsTable->setItem(i, j, new QTableWidgetItem("0.0"));
            }
        }
    }
}

void RobotSettingsWidget::UpdateHandTable(int value) {
    /// Changing the width of the table
    ui->HandTable->setFixedWidth((value * 49) + ((int) (value * 0.5))); // 49 - width of one column

    /// Moving the table under the HandCoefficients label
    int x = (ui->HandCoefficientsLabel->x() + (ui->HandCoefficientsLabel->width() / 2)) -
            (ui->HandTable->width() / 2);
    int y = ui->HandTable->y();
    ui->HandTable->move(x, y);

    /// Moving the side lines
    x = ui->HandTable->x() - 20;
    y = ui->HandLeftLine->y();
    ui->HandLeftLine->move(x, y);
    x = ui->HandTable->x() + ui->HandTable->width();
    ui->HandRightLine->move(x, y);

    /// Moving the upper and lower lines
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

    /// Setting the number of columns in the table
    ui->HandTable->setColumnCount(value);

    /// Filling the empty cells with zeros
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        if (ui->HandTable->item(0, j) == nullptr) {
            ui->HandTable->setItem(0, j, new QTableWidgetItem("0.0"));
        }
    }
}

void RobotSettingsWidget::UpdateMaxSpeedEdit(int value) {
    ui->MaxSpeedEdit->setText(QString::number(value));
}

void RobotSettingsWidget::UpdateMaxSpeedSlider(const QString& string) {
    ui->MaxSpeedSlider->setValue(string.toInt());
}