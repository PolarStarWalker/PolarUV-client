#ifndef CLIENT_LIB_HPP
#define CLIENT_LIB_HPP

#include "./Network/Network.hpp"
#include "./Exceptions/Exceptions.hpp"
#include "./Coroutines/All.hpp"
#include "./Singleton.hpp"
#include "./Logger/Logger.hpp"
#include "./VideoStream/VideoStream.hpp"
#include "./DataStructs/DataStructs.hpp"

namespace lib {
    static void Setup() {
        logger::Setup();
    }
}

#endif