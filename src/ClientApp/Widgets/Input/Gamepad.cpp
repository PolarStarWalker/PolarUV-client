#include <iostream>
#include "Gamepad.hpp"

using namespace control;

constexpr float cameraSpeed = 0.005;


inline XINPUT_STATE GetGamepadState(int id) {
    XINPUT_STATE state{};
    XInputGetState(id, &state);
    return state;
}

inline float GasFunction(double X) {
    if (X > 0) {
        return 0.278112 * X + 0.06916 * X * X + 0.648397 * X * X * X;
    } else {
        return 0.278112 * X - 0.06916 * X * X + 0.648397 * X * X * X;
    }
}


Gamepad::Gamepad(int id) {
    id_ = id;
    _cameraPosition = 0.15;
}

//ToDo: сделать геймпад
//lib::CommandsStruct Gamepad::GetCommandsStruct() const {
//    using namespace lib;
//
//    lib::CommandsStruct commands{};
//
//    int id = GetGamepadId();
//
//    XINPUT_STATE state{};
//    XInputGetState(id, &state);
//
//    commands.MoveVector[lib::Fx] = GasFunction(((double) state.Gamepad.sThumbRY) / STICK_AXES_TO_FLOAT);
//    commands.MoveVector[lib::Fy] = GasFunction(-((double) state.Gamepad.sThumbLX) / STICK_AXES_TO_FLOAT);
//    commands.MoveVector[lib::Fz] = GasFunction(((double) state.Gamepad.sThumbLY) / STICK_AXES_TO_FLOAT);
//    commands.MoveVector[lib::Mx] =
//            GasFunction(((GetAxisDirection(state.Gamepad.wButtons, LeftShoulder)) *
//                         ((double) state.Gamepad.bLeftTrigger) / SHOULDERS_TO_FLOAT));
//
//    commands.MoveVector[My] =
//            GasFunction(((GetAxisDirection(state.Gamepad.wButtons, RightShoulder)) *
//                         ((double) state.Gamepad.bRightTrigger) / SHOULDERS_TO_FLOAT));
//
//    commands.MoveVector[Mz] = GasFunction(-((double) state.Gamepad.sThumbRX) / STICK_AXES_TO_FLOAT);
//
//    if (state.Gamepad.wButtons & DPadLeft)
//        commands.TheHand[0] = -1;
//    else if (state.Gamepad.wButtons & DPadRight)
//        commands.TheHand[0] = 1;
//    else
//        commands.TheHand[0] = 0;
//
//    if (state.Gamepad.wButtons & DPadUp)
//        commands.TheHand[1] = 1;
//    else if (state.Gamepad.wButtons & DPadDown)
//        commands.TheHand[1] = -1;
//    else
//        commands.TheHand[1] = 0;
//
//    commands.MoveVector[Fx] = std::round(commands.MoveVector[Fx] * 1000) / 1000;
//    commands.MoveVector[Fy] = std::round(commands.MoveVector[Fy] * 1000) / 1000;
//    commands.MoveVector[Fz] = std::round(commands.MoveVector[Fz] * 1000) / 1000;
//    commands.MoveVector[Mx] = std::round(commands.MoveVector[Mx] * 1000) / 1000;
//    commands.MoveVector[My] = std::round(commands.MoveVector[My] * 1000) / 1000;
//    commands.MoveVector[Mz] = std::round(commands.MoveVector[Mz] * 1000) / 1000;
//
//    float cameraDirection = (state.Gamepad.wButtons & Cross) ? -1.0f : 0.0f +
//            ((state.Gamepad.wButtons & Triangle) ? 1.0f : 0.0f);
//
//    _cameraPosition += cameraDirection * cameraSpeed;
//
//    if (state.Gamepad.wButtons & RightStick)
//        _cameraPosition = 0.15;
//
//    if (_cameraPosition <= -1.0)
//        _cameraPosition = -1.0;
//    else if (_cameraPosition >= 0.05)
//        _cameraPosition = 0.05;
//
//    commands.LowPWM[0] = _cameraPosition;
//
//    return commands;
//}

void Gamepad::SetVibration(uint16_t left, uint16_t right) const {
    XINPUT_VIBRATION vibration;
    memset(&vibration, 0, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = left;
    vibration.wRightMotorSpeed = right;

    int id = id_.load();

    XInputSetState(id, &vibration);
}

void Gamepad::UpdateGamepadId(int id) {
    id_.exchange(id);
}


float GetAnalogValueByAxis(const XINPUT_STATE &state, GamepadSettingsStruct::AnalogAxis axis) {

    float value = 0.0f;

    //TODO REFACTOR ME PLS
    switch (axis.Axis) {
        case GamepadSettingsStruct::AnalogAxisEnum::LeftStickX: {
            value = ((float) state.Gamepad.sThumbLX) / STICK_AXES_TO_FLOAT;
            break;
        }
        case GamepadSettingsStruct::AnalogAxisEnum::LeftStickY: {
            value = ((float) state.Gamepad.sThumbLY) / STICK_AXES_TO_FLOAT;
            break;
        }
        case GamepadSettingsStruct::AnalogAxisEnum::RightStickX: {
            value = ((float) state.Gamepad.sThumbRX) / STICK_AXES_TO_FLOAT;
            break;
        }
        case GamepadSettingsStruct::AnalogAxisEnum::RightStickY: {
            value = ((float) state.Gamepad.sThumbRY) / STICK_AXES_TO_FLOAT;
            break;
        }
        case GamepadSettingsStruct::AnalogAxisEnum::LeftShoulder: {
            value = ((float) state.Gamepad.bLeftTrigger) / SHOULDERS_TO_FLOAT;
            break;
        }
        case GamepadSettingsStruct::AnalogAxisEnum::RightShoulder: {
            value = ((float) state.Gamepad.bRightTrigger) / SHOULDERS_TO_FLOAT;
            break;
        }
        case GamepadSettingsStruct::AnalogAxisEnum::DPadX: {
            if (state.Gamepad.wButtons & DPadRight)
                value = 1;
            else if (state.Gamepad.wButtons & DPadLeft)
                value = -1;
            break;
        }
        case GamepadSettingsStruct::AnalogAxisEnum::DPadY: {
            if (state.Gamepad.wButtons & DPadUp)
                value = 1;
            else if (state.Gamepad.wButtons & DPadDown)
                value = -1;
            break;
        }
        default: {
            throw std::exception();
        }
    }

    return axis.IsInverted ? -value : value;
}


CommandsStruct Gamepad::GetCommands(const GamepadSettingsStruct &settings) const {

    using AnalogActionEnum = GamepadSettingsStruct::AnalogActionEnum;
    using DiscreteActionsEnum = GamepadSettingsStruct::DiscreteActionEnum;
    using MoveEnum = CommandsStruct::MoveEnum;

    XINPUT_STATE state = GetGamepadState(id_.load());

    //ToDo: motov.s доделать
    CommandsStruct commands{};
    commands.Move[MoveEnum::Fx] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::MoveX]);
    commands.Move[MoveEnum::Fy] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::MoveY]);
    commands.Move[MoveEnum::Fz] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::MoveZ]);
    commands.Move[MoveEnum::Mx] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::RotateX]);
    commands.Move[MoveEnum::My] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::RotateY]);
    commands.Move[MoveEnum::Mz] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::RotateZ]);

    return commands;
}
