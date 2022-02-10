#ifndef CLIENT_LIB_HPP
#define CLIENT_LIB_HPP

#include "./Network/Network.hpp"
#include "./DataStructs/DataStructs.hpp"
#include "./Protocols/Protocols.hpp"
#include "./Exceptions/Exceptions.hpp"
#include "./Gamepad/Gamepad.hpp"
#include "./Coroutines/All.hpp"
#include "./Singleton.hpp"
#include "./Logger/Logger.hpp"
#include "./VideoStream/VideoStream.hpp"

namespace lib {
    static void Setup() {
        logger::Setup();
    }
}

#endif