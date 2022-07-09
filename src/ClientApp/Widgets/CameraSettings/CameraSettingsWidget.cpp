#include "CameraSettingsWidget.hpp"
#include "ui_CameraSettingsWidget.h"


CameraSettingsWidget::CameraSettingsWidget(QWidget *parent, WidgetResources &resources) :
        QWidget(parent),
        ui(new Ui::CameraSettingsWidget),
        resources_(resources),
        settings_("NARFU", "PolarUV-Client") {

    ui->setupUi(this);

    /// Зарузка настроек из реестра
    LoadSettings();

    /// Привязка слотов
    this->connect(ui->RefreshCameraIDsButton, SIGNAL(clicked(bool)), this, SLOT(RefreshCameraIDs()));
    this->connect(ui->BrightnessSlider, SIGNAL(valueChanged(int)), SLOT(UpdateBrightnessEdit(int)));
    this->connect(ui->BrightnessEdit, SIGNAL(textChanged(QString)), SLOT(UpdateBrightnessSlider(QString)));
    this->connect(ui->ContrastSlider, SIGNAL(valueChanged(int)), SLOT(UpdateContrastEdit(int)));
    this->connect(ui->ContrastEdit, SIGNAL(textChanged(QString)), SLOT(UpdateContrastSlider(QString)));
    this->connect(ui->RotatedCheckBox, SIGNAL(stateChanged(int)), SLOT(UpdateRotatedCheckBox(int)));
}

CameraSettingsWidget::~CameraSettingsWidget() {
    delete ui;
}

void CameraSettingsWidget::StartWidget() {

}

void CameraSettingsWidget::StopWidget() {

}

void CameraSettingsWidget::LoadSettings() {
    /// Яркость изображения
    if (!settings_.value("CameraBrightness").isNull()) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.CameraBrightness = settings_.value("CameraBrightness").toInt();
        /// Обновление состояния поля ввода
        ui->BrightnessEdit->setText(settings_.value("CameraBrightness").toString());
    }
    /// Контрастность изображения
    if (!settings_.value("CameraContrast").isNull()) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.CameraContrast = settings_.value("CameraContrast").toInt();
        /// Обновление состояния поля ввода
        ui->ContrastEdit->setText(settings_.value("CameraContrast").toString());
    }
    /// Переворот изображения
    if (!settings_.value("CameraRotated").isNull()) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.CameraRotated = settings_.value("CameraRotated").toBool();
        /// Обновление состояния чек-бокса
        ui->RotatedCheckBox->setChecked(settings_.value("CameraRotated").toBool());
    }
}

void CameraSettingsWidget::RefreshCameraIDs() {
    // ToDo: motov.s получение списка доступных камер
    // ToDo: shushkov.d заполнение комбобокса индексами камер
}

void CameraSettingsWidget::UpdateBrightnessEdit(int value) {
    /// Обновление состояния поля ввода
    ui->BrightnessEdit->setText(QString::number(value));
    /// Обновление переменной в ресурсах
    resources_.CameraSettings.CameraBrightness = value;
    /// Обновление переменной в реестре
    settings_.setValue("CameraBrightness", value);
}

void CameraSettingsWidget::UpdateBrightnessSlider(const QString &string) {
    /// Обновление состояния слайдера
    ui->BrightnessSlider->setValue(string.toInt());
}

void CameraSettingsWidget::UpdateContrastEdit(int value) {
    /// Обновление состояния поля ввода
    ui->ContrastEdit->setText(QString::number(value));
    /// Обновление переменной в ресурсах
    resources_.CameraSettings.CameraContrast = value;
    /// Обновление переменной в реестре
    settings_.setValue("CameraContrast", value);
}

void CameraSettingsWidget::UpdateContrastSlider(const QString &string) {
    /// Обновление состояния слайдера
    ui->ContrastSlider->setValue(string.toInt());
}

void CameraSettingsWidget::UpdateRotatedCheckBox(int state) {
    /// Обновление переменной в ресурсах
    resources_.CameraSettings.CameraRotated = (state == Qt::Checked);
    // Обновление переменной в реестре
    settings_.setValue("CameraRotated", (state == Qt::Checked));
}
