#include "SensorsSettingsWidget.hpp"
#include "ui_SensorsSettingsWidget.h"


SensorsSettingsWidget::SensorsSettingsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SensorsSettingsWidget) {
    ui->setupUi(this);
}

SensorsSettingsWidget::~SensorsSettingsWidget() {
    delete ui;
}

