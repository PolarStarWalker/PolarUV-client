#include "VideoStream.hpp"
#include "../../ClientApp/Widgets/WidgetResources.hpp"
#include <fstream>
#include <iostream>
#include <VideoStreamMessage.pb.h>

//#include <boost/filesystem.hpp>
//#include <processenv.h>

using namespace lib::processing;

VideoStream::VideoStream() :
        isOnline_(false),
        isDone_(false) {
    thread_ = std::thread(&VideoStream::StartClient, this);
}

void VideoStream::StartClient() {

    if (!gstreamer_)
        std::terminate();

    gstreamer_.Setup();

    while (!isDone_) {

        gstreamer_.SetStatePlaying();

        for (;;) {

            auto newFrame = gstreamer_.GetFrame();
            if (newFrame.isNull())
                break;

            isOnline_.store(true);

            SetImage(std::move(newFrame));
        }

        isOnline_.store(false);
    }
}

//ToDo: DanShoo add filling from interface
std::string VideoStream::GetStartMessage(const std::string &clientIp, const CameraSettingsStruct &cameraSettings) {
    VideoMessage message;
    message.set_action(VideoMessage::START);

    auto &settings = *message.mutable_video_settings();

    settings.set_ip(std::string(clientIp));
    settings.set_device_name(std::string(cameraSettings.DeviceName));
    settings.set_framerate_numerator(0);
    settings.set_framerate_denumerator(0);
    settings.set_brightness(cameraSettings.Brightness);
    settings.set_contrast(cameraSettings.Contrast);

    return message.SerializeAsString();
}

std::string VideoStream::GetStopMessage() {
    VideoMessage message;
    message.set_action(VideoMessage::STOP);

    return message.SerializeAsString();
}

VideoStream::~VideoStream() {
    isDone_.store(true);
    thread_.detach();
}

void VideoStream::SetImage(QImage &&img) {
    std::lock_guard lock(qImageMutex_);
    frame = img;
}

