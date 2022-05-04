#ifndef CLIENT_GSTREAMER_HPP
#define CLIENT_GSTREAMER_HPP

#include <gst/gstelement.h>
#include <gst/gstpad.h>

#include <QImage>
#include <mutex>
#include <chrono>

class Gstreamer {
private:
    GstElement *src;
    GstElement *gdpdepay;
    GstElement *rtp;
    GstElement *h264parse;
    GstElement *decode;
    GstElement *videoconvert;
    GstElement *sink;
    GstElement *group;
    GMainLoop *loop;
    std::chrono::steady_clock::time_point time;

    std::mutex qImageMutex_;

    QImage frame;

public:
    Gstreamer();

    ~Gstreamer();

    void Setup();

    void Start();

    operator bool();

    void Stop();

    inline QImage GetQImage() {
        std::unique_lock lock(qImageMutex_);
        return std::move(frame);
    }

private:
    static GstFlowReturn NewSampleCallback(GstElement *sink, Gstreamer *stream);

    static gboolean BusCallback(GstBus *bus, GstMessage *message, Gstreamer *user_data);

    static GstFlowReturn EosCallback(GstElement * appsink, Gstreamer *data);
};

extern "C" {
void InitGstreamer();
}

#endif
