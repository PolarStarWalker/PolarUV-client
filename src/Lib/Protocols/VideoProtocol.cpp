#include "VideoProtocol/VideoProtocol.hpp"
#include <ctime>
#include <processenv.h>

#include "DataStructs/VideoPipelineStruct/VideoPipelineStruct.hpp"

constexpr char destination[] = " ! udpsink host=                 port=5000";
const size_t DestinationSize = std::strlen(destination);
const size_t DestinationIpPosition = std::find(destination, destination + DestinationSize, '=') - destination + 1;

constexpr char ImageNameTemplate[] = R"(\Media\Image\YYYY-MM-DD:HH-MM-SS.jpg)";
constexpr char VideoNameTemplate[] = R"(\Media\Video\YYYY-MM-DD:HH-MM-SS.mkv)";
constexpr char VideoNameMask[] = R"(\Media\Video\%Y-%m-%d-%H-%M-%S.mkv)";
constexpr char ImageNameMask[] = R"(\Media\Image\%Y-%m-%d-%H-%M-%S.jpg)";


enum ContentType : int8_t {
    Video,
    Image
};

std::string CreateFileName(ContentType contentType) {
    char path[MAX_PATH]{};
    GetCurrentDirectory(MAX_PATH, path);
    std::string fileName(path);
    size_t pathSize = fileName.size();
    fileName += contentType == Video ? VideoNameTemplate : ImageNameTemplate;

    time_t now = time(nullptr);

    struct tm *timeStruct = localtime(&now);

    strftime(fileName.data() + pathSize,
             fileName.size(),
             contentType == Video ? VideoNameMask : ImageNameMask,
             timeStruct);

    return fileName;
}

void SendVideoScript(const QString &robotAddress, const QString &clientAddress) {
    std::fstream file("./Pipelines/robot.txt", std::ios_base::in);

    file.seekg(0, std::fstream::end);
    size_t size = (file.tellg());
    file.seekg(0, std::fstream::beg);

    size -= 2;

    VideoPipelineStruct videoStruct(size + DestinationSize);

    file.read(videoStruct.StringBegin(), size);

    std::memcpy(videoStruct.StringBegin() + size, destination, DestinationSize);
    std::string clientIp = clientAddress.toStdString();
    std::memcpy(videoStruct.StringBegin() + size + DestinationIpPosition, clientIp.c_str(), clientIp.size());

    QTcpSocket socket;
    socket.connectToHost(robotAddress, 28840);
    socket.waitForConnected(500);

    char action = 's';

    socket.write(&action, 1);
    socket.waitForBytesWritten(500);

    socket.write(videoStruct.Begin(), videoStruct.Size() + 8);
    socket.waitForBytesWritten(500);
}

static bool SendStopSignal(const QString &address) {
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


VideoProtocol::VideoProtocol() {
    this->_isOnline = false;
    this->_isThreadActive = false;
    this->_videoWriterStatus = false;
    this->_screenshotStatus = false;
}

VideoProtocol::~VideoProtocol() {
    this->SetOnlineStatus(false);
    while (this->IsThreadActive())
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    this->_videoStream.release();
    this->_videoWriter.release();
}

void VideoProtocol::Start(const QString &robotAddress, const QString &clientAddress) {

    this->_videoStream.release();
    this->_videoWriter.release();

    std::fstream file("./Pipelines/client.txt", std::ios_base::in);

    file.seekg(0, std::fstream::end);
    size_t size = file.tellg();
    file.seekg(0, std::fstream::beg);

    VideoPipelineStruct videoStruct(size + 1);

    file.read(videoStruct.StringBegin(), size);
    videoStruct.StringBegin()[size] = '\0';
    file.close();

    SendVideoScript(robotAddress, clientAddress);

    this->_videoStream.open(videoStruct.StringBegin(), cv::CAP_GSTREAMER);

    bool previousVideoWriterState = false;

    SetOnlineStatus(_videoStream.isOpened());

    cv::Mat inFrame;

    while (this->IsStreamOnline()) {

        this->_videoStream >> inFrame;

        if (inFrame.empty())
            this->SetOnlineStatus(false);


        if (IsVideoWriterOnline() && IsStreamOnline()) {
            if (!previousVideoWriterState) {

                std::string fileName = CreateFileName(Video);

                const int fourcc = cv::VideoWriter::fourcc('H', '2', '6', '4');;

                cv::Size frameSize = cv::Size((int) _videoStream.get(cv::CAP_PROP_FRAME_WIDTH),    // Acquire input size
                                              (int) _videoStream.get(cv::CAP_PROP_FRAME_HEIGHT));

                this->_videoWriter.open(fileName, fourcc, 24, frameSize, true);

                previousVideoWriterState = true;
            }

            this->_videoWriter.write(inFrame);

        } else if (previousVideoWriterState) {
            this->_videoWriter.release();
            this->SetVideoWriterState(false);
            previousVideoWriterState = false;
        }

        if (IsNeedScreenshot() && IsStreamOnline()) {
            std::string fileName = CreateFileName(Image);
            cv::imwrite(fileName, inFrame);
            this->SetScreenshotState(false);
        }

        cv::waitKey(20);

        SetQPixmap(inFrame);

        //SetMatrix(std::move(inFrame));
    }

    this->_videoStream.release();
    this->_videoWriter.release();
    this->SetThreadStatus(false);
}

void VideoProtocol::Stop(const QString &address) {
    if (!SendStopSignal(address))
        return;

    this->SetOnlineStatus(false);
    while (this->IsThreadActive()) {}
}

void VideoProtocol::StartVideoWrite() {
    if (!this->IsStreamOnline())
        return;

    SetVideoWriterState(true);
}

void VideoProtocol::StopVideoWrite() {
    SetVideoWriterState(false);
}

void VideoProtocol::StartAsync(const QString &robotAddress, const QString &clientAddress) {
    if (this->IsStreamOnline())
        return;

    std::thread thread(&VideoProtocol::Start, this, robotAddress, clientAddress);
    thread.detach();
}

void VideoProtocol::TakeScreenshot() {
    this->SetScreenshotState(true);
}


QPixmap VideoProtocol::GetPixmap() {
    _qPixmapMutex.lock_shared();
    QPixmap pixmap = _pixmap;
    _qPixmapMutex.unlock_shared();

    return pixmap;
}

void VideoProtocol::SetQPixmap(const cv::Mat &newFrame) {
    QImage image;

    switch (newFrame.type()) {
        case CV_8UC3: {
            image = QImage(newFrame.data, newFrame.cols, newFrame.rows, static_cast<int>(newFrame.step), QImage::Format_RGB888);
            break;
        }
        case CV_8UC4: {
            image = QImage(newFrame.data, newFrame.cols, newFrame.rows, static_cast<int>(newFrame.step), QImage::Format_ARGB32);
            break;
        }
    }

    image = std::move(image.rgbSwapped());
    QPixmap pixmap = QPixmap::fromImage(image);

    _qPixmapMutex.lock();
    _pixmap = std::move(pixmap);
    _qPixmapMutex.unlock();
}
