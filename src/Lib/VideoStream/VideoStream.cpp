#include "VideoStream.hpp"
#include <fstream>
#include <iostream>
#include <VideoStreamMessage.pb.h>

//#include <boost/filesystem.hpp>
//#include <processenv.h>

constexpr std::string_view destination = " ! udpsink host=                 port=8000";
constexpr size_t DestinationIpPosition = destination.find('=') + 1;

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

        for(;;){

            auto newFrame = gstreamer_.GetFrame();
            if(newFrame.isNull())
                break;

            isOnline_.store(true);

            SetImage(std::move(newFrame));
        }

        isOnline_.store(false);
    }
}

std::string VideoStream::GetStartMessage(const std::string &clientIp) {

    std::string pipeline;
    {
        std::fstream file("./Pipelines/robot.txt", std::ios_base::in);
        std::getline(file, pipeline);
    }

    pipeline.append(destination);

    std::memcpy(pipeline.end().base() - destination.size() + DestinationIpPosition, clientIp.c_str(), clientIp.size());

    VideoStreamMessage message;
    message.set_action(VideoStreamMessage::START);
    message.set_pipeline(pipeline);

    return message.SerializeAsString();
}

std::string VideoStream::GetStopMessage() {
    VideoStreamMessage message;
    message.set_action(VideoStreamMessage::STOP);
    message.set_pipeline("");

    return message.SerializeAsString();
}

VideoStream::~VideoStream() {
    isDone_.store(true);
    thread_.detach();
}

void VideoStream::SetImage(QImage&& img) {
    std::lock_guard lock(qImageMutex_);
    frame = img;
}

