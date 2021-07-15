#include "mainwindow.h"

#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();



    cv::namedWindow("Main", cv::WINDOW_NORMAL);

    cv::UMat frame;

    const char pipeline[] = "udpsrc port=5000 ! gdpdepay ! rtph264depay ! decodebin ! autovideoconvert  ! appsink sync=false";

    cv::VideoCapture videoStream;

    videoStream.open(pipeline, cv::CAP_GSTREAMER);

    if (!videoStream.isOpened()) {
        cout << "ERROR! Unable to open camera\n";
        //return -1;
    }

    while (1) {
         videoStream >> frame;

        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
                cv::imshow("Main", frame);
                cv::waitKey(5);

    }

    return  a.exec();;
}
