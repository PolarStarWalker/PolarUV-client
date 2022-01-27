#include "VideoStreamWidget.hpp"
#include <opencv2/videoio.hpp>
#include <thread>

SensorsWidnget::SensorsWidnget(QWidget *parent) {
    std::thread thread(&SensorsWidnget::StartClient, this);
    thread.join();
}

void SensorsWidnget::StartClient() {
    for (;;) {

        std::string pipeline;

        {
            std::fstream file("./Pipelines/client.txt", std::ios::in);
            file >> pipeline;
        }

        cv::VideoCapture stream(pipeline, cv::CAP_GSTREAMER);

        cv::Mat inFrame;

        while (isOnline_) {
            stream >> inFrame;

            if (inFrame.empty())
                isOnline_ = false;

            SetQPixmap(inFrame);
            cv::waitKey(20);

        }
    }
}

inline void SensorsWidnget::SetQPixmap(const cv::Mat &newFrame) {
    QImage image;

    switch (newFrame.type()) {
        case CV_8UC3: {
            image = QImage(newFrame.data, newFrame.cols, newFrame.rows, static_cast<int>(newFrame.step),
                           QImage::Format_RGB888);
            break;
        }
        case CV_8UC4: {
            image = QImage(newFrame.data, newFrame.cols, newFrame.rows, static_cast<int>(newFrame.step),
                           QImage::Format_ARGB32);
            break;
        }
    }

    image = std::move(image.rgbSwapped());
    QPixmap pixmap = QPixmap::fromImage(image);

    std::unique_lock lock(pixmapMutex_);
    pixmap_ = pixmap;
}
