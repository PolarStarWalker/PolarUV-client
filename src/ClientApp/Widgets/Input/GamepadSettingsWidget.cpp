#include "GamepadSettingsWidget.hpp"
#include "ui_GamepadSettingsWidget.h"

#include <iostream>

CommandsSettingsWidget::CommandsSettingsWidget(QWidget *parent, WidgetResources &resources) :
        QWidget(parent),
        ui(new Ui::GamepadSettingsWidget),
        resources_(resources),
        gamepad_(0) {

    ui->setupUi(this);

    settings_ = std::make_unique<QSettings>("NARFU", "PolarROVClient");
    LoadSettings();

    connect(ui->LoadClientSettingsButton, SIGNAL(clicked(bool)), SLOT(LoadSettings()));
    connect(ui->SaveClientSettingsButton, SIGNAL(clicked(bool)), SLOT(SaveSettings()));
    connect(&timer_, SIGNAL(timeout()), this, SLOT(SendCommand()));
}

CommandsSettingsWidget::~CommandsSettingsWidget() {
    delete ui;
}

GamepadSettingsStruct CommandsSettingsWidget::GetGamepadSettings() {

    using DiscreteActionsEnum = GamepadSettingsStruct::DiscreteActionEnum;
    using AnalogActionsEnum = GamepadSettingsStruct::AnalogActionEnum;

    using DiscreteAxisEnum = GamepadSettingsStruct::DiscreteAxisEnum;
    using AnalogAxisEnum = GamepadSettingsStruct::AnalogAxisEnum;

    using DiscreteSettings = GamepadSettingsStruct::DiscreteSettings_t;
    using AnalogSettings = GamepadSettingsStruct::AnalogSettings_t;

    //ToDo: shuskov.d сделать наполнение структуры раскладки
    DiscreteSettings DiscreteActions;
//    DiscreteActions[DiscreteAxisEnum::LeftStick] = (DiscreteActionsEnum) ui->LeftStickPressComboBox->currentIndex();
//    DiscreteActions[DiscreteAxisEnum::RightStick] = (DiscreteActionsEnum) ui->RightStickPressComboBox->currentIndex();
//    DiscreteActions[DiscreteAxisEnum::Square] = (DiscreteActionsEnum) ui->RectangleComboBox->currentIndex();
//    DiscreteActions[DiscreteAxisEnum::Triangle] = (DiscreteActionsEnum) ui->TriangleComboBox->currentIndex();
//    DiscreteActions[DiscreteAxisEnum::Circle] = (DiscreteActionsEnum) ui->CircleComboBox->currentIndex();
//    DiscreteActions[DiscreteAxisEnum::Cross] = (DiscreteActionsEnum) ui->CrossComboBox->currentIndex();
//    DiscreteActions[DiscreteAxisEnum::Start] = (DiscreteActionsEnum) ui->StartComboBox->currentIndex();
//    DiscreteActions[DiscreteAxisEnum::Back] = (DiscreteActionsEnum) ui->BackComboBox->currentIndex();

    AnalogSettings AnalogActions;
    //у аналогового массива значение это структура AnalogAxisEnum + (bool) IsInverted
//    AnalogActions[AnalogAxisEnum::LeftStickX] =
//            convert(ui->LeftStickXCheckBox->isChecked(), ui->LeftStickXComboBox->currentIndex());
//
//    AnalogActions[AnalogAxisEnum::LeftStickY] =
//            convert(ui->LeftStickYCheckBox->isChecked(), ui->LeftStickYComboBox->currentIndex());
//
//    AnalogActions[AnalogAxisEnum::RightStickX] =
//            convert(ui->RightStickXCheckBox->isChecked(), ui->RightStickXComboBox->currentIndex());
//
//    AnalogActions[AnalogAxisEnum::RightStickY] =
//            convert(ui->RightStickYCheckBox->isChecked(), ui->RightStickYComboBox->currentIndex());
//
//    AnalogActions[AnalogAxisEnum::LeftShoulder] =
//            convert(ui->LeftShoulderCheckBox->isChecked(), ui->LeftShoulderComboBox->currentIndex());
//
//    AnalogActions[AnalogAxisEnum::RightShoulder] =
//            convert(ui->RightShoulderCheckBox->isChecked(), ui->RightShoulderComboBox->currentIndex());
//
//    AnalogActions[AnalogAxisEnum::DPadX] =
//            convert(ui->DPadXCheckBox->isChecked(), ui->DPadXComboBox->currentIndex());
//
//    AnalogActions[AnalogAxisEnum::DPadY] =
//            convert(ui->DPadYCheckBox->isChecked(), ui->DPadYComboBox->currentIndex());

    return {AnalogActions, DiscreteActions};
}

void CommandsSettingsWidget::LoadSettings() {
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

void CommandsSettingsWidget::SaveSettings() {
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

void CommandsSettingsWidget::StartWidget() {
    timer_.start(TIMEOUT_ms);
}

void CommandsSettingsWidget::StopWidget() {
    timer_.stop();
}

void CommandsSettingsWidget::SendCommand() {

    gamepad_.UpdateGamepadId(resources_.GamepadId);

    auto gamepadSettings = GetGamepadSettings();

    //ToDo: motov.s убрать
    /*test*/
//    using AnalogActionEnum = GamepadSettingsStruct::AnalogActionEnum;
//    using AnalogAxisEnum = GamepadSettingsStruct::AnalogAxisEnum;
//    using AnalogAxis = GamepadSettingsStruct::AnalogAxis;
//
//    GamepadSettingsStruct::AnalogSettings_t analogSettings;
//
//    analogSettings[AnalogActionEnum::MoveX] = AnalogAxis{AnalogAxisEnum::LeftStickX, false};
//
//    GamepadSettingsStruct gamepadSettings{analogSettings};
    /*test*/

    auto commands = gamepad_.GetCommands(gamepadSettings);

    using MoveEnum = CommandsStruct::MoveEnum;

    std::cout << "Fx: " << commands.Move[MoveEnum::Fx] << ' '
              << "Fy: " << commands.Move[MoveEnum::Fy] << ' '
              << "Fz: " << commands.Move[MoveEnum::Fz] << ' '
              << "Mx: " << commands.Move[MoveEnum::Mx] << ' '
              << "My: " << commands.Move[MoveEnum::My] << ' '
              << "Mz: " << commands.Move[MoveEnum::Mz] << ' '
              << std::endl;



    //auto response = resources_.Network.SendRequest(commands, lib::network::Request::TypeEnum::W, 3);
}
