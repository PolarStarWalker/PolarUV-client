#ifndef CLIENT_VIDEOPROTOCOL_HPP
#define CLIENT_VIDEOPROTOCOL_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <fstream>
#include <shared_mutex>
#include <thread>

#include <QTcpSocket>
#include "../BaseProtocol/BaseProtocol.hpp"

class VideoProtocol : public BaseProtocol{
public:
    VideoProtocol();
    ~VideoProtocol();

    ///ToDo потоки будут плодиться
    void StartAsync(const QString &robotAddress, const QString &clientAddress);
    void Start(const QString &robotAddress, const QString &clientAddress);
    void Stop(const QString& address);

    cv::Mat GetMatrix();

    void StartVideoWrite();
    void StopVideoWrite();

    static void SendVideoScript(const QString &robotAddress, const QString &clientAddress);
    static bool SendStopSignal(const QString& address);

    inline bool IsVideoWriterOnline(){
        this->_frameMutex.lock_shared();
        bool flag = this->_videoWriterStatus;
        this->_frameMutex.unlock_shared();
        return flag;
    }

    inline bool IsNeedScreenshot(){
        this->_frameMutex.lock_shared();
        bool flag = this->_screenshotStatus;
        this->_frameMutex.unlock_shared();
        return flag;
    }

    void MakeScreenShot();
private:

    std::shared_mutex _frameMutex;
    std::shared_mutex _videoWriterMutex;
    std::shared_mutex _screenshotMutex;
    cv::VideoCapture _videoStream;
    cv::VideoWriter _videoWriter;
    cv::Mat _currentFrame;

    bool _videoWriterStatus;
    bool _screenshotStatus;

    inline void SetVideoWriterState(bool state){
        this->_videoWriterMutex.lock();
        this->_videoWriterStatus = state;
        this->_videoWriterMutex.unlock();
    }

    inline void SetScreenshotState(bool state){
        this->_screenshotMutex.lock();
        this->_screenshotStatus = state;
        this->_screenshotMutex.unlock();
    }

    inline void SetMatrix(cv::Mat &&newFrame){
        this->_frameMutex.lock();
        this->_currentFrame = std::move(newFrame);
        this->_frameMutex.unlock();
    }
};


#endif
