#include "Screenshotter.hpp"
#include <QString>
#include <ctime>
#include <filesystem>

constexpr std::wstring_view ImageNameTemplate = LR"(\Media\Image\YYYY-MM-DD:HH-MM-SS.png)";
constexpr std::wstring_view VideoNameTemplate = LR"(\Media\Video\YYYY-MM-DD:HH-MM-SS.mkv)";
constexpr std::wstring_view VideoNameMask = LR"(\Media\Video\%Y-%m-%d-%H-%M-%S.mkv)";
constexpr std::wstring_view ImageNameMask = LR"(\Media\Image\%Y-%m-%d-%H-%M-%S.png)";

enum ContentType : int8_t {
    Video,
    Image
};

QString CreateFileName(ContentType contentType) {
    auto path = std::filesystem::path();

    std::wstring fileName(path.c_str());
    size_t pathSize = fileName.size();
    fileName += contentType == Video ? VideoNameTemplate : ImageNameTemplate;

    time_t now = time(nullptr);

    struct tm *timeStruct = localtime(&now);

    wcsftime(fileName.data() + pathSize,
             fileName.size(),
             contentType == Video ? VideoNameMask.begin() : ImageNameMask.begin(),
             timeStruct);

    return QString::fromStdWString(fileName);
}

ScreenShotter::ScreenShotter(): queue_(), thread_(&ScreenShotter::TakeScreenshot, this) {}
ScreenShotter::~ScreenShotter() { queue_.AddFrame(QImage()); thread_.join();}

void ScreenShotter::TakeScreenshot(){
    for(;;){

        auto screenshot = queue_.GetFrame();

        if(screenshot.isNull())
            return;

        screenshot.save(CreateFileName(Image));
    }
}