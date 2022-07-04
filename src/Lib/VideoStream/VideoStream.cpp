#include "VideoStream.hpp"
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

std::string VideoStream::GetStartMessage(const std::string &clientIp) {
    VideoMessage message;
    message.set_action(VideoMessage::START);

    auto &settings = *message.mutable_video_settings();

    settings.set_ip(std::string(clientIp));
    settings.set_device_name(std::string("/dev/video2"));
    settings.set_device_id(2);
    settings.set_framerate_numerator(0);
    settings.set_framerate_denumerator(0);
    settings.set_brightness(0);
    settings.set_contrast(0);


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

