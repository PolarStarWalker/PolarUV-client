#include <iostream>
#include "Gamepad.hpp"

using namespace Control;

constexpr float cameraSpeed = 0.005;


inline float GasFunction(double X) {
    if (X > 0) {
        return 0.278112 * X + 0.06916 * X * X + 0.648397 * X * X * X;
    } else {
        return 0.278112 * X - 0.06916 * X * X + 0.648397 * X * X * X;
    }
}


Gamepad::Gamepad(int id) {
    _id = id;
    _cameraPosition = 0.15;
}

lib::CommandsStruct Gamepad::GetCommandsStruct() const {
    using namespace lib;

    lib::CommandsStruct commands{};

    int id = GetGamepadId();

    XINPUT_STATE state{};
    XInputGetState(id, &state);

    commands.MoveVector[lib::Fx] = GasFunction(((double) state.Gamepad.sThumbRY) / MAGIC_NUMBER_ONE);
    commands.MoveVector[lib::Fy] = GasFunction(-((double) state.Gamepad.sThumbLX) / MAGIC_NUMBER_ONE);
    commands.MoveVector[lib::Fz] = GasFunction(((double) state.Gamepad.sThumbLY) / MAGIC_NUMBER_ONE);
    commands.MoveVector[lib::Mx] =
            GasFunction(((GetAxisDirection(state.Gamepad.wButtons, LeftShoulder)) *
                         ((double) state.Gamepad.bLeftTrigger) / MAGIC_NUMBER_TWO));

    commands.MoveVector[My] =
            GasFunction(((GetAxisDirection(state.Gamepad.wButtons, RightShoulder)) *
                         ((double) state.Gamepad.bRightTrigger) / MAGIC_NUMBER_TWO));

    commands.MoveVector[Mz] = GasFunction(-((double) state.Gamepad.sThumbRX) / MAGIC_NUMBER_ONE);

    if (state.Gamepad.wButtons & DPadLeft)
        commands.TheHand[0] = -1;
    else if (state.Gamepad.wButtons & DPadRight)
        commands.TheHand[0] = 1;
    else
        commands.TheHand[0] = 0;

    if (state.Gamepad.wButtons & DPadUp)
        commands.TheHand[1] = 1;
    else if (state.Gamepad.wButtons & DPadDown)
        commands.TheHand[1] = -1;
    else
        commands.TheHand[1] = 0;

    commands.MoveVector[Fx] = std::round(commands.MoveVector[Fx] * 1000) / 1000;
    commands.MoveVector[Fy] = std::round(commands.MoveVector[Fy] * 1000) / 1000;
    commands.MoveVector[Fz] = std::round(commands.MoveVector[Fz] * 1000) / 1000;
    commands.MoveVector[Mx] = std::round(commands.MoveVector[Mx] * 1000) / 1000;
    commands.MoveVector[My] = std::round(commands.MoveVector[My] * 1000) / 1000;
    commands.MoveVector[Mz] = std::round(commands.MoveVector[Mz] * 1000) / 1000;

    float cameraDirection = (state.Gamepad.wButtons & Cross) ? -1.0f : 0.0f +
            ((state.Gamepad.wButtons & Triangle) ? 1.0f : 0.0f);

    _cameraPosition += cameraDirection * cameraSpeed;

    if (state.Gamepad.wButtons & RightStick)
        _cameraPosition = 0.15;

    if (_cameraPosition <= -1.0)
        _cameraPosition = -1.0;
    else if (_cameraPosition >= 0.05)
        _cameraPosition = 0.05;

    commands.LowPWM[0] = _cameraPosition;

    return commands;
}

void Gamepad::SetVibration(uint16_t left, uint16_t right) const {
    XINPUT_VIBRATION vibration;
    memset(&vibration, 0, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = left;
    vibration.wRightMotorSpeed = right;

    int id = GetGamepadId();

    XInputSetState(id, &vibration);
}

void Gamepad::UpdateGamepadId(size_t id) {
    _id = id;
}

int Gamepad::GetGamepadId() const {
    return _id;
}



