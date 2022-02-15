#ifndef CLIENT_GAMEPAD_HPP
#define CLIENT_GAMEPAD_HPP

#include "CommandsWidget.hpp"

#include <memory>
#include <cstring>
#include <cmath>
#include <list>
#include <shared_mutex>
#include <atomic>

#include <xinput.h>
#include <minwindef.h>
#include <windows.h>

#define MAGIC_NUMBER_ONE 0x7FFF
#define MAGIC_NUMBER_TWO 0xFF

namespace Control {

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

        //lib::CommandsStruct GetCommandsStruct() const;

        void SetVibration(uint16_t left, uint16_t right) const;

        void UpdateGamepadId(size_t id);

        int GetGamepadId() const;

    private:
        std::atomic<int> _id;
        mutable float _cameraPosition;
    };

    inline std::list<int> GetGamepadsIds() {
        std::list<int> ids;
        XINPUT_STATE state{};
        for (int i = 0; i < XUSER_MAX_COUNT; i++) {
            DWORD gamepadState = XInputGetState(i, &state);
            if (gamepadState == ERROR_SUCCESS)
                ids.push_back(i);
        }
        return ids;
    };
}

#endif
