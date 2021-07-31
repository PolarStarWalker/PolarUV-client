#ifndef CLIENT_VIDEOPROTOCOL_HPP
#define CLIENT_VIDEOPROTOCOL_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>


class VideoProtocol {
public:
    VideoProtocol();
    ~VideoProtocol();

    void Start(const std::string& pipeline);

private:
    cv::VideoCapture _videoStream;
    bool _isOnline;
};


#endif
