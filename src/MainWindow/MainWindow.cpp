
#include "MainWindow.hpp"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartVideoCapture() {
    cv::namedWindow("Main", cv::WINDOW_NORMAL);

    cv::UMat inFrame, outFrame;

    this->stream.open(pipeline, cv::CAP_GSTREAMER);

    if (!this->stream.isOpened()) {
        std::cout << "Чё-та стримчанского я не вижу\n";
        return;
    }

    for (;;) {
        this->stream >> inFrame;

        if (inFrame.empty()) {
            std::cout << "Кадров больше нет\n";
            return;
        }

        outFrame = std::move(inFrame);
        cv::imshow("Main", outFrame);
    }
}

void MainWindow::StopVideoCapture() {
    this->stream.release();
}