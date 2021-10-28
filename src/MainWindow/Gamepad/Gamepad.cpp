#include <iostream>
#include "Gamepad.hpp"

using namespace Control;

constexpr float  cameraSpeed = 0.005;


inline float GasFunction(double X) {
    if (X > 0) {
        return 0.278112 * X + 0.06916 * X * X + 0.648397 * X * X * X;
    } else {
        return 0.278112 * X - 0.06916 * X * X + 0.648397 * X * X * X;
    }
}


Gamepad::Gamepad(int id) {
    this->_id = id;
    _cameraPosition = 0.15;
}

CommandsStruct Gamepad::GetCommandsStruct() const {
    CommandsStruct commands{};

    _idMutex.lock_shared();
    int id = _id;
    _idMutex.unlock_shared();

    XINPUT_STATE state{};
    XInputGetState(id, &state);

    commands.MoveVector[Fx] = GasFunction(((double) state.Gamepad.sThumbRY) / MAGIC_NUMBER_ONE);
    commands.MoveVector[Fy] = GasFunction(-((double) state.Gamepad.sThumbLX) / MAGIC_NUMBER_ONE);
    commands.MoveVector[Fz] = GasFunction(((double) state.Gamepad.sThumbLY) / MAGIC_NUMBER_ONE);
    commands.MoveVector[Mx] =
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

    float cameraDirection = (state.Gamepad.wButtons & Cross) ? -1.0f : 0.0f + (state.Gamepad.wButtons & Triangle) ? 1.0f : 0.0f;

    _cameraPosition += cameraDirection * cameraSpeed;

    if(state.Gamepad.wButtons & RightStick)
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
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = left;
    vibration.wRightMotorSpeed = right;
    XInputSetState(_id, &vibration);
}

void Gamepad::UpdateGamepadId(size_t id) {
    _idMutex.lock();
    _id = id;
    _idMutex.unlock();
}

size_t Gamepad::GetGamepadId() const {

    _idMutex.lock_shared();
    int id = _id;
    _idMutex.unlock_shared();

    return id;
}



