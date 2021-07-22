#ifndef CLIENT_VIDEOPROCESSING_HPP
#define CLIENT_VIDEOPROCESSING_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>


class VideoProcessing {
public:
    VideoProcessing();
    ~VideoProcessing();

    void Start(const std::string& pipeline);

private:
    cv::VideoCapture _videoStream;
    bool _isOnline;
};


#endif
