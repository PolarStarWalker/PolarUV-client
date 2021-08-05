#ifndef CLIENT_SETTINGSSTRUCT_HPP
#define CLIENT_SETTINGSSTRUCT_HPP

#include <fstream>

enum RobotAnalogActions : int8_t {
    NoAnalogAction = 0,
    MoveX = 1,
    MoveY = 2,
    MoveZ = 3,
    RotateX = 4,
    RotateY = 5,
    RotateZ = 6,
    GrabHand = 7,
    RotateHand = 8,
};

enum RobotDiscreteActions : int8_t {
    NoDiscreteAction = 0,
    TurnOn = 1,
    TurnOff = 2
};

class ClientSettingsStruct {
public:
    ClientSettingsStruct();
    ~ClientSettingsStruct();

    void Save();
    void Load();

    int32_t dPadXActionID;
    int32_t dPadYActionID;
    int32_t leftStickXActionID;
    int32_t leftStickYActionID;
    int32_t rightStickXActionID;
    int32_t rightStickYActionID;
    int32_t leftShoulderActionID;
    int32_t rightShoulderActionID;

    int32_t leftStickPressActionID;
    int32_t rightStickPressActionID;
    int32_t triangleActionID;
    int32_t crossActionID;
    int32_t rectangleActionID;
    int32_t circleActionID;
    int32_t startActionID;
    int32_t backActionID;

    bool dPadXInverted;
    bool dPadYInverted;
    bool leftStickXInverted;
    bool leftStickYInverted;
    bool rightStickXInverted;
    bool rightStickYInverted;
    bool leftShoulderInverted;
    bool rightShoulderInverted;

    std::string serverIP;
    int32_t gamepadID;
};

extern ClientSettingsStruct ClientSettingsStructData;
constexpr size_t ClientSettingsStructLen = sizeof(ClientSettingsStructData);

#endif //CLIENT_SETTINGSSTRUCT_HPP
