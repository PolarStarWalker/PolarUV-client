#ifndef CLIENT_COMMANDSSTRUCT_HPP
#define CLIENT_COMMANDSSTRUCT_HPP

#include <DataStructs/StaticMap.hpp>

struct CommandsStruct {
    enum class MoveEnum : size_t {
        Fx = 0,
        Fy = 1,
        Fz = 2,
        Mx = 3,
        My = 4,
        Mz = 5
    };

    enum class HandEnum{
        Hand1,
        Hand2,
        Hand3,
        Hand4,
        Hand5,
        Hand6,
    };

    enum StabilizationType : int8_t {
        None = 0,
        Rotation = 1,
        Absolute = 2
    };

    using MoveArray_t = lib::StaticMap<MoveEnum, float, 6>;
    using HandArray_t = lib::StaticMap<HandEnum, float, 6>;

    MoveArray_t Move{};
    HandArray_t Hand{};
    std::array<float, 4> LowPWM{};

    StabilizationType Stabilization = None;
};

#endif
