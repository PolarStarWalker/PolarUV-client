#ifndef CLIENT_LIB_HPP
#define CLIENT_LIB_HPP

#include "./Network/Network.hpp"
#include "./Exceptions/Exceptions.hpp"
#include "./Coroutines/All.hpp"
#include "./Singleton.hpp"
#include "./Logger/Logger.hpp"
#include "./VideoStream/VideoStream.hpp"
#include "./DataStructs/DataStructs.hpp"
#include "./Drawer/Drawer.hpp"
#include "./Screenshotter/Screenshotter.hpp"
#include <gst/gst.h>

namespace lib {
    static void Setup() {
        SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
        logger::Setup();
        gst_init(nullptr, nullptr);
    }
}

#endif