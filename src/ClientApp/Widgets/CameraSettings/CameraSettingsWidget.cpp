#include "CameraSettingsWidget.hpp"
#include "ui_CameraSettingsWidget.h"

using Request = lib::network::Request;
using Response = lib::network::Response;

CameraSettingsWidget::CameraSettingsWidget(QWidget *parent, WidgetResources &resources) :
        QWidget(parent),
        ui(new Ui::CameraSettingsWidget),
        resources_(resources),
        settings_("NARFU", "PolarUV-Client") {

    ui->setupUi(this);

    /// Загрузка настроек из реестра
    LoadSettings();

    /// Привязка слотов
    connect(ui->RefreshCameraNamesButton, SIGNAL(clicked(bool)), SLOT(RefreshCameraNames()));
    connect(ui->CameraNameComboBox, SIGNAL(currentTextChanged(QString)), SLOT(UpdateCameraName(QString)));
    connect(ui->BrightnessSlider, SIGNAL(valueChanged(int)), SLOT(UpdateBrightnessEdit(int)));
    connect(ui->BrightnessEdit, SIGNAL(textChanged(QString)), SLOT(UpdateBrightnessSlider(QString)));
    connect(ui->ContrastSlider, SIGNAL(valueChanged(int)), SLOT(UpdateContrastEdit(int)));
    connect(ui->ContrastEdit, SIGNAL(textChanged(QString)), SLOT(UpdateContrastSlider(QString)));
    connect(ui->RotatedCheckBox, SIGNAL(stateChanged(int)), SLOT(UpdateRotatedCheckBox(int)));
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

void CameraSettingsWidget::RefreshCameraNames() {

    auto response = resources_.Network.SendRequest(std::string(), Request::TypeEnum::R, 2);

    std::cout << response.Data << std::endl;

    /// Заполнение комбо-бокса
    //ui->CameraNameComboBox->clear()               <- Очищаем комбо-бокс
    //ui->CameraNameComboBox->addItem(std::string); <- Вставляем по одному элементу через цикл
}

void CameraSettingsWidget::UpdateCameraName(const QString &string) {
    if (string != nullptr) {
        /// Обновление переменной в ресурсах
        resources_.CameraSettings.CameraName = string.toStdString();
    }
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
    /// Обновление переменной в реестре
    settings_.setValue("CameraRotated", (state == Qt::Checked));
}
