#ifndef CLIENT_CONTROLSSETTINGSSTRUCT_HPP
#define CLIENT_CONTROLSSETTINGSSTRUCT_HPP

enum AnalogControls : int8_t {
    LeftStickX,
    LeftStickY,
    RightStickX,
    RightStickY,
    LeftShoulder,
    RightShoulder,
    DPadX,
    DPadY
};

enum DiscreteControls : int8_t {
    LeftStick,
    RightStick,
    Square,
    Triangle,
    Circle,
    Cross,
    Start,
    Back
};

enum AnalogActions : int8_t {
    NoAnalogAction = 0,

    MoveX = 1,
    MoveY = 2,
    MoveZ = 3,
    RotateX = 4,
    RotateY = 5,
    RotateZ = 6,
    GrabHand = 7,
    RotateHand = 8,

    MoveXInverted = -1,
    MoveYInverted = -2,
    MoveZInverted = -3,
    RotateXInverted = -4,
    RotateYInverted = -5,
    RotateZInverted = -6,
    GrabHandInverted = -7,
    RotateHandInverted = -8
};

enum DiscreteActions : int8_t {
    NoDiscreteAction = 0,
    TurnOn = 1,
    TurnOff = 2
};

struct ControlsSettings {
    std::array<AnalogActions, 8> Analog;
    std::array<DiscreteActions, 8> Discrete;
};

#endif //CLIENT_CONTROLSSETTINGSSTRUCT_HPP
