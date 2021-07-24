#include <iostream>
#include "Gamepad.hpp"

Gamepad::Gamepad(size_t id) {
    this->_id = id;
}

Gamepad::~Gamepad() = default;

CommandsStruct *Gamepad::GetCommandsStruct() const {
    CommandsStruct *commands = new CommandsStruct{};

    XINPUT_STATE state{};
    std::memset(&state, 0, sizeof(state));
    XInputGetState(this->_id, &state);

    commands->VectorArray[Fx] = GasFunction(((double) state.Gamepad.sThumbRY) / MAGIC_NUMBER_ONE);
    commands->VectorArray[Fy] = GasFunction(((double) state.Gamepad.sThumbLX) / MAGIC_NUMBER_ONE);
    commands->VectorArray[Fz] = GasFunction(((double) state.Gamepad.sThumbLY) / MAGIC_NUMBER_ONE);
    commands->VectorArray[Mx] = GasFunction(((double) state.Gamepad.bLeftTrigger) / MAGIC_NUMBER_TWO);
    commands->VectorArray[My] = GasFunction(((double) state.Gamepad.bRightTrigger) / MAGIC_NUMBER_TWO);
    commands->VectorArray[Mz] = GasFunction(((double) state.Gamepad.sThumbRX) / MAGIC_NUMBER_ONE);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
        commands->TheHand[0] = -1;
    else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
        commands->TheHand[0] = 1;
    else
        commands->TheHand[0] = 0;

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
        commands->TheHand[1] = 1;
    else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
        commands->TheHand[1] = -1;
    else
        commands->TheHand[1] = 0;

    commands->VectorArray[Fx] = std::round(commands->VectorArray[Fx] * 1000) / 1000;
    commands->VectorArray[Fy] = std::round(commands->VectorArray[Fy] * 1000) / 1000;
    commands->VectorArray[Fz] = std::round(commands->VectorArray[Fz] * 1000) / 1000;
    commands->VectorArray[Mx] = std::round(commands->VectorArray[Mx] * 1000) / 1000;
    commands->VectorArray[My] = std::round(commands->VectorArray[My] * 1000) / 1000;
    commands->VectorArray[Mz] = std::round(commands->VectorArray[Mz] * 1000) / 1000;

    return commands;
}

void Gamepad::SetVibration(uint16_t left, uint16_t right) const {
    XINPUT_VIBRATION vibration;
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = left;
    vibration.wRightMotorSpeed = right;
    XInputSetState(this->_id, &vibration);
}

IDataStream::Stream Gamepad::GetStream() const {
    IDataStream::Stream stream;
    stream.Data = std::shared_ptr<void>(this->GetCommandsStruct());
    stream.Size = CommandsStructLen;
    return stream;
}

std::ostream &Gamepad::Print(IDataStream::Stream &stream) const {
    return operator<<(std::ostream(nullptr ), *((CommandsStruct *) stream.Data.get()));
}
