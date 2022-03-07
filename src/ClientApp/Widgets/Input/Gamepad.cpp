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

    float value;

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
        case GamepadSettingsStruct::AnalogAxisEnum::LeftTrigger: {
            value = ((float) state.Gamepad.bLeftTrigger) / SHOULDERS_TO_FLOAT;
            value = state.Gamepad.wButtons & LeftShoulder ? -value : value;
            break;
        }
        case GamepadSettingsStruct::AnalogAxisEnum::RightTrigger: {
            value = ((float) state.Gamepad.bRightTrigger) / SHOULDERS_TO_FLOAT;
            value = state.Gamepad.wButtons & RightShoulder ? -value : value;
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
        case GamepadSettingsStruct::AnalogAxisEnum::NoButton:{
            value = 0;
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
    using HandEnum = CommandsStruct::HandEnum;

    XINPUT_STATE state = GetGamepadState(id_.load());

    //ToDo: motov.s доделать
    CommandsStruct commands{};
    commands.Move[MoveEnum::Fx] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::MoveX]);
    commands.Move[MoveEnum::Fy] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::MoveY]);
    commands.Move[MoveEnum::Fz] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::MoveZ]);
    commands.Move[MoveEnum::Mx] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::RotateX]);
    commands.Move[MoveEnum::My] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::RotateY]);
    commands.Move[MoveEnum::Mz] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::RotateZ]);

    commands.Hand[HandEnum::Hand1] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::Hand1]);
    commands.Hand[HandEnum::Hand2] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::Hand2]);
    commands.Hand[HandEnum::Hand3] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::Hand3]);
    commands.Hand[HandEnum::Hand4] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::Hand4]);
    commands.Hand[HandEnum::Hand5] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::Hand5]);
    commands.Hand[HandEnum::Hand6] = GetAnalogValueByAxis(state, settings.AnalogActionsIds[AnalogActionEnum::Hand6]);

    return commands;
}
