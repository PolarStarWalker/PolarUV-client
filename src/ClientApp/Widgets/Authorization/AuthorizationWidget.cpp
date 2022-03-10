#include "AuthorizationWidget.hpp"
#include "ui_AuthorizationWidget.h"

#include <QWindow>
#include <QMessageBox>

#include "../Input/Gamepad.hpp"

#include "IPFunction.hpp"

AuthorizationWidget::AuthorizationWidget(QMainWindow *parent) :
        QWidget(parent),
        ui(new Ui::AuthorizationWidget),
        settings_("NARFU", "PolarROVClient"),
        ioContext_(),
        resources_() {

    ui->setupUi(this);

    if (!settings_.value("RobotIP").isNull()) {
        ui->RobotIPEdit->setText(settings_.value("RobotIP").toString());
    }

    /// Создаем в ресурсах два OpenGL-буфера для кадров
//    renderWindow_.setSurfaceType(QWindow::OpenGLSurface);
//    renderWindow_.create();
//
//    openGLContext_.create();
//    openGLContext_.makeCurrent(&renderWindow_);
//
//    fboFormat_.setSamples(16);
//    fboFormat_.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
//
//    resources_.telemetryFBO = new QOpenGLFramebufferObject(1920, 1080, fboFormat_);
//    resources_.displayFBO = new QOpenGLFramebufferObject(1920, 1080, fboFormat_);

    /// Соединяем собственные слоты
    connect(ui->RefreshClientIPsButton, SIGNAL(clicked(bool)), this, SLOT(RefreshClientIPs()));
    connect(ui->RefreshGamepadIDsButton, SIGNAL(clicked(bool)), this, SLOT(RefreshGamepadIDs()));
    connect(ui->LaunchButton, SIGNAL(clicked(bool)), this, SLOT(LaunchHandler()));

    /// Соединяем слоты MainWindow
    connect(ui->DebugButton, SIGNAL(clicked(bool)), parent, SLOT(LaunchDebug()));
    connect(this, SIGNAL(StartWidget()), parent, SLOT(Launch()));
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
    auto gamepads = control::GetGamepadsIds();
    ui->GamepadComboBox->clear();

    for (auto &&id: gamepads)
        ui->GamepadComboBox->addItem(QString::number(id));
}

void AuthorizationWidget::LaunchHandler() {

    auto ip = ui->RobotIPEdit->text().toStdString();

    bool isConnected = resources_.Network.TryConnect(ip);

    if (!isConnected) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось подключиться к роботу");
        return;
    }

    settings_.setValue("RobotIP", ui->RobotIPEdit->text());


    resources_.ClientIp = ui->ClientIPComboBox->currentText().toStdString();

    emit StartWidget();
}

