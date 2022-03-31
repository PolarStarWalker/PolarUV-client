#ifndef CLIENT_SCREENSHOTTER_HPP
#define CLIENT_SCREENSHOTTER_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <QImage>


class ScreenShotter {

    class ScreenshotsQueue {

        std::queue<QImage> screenshots_;
        std::condition_variable isNotEmpty_;
        std::mutex queueMutex_;

    public:

        /// If frame is empty, thread will stop
        inline void AddFrame(const QImage &screenshot) {
            auto screenshotCopy = screenshot;
            AddFrame(std::move(screenshotCopy));
        }

        /// If frame is empty, thread will stop
        inline void AddFrame(QImage &&screenshot) {
            std::unique_lock lock(queueMutex_);
            screenshots_.push(std::move(screenshot));

            isNotEmpty_.notify_one();
        }

        inline QImage GetFrame() {
            std::unique_lock lock(queueMutex_);

            isNotEmpty_.wait(lock, [&]() { return !screenshots_.empty(); });

            auto screenshot = std::move(screenshots_.back());
            screenshots_.pop();

            return screenshot;
        }

    };

    ScreenshotsQueue queue_;
    std::thread thread_;


    void TakeScreenshot();

public:

    ScreenShotter();
    ~ScreenShotter();

    inline void AddToQueue(QImage&& frame){
        queue_.AddFrame(std::move(frame));
    }

    inline void AddToQueue(const QImage& frame){
        queue_.AddFrame(frame);
    }

};


#endif