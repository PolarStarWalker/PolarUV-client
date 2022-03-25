#include "DisplayWidget.hpp"
#include "ui_DisplayWidget.h"

#include <QPainter>
#include <QMessageBox>
#include <iostream>

void DisplayWidget::SwitchVideoStream() {
    std::string message;

    if (stream_.IsOnline()) {
        message = lib::processing::VideoStream::GetStopMessage();
        stream_.RestartClient();
    } else {
        message = lib::processing::VideoStream::GetStartMessage(resources_.ClientIp);
    }

    resources_.Network.SendRequest(message, lib::network::Request::TypeEnum::W, 2);
}

void DisplayWidget::SwitchVideoCapture() {

}

void DisplayWidget::SetScreenshotFlag() {
    screenshotFlag_ = true;
}

void DisplayWidget::initializeGL() {

}

void DisplayWidget::resizeGL(int w, int h) {

}

void DisplayWidget::paintGL() {

    const auto &sensors = resources_.Sensors;
    const auto &sensorsSettings = resources_.SensorsSettings;

    QImage currentFrame{};

    if (stream_.IsOnline()) {
        auto videoFrame = stream_.GetQImage();

        if (!videoFrame.isNull()) {
            videoFrame_ = std::move(videoFrame).mirrored(true, true);
        }

        currentFrame = videoFrame_.scaled(this->width(), this->height());
    } else {
        currentFrame = placeholderImage_.scaled(this->width(), this->height());
    }

    drawer_.Begin(&currentFrame)
            .SetRenderHint(QPainter::Antialiasing)
            .SetResolution(width(), height())
            .DrawImage(0, 0, currentFrame);

    if (sensorsSettings.IndicatorsEnabled) {
        //ToDo исправить это безобразие (перенести сразу в функции)
        float rotationZ = (sensors.Rotation[SensorsStruct::Z] >= sensorsSettings.OrientationOffsetZ) ?
                          sensors.Rotation[SensorsStruct::Z] - sensorsSettings.OrientationOffsetZ :
                          sensors.Rotation[SensorsStruct::Z] - sensorsSettings.OrientationOffsetZ + 360;
        drawer_.Draw(PaintYawIndicator, rotationZ)
                .Draw(PaintCentralIndicator, sensors.Rotation[SensorsStruct::X], sensors.Rotation[SensorsStruct::Y])
                .Draw(PaintDepthIndicator, sensors.Depth - sensorsSettings.DepthOffset, sensorsSettings.MaxDepth)
                .Draw(PaintTextInfo, sensors.MotionCalibration);
    }

    drawer_.DrawImage(width() / 2 - 400 - 60, 0, currentFrame, width() / 2 - 400 - 60, 0, 60, 30)
            .DrawImage(width() / 2 + 400, 0, currentFrame, width() / 2 + 400, 0, 60, 30)
            .End();

    if (screenshotFlag_) {
        static size_t counter = 0;
        screenshotFlag_ = false;
        currentFrame.save(QString("Media/Image/screen-%1.png").arg(++counter));
        ///ToDo неблокирующая всплывашка
        //QMessageBox::information(nullptr, "Скриншот", "Вы жёстко сохранили скриншот");
    }

    drawer_.Begin(this)
            .DrawImage(0, 0, currentFrame)
            .End();

}