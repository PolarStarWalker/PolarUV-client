
#include <QMessageBox>

#include "AuthorizationWidget.hpp"
#include "ui_AuthorizationWidget.h"

#include <Gamepad/Gamepad.hpp>

#include "IPFunction.hpp"


AuthorizationWidget::AuthorizationWidget(QMainWindow *mainWindow, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::AuthorizationWidget),
        settings_("NARFU", "PolarROVClient"),
        ioContext_(),
        resources_(ioContext_){

    ui->setupUi(this);

    if (!settings_.value("RobotIP").isNull()) {
        ui->RobotIPEdit->setText(settings_.value("RobotIP").toString());
    }

    /// Соединяем собственные слоты
    connect(ui->RefreshClientIPsButton, SIGNAL(clicked(bool)), this, SLOT(RefreshClientIPs()));
    connect(ui->RefreshGamepadIDsButton, SIGNAL(clicked(bool)), this, SLOT(RefreshGamepadIDs()));
    connect(ui->LaunchButton, SIGNAL(clicked(bool)), this, SLOT(LaunchHandler()));

    /// Соединяем слоты MainWindow
    connect(this, SIGNAL(Launched(QString, QString, int)), mainWindow, SLOT(Launch(QString, QString, int)));
    connect(ui->DebugButton, SIGNAL(clicked(bool)), mainWindow, SLOT(LaunchDebug()));
}

AuthorizationWidget::~AuthorizationWidget() {
    delete ui;
}

void AuthorizationWidget::RefreshClientIPs() {
    auto addresses = GetIps();

    ui->ClientIPComboBox->clear();

    for (auto &&address: addresses)
        ui->ClientIPComboBox->addItem(QString::fromStdString(address));
}

void AuthorizationWidget::RefreshGamepadIDs() {
    auto gamepads = Control::GetGamepadsIds();
    ui->GamepadComboBox->clear();

    for (auto &&id: gamepads)
        ui->GamepadComboBox->addItem(QString::number(id));
}

void AuthorizationWidget::LaunchHandler() {

    auto ip = ui->RobotIPEdit->text().toStdString();

    ///ToDo: почему-то таймаут у socket.connect очень большой
    bool isConnected = resources_.Network.TryConnect(ip);

    if (!isConnected) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось подключиться к роботу");
        return;
    }

    settings_.setValue("RobotIP", ui->RobotIPEdit->text());

    emit StartWidget();

    emit Launched(ui->RobotIPEdit->text(),
                  ui->ClientIPComboBox->currentText(),
                  ui->GamepadComboBox->currentText().toInt());
}