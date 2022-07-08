#include "CameraSettingsWidget.hpp"
#include "ui_CameraSettingsWidget.h"


CameraSettingsWidget::CameraSettingsWidget(QWidget *parent, WidgetResources &resources) :
        QWidget(parent),
        ui(new Ui::CameraSettingsWidget),
        resources_(resources) {

    ui->setupUi(this);

    this->connect(ui->RefreshCameraIDsButton, SIGNAL(clicked(bool)), this, SLOT(RefreshCameraIDs()));
    this->connect(ui->BrightnessSlider, SIGNAL(valueChanged(int)), SLOT(UpdateBrightnessEdit(int)));
    this->connect(ui->BrightnessEdit, SIGNAL(textChanged(QString)), SLOT(UpdateBrightnessSlider(QString)));
    this->connect(ui->ContrastSlider, SIGNAL(valueChanged(int)), SLOT(UpdateContrastEdit(int)));
    this->connect(ui->ContrastEdit, SIGNAL(textChanged(QString)), SLOT(UpdateContrastSlider(QString)));
}

CameraSettingsWidget::~CameraSettingsWidget() {
    delete ui;
}

void CameraSettingsWidget::StartWidget() {

}

void CameraSettingsWidget::StopWidget() {

}

void CameraSettingsWidget::RefreshCameraIDs() {
    // ToDo: motov.s получение списка доступных камер
    // ToDo: shushkov.d заполнение комбобокса индексами камер
}

void CameraSettingsWidget::UpdateBrightnessEdit(int value) {
    ui->BrightnessEdit->setText(QString::number(value));
}

void CameraSettingsWidget::UpdateBrightnessSlider(const QString& string) {
    ui->BrightnessSlider->setValue(string.toInt());
}

void CameraSettingsWidget::UpdateContrastEdit(int value) {
    ui->ContrastEdit->setText(QString::number(value));
}

void CameraSettingsWidget::UpdateContrastSlider(const QString& string) {
    ui->ContrastSlider->setValue(string.toInt());
}
