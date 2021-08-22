#include "VideoProtocol/VideoProtocol.hpp"
#include "../DataStructs/VideoPipelineStruct/VideoPipelineStruct.hpp"


constexpr char pipeline[] = "udpsrc port=5000 ! gdpdepay ! rtph264depay ! decodebin ! autovideoconvert ! appsink sync=false";

VideoProtocol::VideoProtocol() {
    this->_isOnline = false;
    this->_isThreadActive = false;
}

VideoProtocol::~VideoProtocol() {
    this->SetOnlineStatus(false);
    while (this->IsThreadActive())
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void VideoProtocol::Start(const QString &address) {

    this->_videoStream.release();

    std::fstream file("./Pipelines/client.txt", std::ios_base::in);

    file.seekg(0, std::fstream::end);
    size_t size = file.tellg();
    file.seekg(0, std::fstream::beg);

    VideoPipelineStruct videoStruct(size + 1);

    file.read(videoStruct.StringBegin(), size);
    videoStruct.StringBegin()[size] = '\0';
    file.close();

    this->SendVideoScript(address);

    this->_videoStream.open(pipeline, cv::CAP_GSTREAMER);

    SetOnlineStatus(_videoStream.isOpened());

    cv::Mat inFrame;

    while (this->IsOnline()) {

        this->_videoStream >> inFrame;

        if (inFrame.empty())
            this->SetOnlineStatus(false);

        cv::waitKey(1);

        this->SetMatrix(std::move(inFrame));
    }

    this->_videoStream.release();
    this->SetThreadStatus(false);
}

void VideoProtocol::Stop(const QString &address) {
    if (this->SendStopSignal(address))
        this->SetOnlineStatus(false);
}

cv::Mat VideoProtocol::GetMatrix() {

    this->_frameMutex.lock_shared();
    cv::Mat outFrame = this->_currentFrame;
    this->_frameMutex.unlock_shared();

    return outFrame;
}

void VideoProtocol::StartAsync(const QString &address) {
    if (this->IsOnline())
        return;

    std::thread thread(&VideoProtocol::Start, this, address);
    thread.detach();
}

void VideoProtocol::SendVideoScript(const QString &address) {
    std::fstream file("./Pipelines/robot.txt", std::ios_base::in);

    file.seekg(0, std::fstream::end);
    size_t size = file.tellg();
    file.seekg(0, std::fstream::beg);

    VideoPipelineStruct videoStruct(size);

    file.read(videoStruct.StringBegin(), size);

    QTcpSocket socket;
    socket.connectToHost(address, 28840);
    socket.waitForConnected(500);

    char action = 's';

    socket.write(&action, 1);
    socket.waitForBytesWritten(500);

    socket.write(videoStruct.Begin(), videoStruct.Size() + 8);
    socket.waitForBytesWritten(500);
}

bool VideoProtocol::SendStopSignal(const QString &address) {
    QTcpSocket socket;
    socket.connectToHost(address, 28840);
    if (!socket.waitForConnected(500))
        return false;

    char signal = 'f';
    socket.write(&signal, 1);
    if (!socket.waitForBytesWritten(500))
        return false;

    return true;
}

