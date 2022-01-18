#include "RobotSettingsWidget.hpp"
#include "ui_RobotSettingsWidget.h"

RobotSettingsWidget::RobotSettingsWidget(QWidget *parent) :
        QWidget(parent),
        _transmitter(lib::network::TcpSession::GetInstance()),
        ui(new Ui::RobotSettingsWidget) {

    ui->setupUi(this);

    /// Buttons
    this->connect(ui->ReceiveSettingsButton, SIGNAL(clicked(bool)), SLOT(ReceiveSettings()));
    this->connect(ui->SendSettingsButton, SIGNAL(clicked(bool)), SLOT(SendSettings()));

    /// Animations
    this->connect(ui->MotorsNumberSpinBox, SIGNAL(valueChanged(int)), SLOT(UpdateMotorsTable(int)));
    this->connect(ui->HandFreedomSpinBox, SIGNAL(valueChanged(int)), SLOT(UpdateHandTable(int)));
    this->connect(ui->MaxSpeedSlider, SIGNAL(valueChanged(int)), SLOT(UpdateMaxSpeedEdit(int)));
    this->connect(ui->MaxSpeedEdit, SIGNAL(textChanged(QString)), SLOT(UpdateMaxSpeedSlider(QString)));
}

RobotSettingsWidget::~RobotSettingsWidget() {
    delete ui;
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

void RobotSettingsWidget::UpdateMaxSpeedSlider(const QString &string) {
    ui->MaxSpeedSlider->setValue(string.toInt());
}

void RobotSettingsWidget::UpdateGeometry(QSize newParentSize) {
    int x = (newParentSize.width() - this->width()) / 2;
    int y = (newParentSize.height() - this->height()) / 2;
    this->move(x,y);
}

