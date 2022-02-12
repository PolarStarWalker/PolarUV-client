#include "VideoStream.hpp"
#include <fstream>
#include <VideoStreamMessage.pb.h>

//#include <boost/filesystem.hpp>
//#include <processenv.h>

constexpr std::string_view destination = " ! udpsink host=                 port=8000";
constexpr size_t DestinationIpPosition = destination.find('=') + 1;

constexpr char ImageNameTemplate[] = R"(\Media\Image\YYYY-MM-DD:HH-MM-SS.jpg)";
constexpr char VideoNameTemplate[] = R"(\Media\Video\YYYY-MM-DD:HH-MM-SS.mkv)";
constexpr char VideoNameMask[] = R"(\Media\Video\%Y-%m-%d-%H-%M-%S.mkv)";
constexpr char ImageNameMask[] = R"(\Media\Image\%Y-%m-%d-%H-%M-%S.jpg)";

enum ContentType : int8_t {
    Video,
    Image
};

//std::string CreateFileName(ContentType contentType) {
//char path[MAX_PATH]{};
//GetCurrentDirectory(MAX_PATH, path);
//    GetCurrentDirectory(MAX_PATH, path);
//    std::string fileName(path);
//    size_t pathSize = fileName.size();
//    fileName += contentType == Video ? VideoNameTemplate : ImageNameTemplate;
//
//    time_t now = time(nullptr);
//
//    struct tm *timeStruct = localtime(&now);
//
//    strftime(fileName.data() + pathSize,
//             fileName.size(),
//             contentType == Video ? VideoNameMask : ImageNameMask,
//             timeStruct);
//
//    return fileName;
//}

using namespace lib::processing;

VideoStream::VideoStream() :
        capture_(),
        qImage_(),
        isListen_(false),
        isOnline_(false),
        isDone_(false){
    thread_ = std::thread(&VideoStream::StartClient, this);
}

void VideoStream::StartClient() {
    while (!isDone_.load()) {

        std::string pipeline;

        {
            std::fstream file("./Pipelines/client.txt", std::ios::in);
            std::getline(file, pipeline);
        }

        isListen_.store(true);
        capture_.open(pipeline, cv::CAP_GSTREAMER);
        isListen_.store(false);
        isOnline_.store(true);

        cv::Mat inFrame;

        while (isOnline_.load()) {
            capture_ >> inFrame;

            if (inFrame.empty())
                isOnline_.store(false);

            SetQImage(inFrame);
            cv::waitKey(10);
        }

        isOnline_.store(false);
    }
}

inline void VideoStream::SetQImage(const cv::Mat &frame) {
    QImage image;

    switch (frame.type()) {
        case CV_8UC3: {
            image = QImage(frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888);
            break;
        }
        case CV_8UC4: {
            image = QImage(frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_ARGB32);
            break;
        }
    }

    image = image.rgbSwapped();

    std::unique_lock lock(qImageMutex_);
    qImage_ = std::move(image);
}

void VideoStream::RestartClient() {
    capture_.release();
}

std::string VideoStream::GetStartMessage(const std::string &clientIp) {

    std::string pipeline;
    {
        std::fstream file("./Pipelines/robot.txt", std::ios_base::in);
        std::getline(file, pipeline);
    }

    pipeline.append(destination);

    std::memcpy(pipeline.end().base() - destination.size() + DestinationIpPosition, clientIp.c_str(), clientIp.size());

    VideoStreamMessage message;
    message.set_action(VideoStreamMessage::START);
    message.set_pipeline(pipeline);

    return message.SerializeAsString();
}

std::string VideoStream::GetStopMessage() {
    VideoStreamMessage message;
    message.set_action(VideoStreamMessage::STOP);
    message.set_pipeline("");

    return message.SerializeAsString();
}

VideoStream::~VideoStream() {
    //ToDo: фикс закрытия
    isDone_.store(true);
    capture_.release();
    thread_.detach();
}