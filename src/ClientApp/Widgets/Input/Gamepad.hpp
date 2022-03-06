#ifndef CLIENT_GAMEPAD_HPP
#define CLIENT_GAMEPAD_HPP

#include "CommandsStruct.hpp"
#include "GamepadSettingsStruct.hpp"

#include <memory>
#include <cstring>
#include <cmath>
#include <list>
#include <shared_mutex>
#include <atomic>
#include <vector>

#include <xinput.h>
#include <minwindef.h>
#include <windows.h>

constexpr uint16_t STICK_AXES_TO_FLOAT = 0x7FFF;
constexpr uint16_t SHOULDERS_TO_FLOAT = 0x00FF;

namespace control {

    enum ButtonMask : DWORD {
        DPadUp = XINPUT_GAMEPAD_DPAD_UP,
        DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
        DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
        DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
        Start = XINPUT_GAMEPAD_START,
        Stop = XINPUT_GAMEPAD_BACK,
        LeftStick = XINPUT_GAMEPAD_LEFT_THUMB,
        RightStick = XINPUT_GAMEPAD_RIGHT_THUMB,
        LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
        RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
        Cross = XINPUT_GAMEPAD_A,
        Circle = XINPUT_GAMEPAD_B,
        Rectangle = XINPUT_GAMEPAD_X,
        Triangle = XINPUT_GAMEPAD_Y
    };

    inline int16_t GetAxisDirection(DWORD buttons, ButtonMask mask) {
        return buttons & mask ? -1 : 1;
    }

    class Gamepad {
    public:
        explicit Gamepad(int id);

        void SetVibration(uint16_t left, uint16_t right) const;

        void UpdateGamepadId(int id);

        CommandsStruct GetCommands(const GamepadSettingsStruct& settings) const;

    private:
        std::atomic<int> id_;
        mutable float _cameraPosition;
    };

    inline std::vector<int> GetGamepadsIds() {
        std::vector<int> ids;
        ids.reserve(XUSER_MAX_COUNT);

        XINPUT_STATE state{};
        for (int i = 0; i < XUSER_MAX_COUNT; i++) {
            DWORD gamepadState = XInputGetState(i, &state);
            if (gamepadState == NO_ERROR)
                ids.push_back(i);
        }

        return ids;
    };
}

#endif
