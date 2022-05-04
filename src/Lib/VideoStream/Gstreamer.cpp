#include "Gstreamer.hpp"
#include <gst/gst.h>
#include <iostream>

Gstreamer::Gstreamer() :
        src(gst_element_factory_make("udpsrc", "src")),
        gdpdepay(gst_element_factory_make("gdpdepay", "gdp")),
        rtp(gst_element_factory_make("rtph264depay", "rtp")),
        h264parse(gst_element_factory_make("h264parse", "h264parse")),
        decode(gst_element_factory_make("d3d11h264dec", "decode")),
        videoconvert(gst_element_factory_make("videoconvert", "videoconvert")),
        sink(gst_element_factory_make("appsink", "sink")),
        group(gst_pipeline_new("group")),
        loop(nullptr) {}

Gstreamer::~Gstreamer() {
    gst_element_set_state(group, GST_STATE_NULL);
    gst_object_unref(group);
}

Gstreamer::operator bool() {
    return src && gdpdepay && rtp && h264parse && decode && videoconvert && sink && group;
}

void Gstreamer::Setup() {
    auto caps = gst_caps_new_simple("video/x-raw",
                                    "format", G_TYPE_STRING, "RGB",
                                    "width", G_TYPE_INT, 1920,
                                    "height", G_TYPE_INT, 1080,
                                    "framerate", GST_TYPE_FRACTION, 0, 1,
                                    nullptr);

    g_object_set(src, "port", 8000, nullptr);

    g_object_set(sink, "emit-signals", TRUE, "caps", src, nullptr);
    g_signal_connect (sink, "new-sample", G_CALLBACK(NewSampleCallback), this);

    g_signal_connect(sink, "eos", G_CALLBACK(EosCallback), this);

    gst_bin_add_many(GST_BIN (group), src, gdpdepay, rtp, h264parse, decode, videoconvert, sink, nullptr);

    gst_element_link_filtered(videoconvert, sink, caps);

    gst_caps_unref(caps);

    gst_element_link_many(src, gdpdepay, rtp, h264parse, decode, videoconvert, sink, nullptr);
}

void Gstreamer::Start() {
    auto bus = gst_element_get_bus(group);

    if(!loop)
        loop = g_main_loop_new(nullptr, FALSE);

    gst_bus_add_signal_watch(bus);
    g_signal_connect(G_OBJECT(bus), "message", G_CALLBACK(BusCallback), this);
    gst_object_unref(GST_OBJECT(bus));

    gst_element_set_state(group, GST_STATE_PLAYING);

    g_print("Starting loop\n");
    g_main_loop_run(loop);
}

void Gstreamer::Stop() {
    g_main_loop_quit(loop);
}

///***********Callbacks******************
gboolean Gstreamer::BusCallback(GstBus *bus, GstMessage *message, Gstreamer *stream) {
#if 0
    switch (GST_MESSAGE_TYPE (message)) {
        case GST_MESSAGE_ERROR: {
            GError *err = nullptr;
            gchar *name, *debug = nullptr;

            name = gst_object_get_path_string(message->src);
            gst_message_parse_error(message, &err, &debug);

            g_printerr("ERROR: from element %s: %s\n", name, err->message);
            if (debug != nullptr)
                g_printerr("Additional debug info:\n%s\n", debug);

            g_error_free(err);
            g_free(debug);
            g_free(name);

            g_main_loop_quit(stream->loop);
            gst_element_set_state(stream->group, GST_STATE_NULL);
            break;
        }
        case GST_MESSAGE_WARNING: {
            GError *err = nullptr;
            gchar *name, *debug = nullptr;

            name = gst_object_get_path_string(message->src);
            gst_message_parse_warning(message, &err, &debug);

            g_printerr("ERROR: from element %s: %s\n", name, err->message);
            if (debug != nullptr)
                g_printerr("Additional debug info:\n%s\n", debug);

            g_error_free(err);
            g_free(debug);
            g_free(name);
            break;
        }
        case GST_MESSAGE_EOS: {
            std::cout << "Got EOS" << std::endl;
            // g_main_loop_quit (loop);
            // gst_element_set_state (pipeline, GST_STATE_NULL);
            // g_main_loop_unref (loop);
            // gst_object_unref (pipeline);
            // exit(0);
            break;
        }
        case GST_MESSAGE_STEP_DONE: {
            std::cout << "step done" << std::endl;
            break;
        }
        case GST_MESSAGE_STREAM_STATUS: {

            GstStreamStatusType newstate;
            gchar *name;

            name = gst_object_get_path_string(message->src);
            gst_message_parse_stream_status(message, &newstate, &(stream->group));

            g_print("INFO: from element %s: %i\n", name, newstate);

            g_free(name);

            std::cout << "change status" << std::endl;
            break;
        }
        case GST_MESSAGE_SEGMENT_START : {
            std::cout << "segment start" << std::endl;
            break;
        }
        case GST_MESSAGE_SEGMENT_DONE  : {
            std::cout << "segment done" << std::endl;
            break;
        }
        case GST_MESSAGE_ELEMENT: {
            const GstStructure *s = gst_message_get_structure(message);

            if (gst_structure_has_name(s, "GstBinForwarded")) {
                GstMessage *forward_msg = nullptr;

                gst_structure_get(s, "message", GST_TYPE_MESSAGE, &forward_msg, nullptr);
                if (GST_MESSAGE_TYPE (forward_msg) == GST_MESSAGE_EOS) {
                    g_print("EOS from element %s\n", GST_OBJECT_NAME (GST_MESSAGE_SRC(forward_msg)));
                }
                gst_message_unref(forward_msg);
                break;
            }
        }
        default:
            break;
    }
#endif

    return TRUE;
}


GstFlowReturn Gstreamer::NewSampleCallback(GstElement *sink, Gstreamer *stream) {
    GstSample *sample;

    g_signal_emit_by_name(sink, "pull-sample", &sample);

    if (sample) {
        GstMapInfo buffInfo;
        auto buffer = gst_sample_get_buffer(sample);
        gst_buffer_map(buffer, &buffInfo, GST_MAP_READ);

        auto frameBufferPtr = reinterpret_cast<const uchar *>(buffInfo.data);

        {
            auto newFrame = QImage(frameBufferPtr, 1920, 1080, QImage::Format_RGB888);
            std::lock_guard guard(stream->qImageMutex_);
            stream->frame = newFrame;
        }

        gst_buffer_unmap(buffer, &buffInfo);
        gst_sample_unref(sample);

        auto now = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(now - stream->time).count()
                  << "[ms]" << std::endl;
        stream->time = now;

        return GST_FLOW_OK;
    }

    return GST_FLOW_ERROR;
}

GstFlowReturn Gstreamer::EosCallback(GstElement *appsink, Gstreamer *data) {

    std::cout << "EOS CALLBACK" << std::endl;

    return GST_FLOW_OK;
}

///************Init Gstreamer*************
extern "C" void InitGstreamer() {

    gst_init(nullptr, nullptr);

    GST_PLUGIN_STATIC_DECLARE(coreelements);
    GST_PLUGIN_STATIC_REGISTER(coreelements);

    GST_PLUGIN_STATIC_DECLARE(udp);
    GST_PLUGIN_STATIC_REGISTER(udp);

    GST_PLUGIN_STATIC_DECLARE(gdp);
    GST_PLUGIN_STATIC_REGISTER(gdp);

    GST_PLUGIN_STATIC_DECLARE(rtp);
    GST_PLUGIN_STATIC_REGISTER(rtp);

    GST_PLUGIN_STATIC_DECLARE(playback);
    GST_PLUGIN_STATIC_REGISTER(playback);

    GST_PLUGIN_STATIC_DECLARE(autoconvert);
    GST_PLUGIN_STATIC_REGISTER(autoconvert);

    GST_PLUGIN_STATIC_DECLARE(app);
    GST_PLUGIN_STATIC_REGISTER(app);

    /*delete*/
    GST_PLUGIN_STATIC_DECLARE(videotestsrc);
    GST_PLUGIN_STATIC_REGISTER(videotestsrc);

    GST_PLUGIN_STATIC_DECLARE(d3d11);
    GST_PLUGIN_STATIC_REGISTER(d3d11);

    GST_PLUGIN_STATIC_DECLARE(videoparsersbad);
    GST_PLUGIN_STATIC_REGISTER(videoparsersbad);

    GST_PLUGIN_STATIC_DECLARE(autodetect);
    GST_PLUGIN_STATIC_REGISTER(autodetect);

    GST_PLUGIN_STATIC_DECLARE(videoconvert);
    GST_PLUGIN_STATIC_REGISTER(videoconvert);
};