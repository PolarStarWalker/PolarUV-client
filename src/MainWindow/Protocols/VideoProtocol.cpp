#include <iostream>
#include "VideoProtocol/VideoProtocol.hpp"

VideoProtocol::VideoProtocol() {
    this->_isOnline = false;
    this->_isThreadActive = false;
}

VideoProtocol::~VideoProtocol() {
    this->SetOnlineStatus(false);
    while (this->IsThreadActive())
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void VideoProtocol::Start(const std::string &pipeline) {

    this->_videoStream.open(pipeline, cv::CAP_GSTREAMER);

    if (_videoStream.isOpened()) {
        SetOnlineStatus(true);
    }

    cv::Mat inFrame;

    while (this->IsOnline()) {

        this->_videoStream >> inFrame;

        if (inFrame.empty())
            continue;

        cv::waitKey(1);

        this->SetMatrix(std::move(inFrame));
    }

    this->_videoStream.release();
    this->SetOnlineStatus(false);
}

void VideoProtocol::Stop() {
    this->SetOnlineStatus(false);
}

cv::Mat VideoProtocol::GetMatrix() {

    this->_frameMutex.lock_shared();
    cv::Mat outFrame = this->_currentFrame;
    this->_frameMutex.unlock_shared();

    return outFrame;
}

void VideoProtocol::StartAsync(const std::string& pipeline) {
    if(this->IsOnline())
        return;

    std::thread thread(&VideoProtocol::Start, this, pipeline);
    thread.detach();
}

