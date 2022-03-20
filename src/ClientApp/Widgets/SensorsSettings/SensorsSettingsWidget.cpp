#include "SensorsSettingsWidget.hpp"
#include "ui_SensorsSettingsWidget.h"


SensorsSettingsWidget::SensorsSettingsWidget(QWidget *parent, WidgetResources &resources) :
        QWidget(parent),
        resources_(resources),
        ui(new Ui::SensorsSettingsWidget) {

    ui->setupUi(this);

    connect(ui->ShowIndicatorsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(UpdateIndicatorsState(int)));
    connect(ui->MaxDepthSlider, SIGNAL(valueChanged(int)), this, SLOT(UpdateMaxDepth(int)));
    connect(ui->DepthCalibrationButton, SIGNAL(pressed()), this, SLOT(UpdateCalibration()));
}

SensorsSettingsWidget::~SensorsSettingsWidget() {
    delete ui;
}

void SensorsSettingsWidget::StartWidget() {

}

void SensorsSettingsWidget::StopWidget() {

}

/// ToDo: что-то сделать с этими слотами

void SensorsSettingsWidget::UpdateIndicatorsState(int state) {
    resources_.SensorsSettings.IndicatorsEnabled = (state == Qt::Checked);
}

void SensorsSettingsWidget::UpdateMaxDepth(int value) {
    ui->MaxDepthSlider->setValue(value - (value % 10));
    ui->MaxDepthEdit->setText(QString::number(value - (value % 10)));

    resources_.SensorsSettings.MaxDepth = value - (value % 10);
}

void SensorsSettingsWidget::UpdateCalibration() {
    float currentDepth = resources_.Sensors.Depth;
    resources_.SensorsSettings.DepthOffset = currentDepth;
    ui->DepthOffsetEdit->setText(QString::number(currentDepth));
}

