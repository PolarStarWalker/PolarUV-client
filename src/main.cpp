
#include <iostream>

#include "main.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //MainWindow w;
    //w.show();

    cv::namedWindow("Main", cv::WINDOW_NORMAL);

    cv::UMat frame;

    const char pipeline[] = "udpsrc port=5000 ! gdpdepay ! rtph264depay ! decodebin ! autovideoconvert  ! appsink sync=false";

    cv::VideoCapture videoStream;

    videoStream.open(pipeline, cv::CAP_GSTREAMER);

    if (!videoStream.isOpened()) {
        std::cout << "Чё-та стримчанского я не вижу\n";
        return -1;
    }

    while (1) {
        videoStream >> frame;

        if (frame.empty()) {
            std::cout << "Кадров больше нет\n";
            return  -2;
        }
        cv::imshow("Main", frame);
        cv::waitKey(5);

    }

    return a.exec();
}
