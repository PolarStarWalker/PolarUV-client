#ifndef CLIENT_VIDEOSTREAM_HPP
#define CLIENT_VIDEOSTREAM_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <shared_mutex>
#include <thread>
#include <QImage>

namespace lib::processing {
    class VideoStream {
    public:

        VideoStream();
        ~VideoStream();

        void RestartClient();

        static std::string GetStartMessage(const std::string &clientIp);
        static std::string GetStopMessage();

        QImage GetQImage() {
            std::unique_lock lock(qImageMutex_);
            QImage pixmap = qImage_;
            qImage_ = QImage();
            return pixmap;
        }

        bool IsOnline(){
            return isOnline_.load();
        }

    private:
        void StartClient();

        std::thread thread_;

        std::shared_mutex qImageMutex_;
        cv::VideoCapture capture_;
        QImage qImage_;

        std::atomic<bool> isOnline_;
        std::atomic<bool> isListen_;
        std::atomic<bool> isDone_;

        void SetQImage(const cv::Mat &frame);
    };

}


#endif
