#include "ClientSettingsWidget.hpp"
#include "ui_ClientSettingsWidget.h"

#include "./DataStructs/DataStructs.hpp"
#include "./Protocols/Protocols.hpp"
#include "./Gamepad/Gamepad.hpp"
#include <Exceptions/Exceptions.hpp>

#include <iostream>


ClientSettingsWidget::ClientSettingsWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ClientSettingsWidget) {
    ui->setupUi(this);
}

ClientSettingsWidget::~ClientSettingsWidget() {
    delete ui;
}

//void ClientSettingsWidget::SaveClientSettings() {
//    auto method = Function([&]() { this->RawSaveClientSettings(); });
//    ExceptionHandler(method, "Сообщение", "Настройки успешно сохранены");
//}
//
//void ClientSettingsWidget::LoadClientSettings() {
//    auto method = Function([&]() { this->RawLoadClientSettings(); });
//    ExceptionHandler(method, "Успех", "Настройки успешно загружены");
//}
//
//void ClientSettingsWidget::RefreshGamepads() {
//    auto gamepads = Control::GetGamepadsIds();
//    ui->GamepadComboBox->clear();
//
//    for (auto &&id: gamepads)
//        ui->GamepadComboBox->addItem(QString::number(id));
//
//    // The path to get the selected ID:
//    // int id = ui->GamepadComboBox->itemText(ui->GamepadComboBox->currentIndex()).toInt()
//}
//
//void ClientSettingsWidget::RefreshClientIps() {
//    auto addresses = GetClientIps();
//    ui->ClientIPComboBox->clear();
//    for (auto &&address: addresses)
//        ui->ClientIPComboBox->addItem(QString::fromStdString(address));
//
//    // The path to get the selected IP:
//    // QString ip = ui->ClientIPComboBox->itemText(ui->ClientIPComboBox->currentIndex());
//
//}

void ClientSettingsWidget::UpdateGeometry(QSize newParentSize) {
    int x = (newParentSize.width() - this->width()) / 2;
    int y = (newParentSize.height() - this->height()) / 2;
    this->move(x,y);
}

