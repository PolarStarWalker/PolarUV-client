#include <iostream>
#include "Gamepad.hpp"

Gamepad::Gamepad(size_t id) {
    this->_id = id;
}

Gamepad::~Gamepad() = default;

CommandsStruct Gamepad::GetCommandsStruct() const {
    CommandsStruct commands;

    XINPUT_STATE state{};
    std::memset(&state, 0, sizeof(state));
    XInputGetState(this->_id, &state);

    //ToDo: привести к double через функцию газа;
    commands.VectorArray[Fx] = ((double) state.Gamepad.sThumbRY) / MAGIC_NUMBER_ONE;
    commands.VectorArray[Fy] = ((double) state.Gamepad.sThumbLX) / MAGIC_NUMBER_ONE;
    commands.VectorArray[Fz] = ((double) state.Gamepad.sThumbLY) / MAGIC_NUMBER_ONE;
    commands.VectorArray[Mx] = ((double) state.Gamepad.bLeftTrigger) / MAGIC_NUMBER_TWO;
    commands.VectorArray[My] = ((double) state.Gamepad.bRightTrigger) / MAGIC_NUMBER_TWO;
    commands.VectorArray[Mz] = ((double) state.Gamepad.sThumbRX) / MAGIC_NUMBER_ONE;

    commands.TheHand[0] = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT
                          ||
                          state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;

    commands.TheHand[0] = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP
                          ||
                          state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;

    return commands;
}

void Gamepad::SetVibration(uint16_t left, uint16_t right) const {
    XINPUT_VIBRATION vibration;
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = left;
    vibration.wRightMotorSpeed = right;
    XInputSetState(this->_id, &vibration);
}
