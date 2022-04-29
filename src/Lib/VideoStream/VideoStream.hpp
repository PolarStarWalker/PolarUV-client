#ifndef CLIENT_VIDEOSTREAM_HPP
#define CLIENT_VIDEOSTREAM_HPP

#include <shared_mutex>
#include <thread>
#include <QImage>
#include <opencv2/videoio.hpp>

#include <gst/gstelement.h>
#include <gst/gstbus.h>
#include <gst/gstmessage.h>
#include <gst/gstpipeline.h>
#include <gst/gstutils.h>

namespace lib::processing {

    struct PipelineData {
        GstElement *source;
        GstElement *gdpdepay;
        GstElement *rtpdepay;
        GstElement *decode;
        GstElement *videoconvert;
        GstElement *sink;

    private:
        GstElement *pipeline;

    public:
        PipelineData() : source(gst_element_factory_make("udpsrc", "udpsrc")),
                         gdpdepay(gst_element_factory_make("gdpdepay", "gdpdepay")),
                         rtpdepay(gst_element_factory_make("rtph264depay", "rtph264depay")),
                         decode(gst_element_factory_make("decodebin", "decodebin")),
                         videoconvert(gst_element_factory_make("videoconvert", "videoconvert")),
                         sink(gst_element_factory_make("autovideosink", "autovideosink")),
                         pipeline(gst_pipeline_new("rtp-stream")) {
            gst_bin_add_many (GST_BIN (pipeline), source, gdpdepay, rtpdepay, decode, videoconvert,  sink, nullptr);
        }

        ~PipelineData() {
            gst_element_set_state (pipeline, GST_STATE_NULL);
            gst_object_unref (pipeline);
        }

    };

    class VideoStream {
    public:

        VideoStream();

        ~VideoStream();

        void RestartClient();

        static std::string GetStartMessage(const std::string &clientIp);

        static std::string GetStopMessage();

        QImage GetQImage() {
            std::unique_lock lock(qImageMutex_);
            QImage pixmap = qImage_;
            qImage_ = QImage();
            return pixmap;
        }

        bool IsOnline() {
            return isOnline_.load();
        }

    private:
        void StartClient();

        std::thread thread_;
        cv::VideoCapture capture_;
        std::shared_mutex qImageMutex_;
        QImage qImage_;

        std::atomic<bool> isOnline_;
        std::atomic<bool> isListen_;
        std::atomic<bool> isDone_;


        PipelineData pipeline_;
//
//        GstBus *bus;
//        GstMessage *msg;

        void SetQImage(const cv::Mat &frame);
    };

}


#endif
