#include "RobotSettingsWidget.hpp"
#include "ui_RobotSettingsWidget.h"

RobotSettingsWidget::RobotSettingsWidget(QWidget *parent, WidgetResources& resources) :
        QWidget(parent),
        resources_(resources),
        ui(new Ui::RobotSettingsWidget) {

    ui->setupUi(this);

    /// Connecting buttons
    this->connect(ui->ReceiveSettingsButton, SIGNAL(clicked(bool)), SLOT(ReceiveSettings()));
    this->connect(ui->SendSettingsButton, SIGNAL(clicked(bool)), SLOT(SendSettings()));

    /// Connecting other
    this->connect(ui->MotorsNumberSpinBox, SIGNAL(valueChanged(int)), SLOT(UpdateMotorsTable(int)));
    this->connect(ui->HandFreedomSpinBox, SIGNAL(valueChanged(int)), SLOT(UpdateHandTable(int)));
    this->connect(ui->MaxSpeedSlider, SIGNAL(valueChanged(int)), SLOT(UpdateMaxSpeedEdit(int)));
    this->connect(ui->MaxSpeedEdit, SIGNAL(textChanged(QString)), SLOT(UpdateMaxSpeedSlider(QString)));

    /// Changind default header labels for MotorsTable
    QStringList labelsList = {"Fx", "Fy", "Fz," "Mx", "My", "Mz"};
    ui->MotorsTable->setHorizontalHeaderLabels(labelsList);
}

RobotSettingsWidget::~RobotSettingsWidget() {
    delete ui;
}

void RobotSettingsWidget::UpdateMotorsTable(int value) {
    /// Changing the height of the table
    ui->MotorsTable->setMinimumHeight((value + 1) * 25 + 2);
    ui->MotorsTable->setMaximumHeight((value + 1) * 25 + 2);

    /// Setting the number of rows in the table
    ui->MotorsTable->setRowCount(value);

    /// Filling the empty cells with zeros
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            if (ui->MotorsTable->item(i, j) == nullptr) {
                ui->MotorsTable->setItem(i, j, new QTableWidgetItem("0.0"));
                ui->MotorsTable->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void RobotSettingsWidget::UpdateHandTable(int value) {
    /// Changing the width of the table
    ui->HandTable->setMinimumWidth(value * 50 + 1);
    ui->HandTable->setMaximumWidth(value * 50 + 1);

    /// Setting the number of columns in the table
    ui->HandTable->setColumnCount(value);

    /// Filling the empty cells with zeros
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        if (ui->HandTable->item(0, j) == nullptr) {
            ui->HandTable->setItem(0, j, new QTableWidgetItem("0.0"));
            ui->HandTable->item(0,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void RobotSettingsWidget::UpdateMaxSpeedEdit(int value) {
    ui->MaxSpeedEdit->setText(QString::number(value));
}

void RobotSettingsWidget::UpdateMaxSpeedSlider(const QString &string) {
    ui->MaxSpeedSlider->setValue(string.toInt());
}