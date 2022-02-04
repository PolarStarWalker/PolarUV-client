#include "AutorizationWidget.hpp"
#include "ui_AutorizationWidget.h"

#include <iphlpapi.h>

std::list<std::string> GetIps();

AutorizationWidget::AutorizationWidget(QMainWindow *mainWindow, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::AutorizationWidget),
        settings_("NARFU","PolarROVClient"){

    ui->setupUi(this);

    if (!settings_.value("RobotIP").isNull()) {
        ui->RobotIPEdit->setText(settings_.value("RobotIP").toString());
    }

    /// Соединяем собственные слоты
    connect(ui->RefreshClientIPsButton, SIGNAL(clicked(bool)),this,SLOT(RefreshClientIPs()));
    connect(ui->RefreshGamepadIDsButton, SIGNAL(clicked(bool)),this, SLOT(RefreshGamepadIDs()));
    connect(ui->LaunchButton, SIGNAL(clicked(bool)),this,SLOT(LaunchHandler()));

    /// Соединяем слоты MainWindow
    connect(this, SIGNAL(Launched(QString,QString,int)),
            mainWindow, SLOT(Launch(QString,QString,int)));
    connect(ui->DebugButton, SIGNAL(clicked(bool)), mainWindow, SLOT(LaunchDebug()));
}

AutorizationWidget::~AutorizationWidget() {
    delete ui;
}

void AutorizationWidget::RefreshClientIPs() {
    auto addresses = GetIps();

    ui->ClientIPComboBox->clear();

    for (auto &&address: addresses)
        ui->ClientIPComboBox->addItem(QString::fromStdString(address));
}

void AutorizationWidget::RefreshGamepadIDs() {
    auto gamepads = Control::GetGamepadsIds();
    ui->GamepadComboBox->clear();

    for (auto &&id: gamepads)
        ui->GamepadComboBox->addItem(QString::number(id));
}

void AutorizationWidget::LaunchHandler() {

    emit StartWidget();

    /// ToDo: проверка подключения и передача параметров
    settings_.setValue("RobotIP",ui->RobotIPEdit->text());
    emit Launched(ui->RobotIPEdit->text(),
                  ui->ClientIPComboBox->currentText(),
                  ui->GamepadComboBox->currentText().toInt());

}


std::list<std::string> GetIps(){

    std::list<std::string> addresses;

    PIP_ADAPTER_INFO adapterInfo = nullptr;
    ULONG ulOutBufLen = 0;

    DWORD result = GetAdaptersInfo(nullptr, &ulOutBufLen);

    if (result == ERROR_BUFFER_OVERFLOW) {
        HeapFree(GetProcessHeap(), 0, adapterInfo);
        adapterInfo = new IP_ADAPTER_INFO[ulOutBufLen / sizeof(IP_ADAPTER_INFO)];
        result = GetAdaptersInfo(adapterInfo, &ulOutBufLen);
    }

    if (result != ERROR_SUCCESS) {
        HeapFree(GetProcessHeap(), 0, adapterInfo);
    } else {
        PIP_ADAPTER_INFO deleteAdapter = adapterInfo;
        std::string nullIp = "0.0.0.0";
        for (size_t i = 0; i < ulOutBufLen / sizeof(IP_ADAPTER_INFO); ++i) {
            bool isEqual = !strcmp(nullIp.c_str(), adapterInfo->IpAddressList.IpAddress.String);
            if (isEqual) {
                adapterInfo = adapterInfo->Next;
                continue;
            }
            addresses.emplace_back(std::string(adapterInfo->IpAddressList.IpAddress.String));
            adapterInfo = adapterInfo->Next;
        }
        delete[] deleteAdapter;
    }

    return addresses;
}