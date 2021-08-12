#ifndef CLIENT_VIDEOPROTOCOL_HPP
#define CLIENT_VIDEOPROTOCOL_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <shared_mutex>
#include <thread>

#include "../../../../../robot/src/Robot/DataProtocols/BaseProtocol/BaseProtocol.hpp"

class VideoProtocol : public BaseProtocol{
public:
    VideoProtocol();
    ~VideoProtocol();

    void Start(const std::string& pipeline);
    void Stop();

    cv::Mat GetMatrix();

    void StartAsync(const std::string& pipeline);

private:

    std::shared_mutex _frameMutex;

    cv::VideoCapture _videoStream;
    cv::Mat _currentFrame;

    inline void SetMatrix(cv::Mat &&newFrame){
        this->_frameMutex.lock();
        this->_currentFrame = std::move(newFrame);
        this->_frameMutex.unlock();
    }

};


#endif
