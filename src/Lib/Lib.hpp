#ifndef CLIENT_LIB_HPP
#define CLIENT_LIB_HPP

#include "./TcpSession/TcpSession.hpp"
#include "./DataStructs/DataStructs.hpp"
#include "./Protocols/Protocols.hpp"
#include "./Exceptions/Exceptions.hpp"
#include "./Gamepad/Gamepad.hpp"
#include "./Coroutines/All.hpp"
#include "./Singleton.hpp"
#include "./Logger/Logger.hpp"


namespace lib {
    static void Setup() {
        logger::Setup();
        auto& startNetwork = network::TcpSession::GetInstance();

    }
}

#endif