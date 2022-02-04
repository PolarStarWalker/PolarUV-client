#include "ClientSettingsWidget.hpp"
#include "ui_ClientSettingsWidget.h"


ClientSettingsWidget::ClientSettingsWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ClientSettingsWidget) {

    ui->setupUi(this);

    settings_ = std::make_unique<QSettings>("NARFU", "PolarROVClient");
    LoadSettings();

    connect(ui->LoadClientSettingsButton, SIGNAL(clicked(bool)), SLOT(LoadSettings()));
    connect(ui->SaveClientSettingsButton, SIGNAL(clicked(bool)), SLOT(SaveSettings()));
}

ClientSettingsWidget::~ClientSettingsWidget() {
    delete ui;
}

ControlsSettings ClientSettingsWidget::GetControlsSettings() {
    std::array<AnalogActions, 8> AnalogArray{
            ui->LeftStickXCheckBox->isChecked() ?
            (AnalogActions) -ui->LeftStickXComboBox->currentIndex() :
            (AnalogActions) ui->LeftStickXComboBox->currentIndex(),

            ui->LeftStickYCheckBox->isChecked() ?
            (AnalogActions) -ui->LeftStickYComboBox->currentIndex() :
            (AnalogActions) ui->LeftStickYComboBox->currentIndex(),

            ui->RightStickXCheckBox->isChecked() ?
            (AnalogActions) -ui->RightStickXComboBox->currentIndex() :
            (AnalogActions) ui->RightStickXComboBox->currentIndex(),

            ui->RightStickYCheckBox->isChecked() ?
            (AnalogActions) -ui->RightStickYComboBox->currentIndex() :
            (AnalogActions) ui->RightStickYComboBox->currentIndex(),

            ui->LeftShoulderCheckBox->isChecked() ?
            (AnalogActions) -ui->LeftShoulderComboBox->currentIndex() :
            (AnalogActions) ui->LeftShoulderComboBox->currentIndex(),

            ui->RightShoulderCheckBox->isChecked() ?
            (AnalogActions) -ui->RightShoulderComboBox->currentIndex() :
            (AnalogActions) ui->RightShoulderComboBox->currentIndex(),

            ui->DPadXCheckBox->isChecked() ?
            (AnalogActions) -ui->DPadXComboBox->currentIndex() :
            (AnalogActions) ui->DPadXComboBox->currentIndex(),

            ui->DPadYCheckBox->isChecked() ?
            (AnalogActions) -ui->DPadYComboBox->currentIndex() :
            (AnalogActions) ui->DPadYComboBox->currentIndex()
    };
    std::array<DiscreteActions, 8> DiscreteArray{
            (DiscreteActions) ui->LeftStickPressComboBox->currentIndex(),
            (DiscreteActions) ui->RightStickPressComboBox->currentIndex(),
            (DiscreteActions) ui->RectangleComboBox->currentIndex(),
            (DiscreteActions) ui->TriangleComboBox->currentIndex(),
            (DiscreteActions) ui->CircleComboBox->currentIndex(),
            (DiscreteActions) ui->CrossComboBox->currentIndex(),
            (DiscreteActions) ui->StartComboBox->currentIndex(),
            (DiscreteActions) ui->BackComboBox->currentIndex()
    };

    return {AnalogArray, DiscreteArray};;

    // Использовать примерно так:
    // controlsSettings.Analog[AnalogControls::DPadX];
}

void ClientSettingsWidget::LoadSettings() {
    if (!settings_->value("DPadXAction").isNull()) {
        // Analog actions
        ui->DPadXComboBox->setCurrentIndex(settings_->value("DPadXAction").toInt());
        ui->DPadYComboBox->setCurrentIndex(settings_->value("DPadYAction").toInt());
        ui->LeftStickXComboBox->setCurrentIndex(settings_->value("LeftStickXAction").toInt());
        ui->LeftStickYComboBox->setCurrentIndex(settings_->value("LeftStickYAction").toInt());
        ui->RightStickXComboBox->setCurrentIndex(settings_->value("RightStickXAction").toInt());
        ui->RightStickYComboBox->setCurrentIndex(settings_->value("RightStickYAction").toInt());
        ui->LeftShoulderComboBox->setCurrentIndex(settings_->value("LeftShoulderAction").toInt());
        ui->RightShoulderComboBox->setCurrentIndex(settings_->value("RightShoulderAction").toInt());
        // Discrete actions
        ui->LeftStickPressComboBox->setCurrentIndex(settings_->value("LeftStickPressAction").toInt());
        ui->RightStickPressComboBox->setCurrentIndex(settings_->value("RightStickPressAction").toInt());
        ui->RectangleComboBox->setCurrentIndex(settings_->value("SquareAction").toInt());
        ui->TriangleComboBox->setCurrentIndex(settings_->value("TriangleAction").toInt());
        ui->CircleComboBox->setCurrentIndex(settings_->value("CircleAction").toInt());
        ui->CrossComboBox->setCurrentIndex(settings_->value("CrossAction").toInt());
        ui->StartComboBox->setCurrentIndex(settings_->value("StartAction").toInt());
        ui->BackComboBox->setCurrentIndex(settings_->value("BackAction").toInt());
        // Booleans
        ui->DPadXCheckBox->setChecked(settings_->value("DPadXInverted").toBool());
        ui->DPadYCheckBox->setChecked(settings_->value("DPadYInverted").toBool());
        ui->LeftStickXCheckBox->setChecked(settings_->value("LeftStickXInverted").toBool());
        ui->LeftStickYCheckBox->setChecked(settings_->value("LeftStickYInverted").toBool());
        ui->RightStickXCheckBox->setChecked(settings_->value("RightStickXInverted").toBool());
        ui->RightStickYCheckBox->setChecked(settings_->value("RightStickYInverted").toBool());
        ui->LeftShoulderCheckBox->setChecked(settings_->value("LeftShoulderInverted").toBool());
        ui->RightShoulderCheckBox->setChecked(settings_->value("RightShoulderInverted").toBool());
    }
}

void ClientSettingsWidget::SaveSettings() {
    // Analog actions
    settings_->setValue("DPadXAction", ui->DPadXComboBox->currentIndex());
    settings_->setValue("DPadYAction", ui->DPadYComboBox->currentIndex());
    settings_->setValue("LeftStickXAction", ui->LeftStickXComboBox->currentIndex());
    settings_->setValue("LeftStickYAction", ui->LeftStickYComboBox->currentIndex());
    settings_->setValue("RightStickXAction", ui->RightStickXComboBox->currentIndex());
    settings_->setValue("RightStickYAction", ui->RightStickYComboBox->currentIndex());
    settings_->setValue("LeftShoulderAction", ui->LeftShoulderComboBox->currentIndex());
    settings_->setValue("RightShoulderAction", ui->RightShoulderComboBox->currentIndex());
    // Discrete actions
    settings_->setValue("LeftStickPressAction", ui->LeftStickPressComboBox->currentIndex());
    settings_->setValue("RightStickPressAction", ui->RightStickPressComboBox->currentIndex());
    settings_->setValue("SquareAction", ui->RectangleComboBox->currentIndex());
    settings_->setValue("TriangleAction", ui->TriangleComboBox->currentText());
    settings_->setValue("CircleAction", ui->CircleComboBox->currentIndex());
    settings_->setValue("CrossAction", ui->CrossComboBox->currentIndex());
    settings_->setValue("StartAction", ui->StartComboBox->currentIndex());
    settings_->setValue("BackAction", ui->BackComboBox->currentIndex());
    // Booleans
    settings_->setValue("DPadXInverted", ui->DPadXCheckBox->isChecked());
    settings_->setValue("DPadYInverted", ui->DPadYCheckBox->isChecked());
    settings_->setValue("LeftStickXInverted", ui->LeftStickXCheckBox->isChecked());
    settings_->setValue("LeftStickYInverted", ui->LeftStickYCheckBox->isChecked());
    settings_->setValue("RightStickXInverted", ui->RightStickXCheckBox->isChecked());
    settings_->setValue("RightStickYInverted", ui->RightStickYCheckBox->isChecked());
    settings_->setValue("LeftShoulderInverted", ui->LeftShoulderCheckBox->isChecked());
    settings_->setValue("RightShoulderInverted", ui->RightShoulderCheckBox->isChecked());
}

void ClientSettingsWidget::StartWidget() {

}

void ClientSettingsWidget::StopWidget() {

}

