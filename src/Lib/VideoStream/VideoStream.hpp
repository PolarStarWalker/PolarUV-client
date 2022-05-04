#ifndef CLIENT_VIDEOSTREAM_HPP
#define CLIENT_VIDEOSTREAM_HPP

#include <thread>

#include "./Gstreamer.hpp"

namespace lib::processing {

    class VideoStream {
    public:

        VideoStream();

        ~VideoStream();

        void RestartClient();

        static std::string GetStartMessage(const std::string &clientIp);

        static std::string GetStopMessage();

        QImage GetQImage() {
            return gstreamer_.GetQImage();
        }

        bool IsOnline() {
            return isOnline_.load();
        }

    private:
        void StartClient();

        std::thread thread_;
        std::mutex qImageMutex_;

        std::atomic<bool> isOnline_;
        std::atomic<bool> isDone_;

        Gstreamer gstreamer_;
    };

}


#endif
