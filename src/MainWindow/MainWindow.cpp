
#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

#define SERVER_IP "169.254.154.5"
#define PORT 1999
#define COMMAND_DELAY 3000

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

void MainWindow::on_socketConnectButton_clicked() {

    if (!dataProtocol.GetStatus()) {

        std::cout << "Connecting to server\n";
        if (dataProtocol.ConnectToServer(SERVER_IP, PORT)) {

            std::cout << "Connected\n";

            QByteArray qByteCommand(CommandsStructLen, 0);

            for (size_t i = 0;; i++) {

                ((CommandsStruct *) qByteCommand.data())->VectorArray[0] = i;
                dataProtocol.SendCommand(qByteCommand);

                /// Инновационное неблокирующее ожидание
                std::chrono::steady_clock::time_point startingTimePoint = std::chrono::steady_clock::now();
                std::chrono::steady_clock::time_point currentTimePoint;
                while (1) {
                    currentTimePoint = std::chrono::steady_clock::now();
                    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint - startingTimePoint);
                    if (elapsedMs >= std::chrono::milliseconds(COMMAND_DELAY)) {break;}
                }
            }
        } else {
            std::cout << "Can't connect to server\n";
        };
    }
    else {
        dataProtocol.Disconnect();
        std::cout << "Disconnected\n";
    };
};