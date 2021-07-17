
#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

#define SERVER_IP "169.254.154.5"
#define PORT 1999

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

void MainWindow::on_socketConnectButton_clicked()
{
    DataProtocol dataProtocol;

    std::cout << "Connecting to server\n";
    if (dataProtocol.ConnectToServer(SERVER_IP,PORT)) {

        std::cout << "Connected\n";

        QByteArray qByteCommand(CommandsStructLen,0);

        for (size_t i = 0;;i++) {

            ((CommandsStruct*)qByteCommand.data())->VectorArray[0] = i;
            dataProtocol.SendCommand(qByteCommand);
            Sleep(3000);
        }
    }
    else {
        std::cout << "Can't connect to server\n";
    };
};