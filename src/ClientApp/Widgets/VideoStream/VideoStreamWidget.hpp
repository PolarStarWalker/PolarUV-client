#ifndef CLIENT_VIDEOSTREAMWIDGET_HPP
#define CLIENT_VIDEOSTREAMWIDGET_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <fstream>
#include <shared_mutex>
#include <thread>
#include <QPixmap>

#include <QWidget>

class SensorsWidnget final : public QWidget {
Q_OBJECT
public:

    static constexpr std::string_view PIPELINE_PATH = "./Pipelines";
    explicit SensorsWidnget(QWidget* parent  = nullptr);

    QPixmap GetPixmap(){
        std::shared_lock guard(pixmapMutex_);
        QPixmap pixmap = pixmap_;
        pixmap_ = QPixmap();
        return pixmap;
    }

private:
    [[noreturn]]
    void StartClient();

    std::shared_mutex pixmapMutex_;
    QPixmap pixmap_;

    std::atomic<bool> isOnline_;

    void SetQPixmap(const cv::Mat &newFrame);
};


#endif
