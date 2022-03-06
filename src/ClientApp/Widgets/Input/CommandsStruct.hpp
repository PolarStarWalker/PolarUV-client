#ifndef CLIENT_COMMANDSSTRUCT_HPP
#define CLIENT_COMMANDSSTRUCT_HPP

#include <array>

struct CommandsStruct {
    enum MoveEnum : size_t {
        Fx = 0,
        Fy = 1,
        Fz = 2,
        Mx = 3,
        My = 4,
        Mz = 5
    };

    enum StabilizationType : int8_t {
        None = 0,
        Rotation = 1,
        Absolute = 2
    };

    std::array<float, 6> Move{};
    std::array<float, 6> Hand{};
    std::array<float, 4> LowPWM{};

    StabilizationType Stabilization = None;
};

//    auto response = resources_.Network.SendRequest(commands, lib::network::Request::TypeEnum::W, 3);
#endif
