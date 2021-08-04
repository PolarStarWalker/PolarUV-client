#ifndef CLIENT_SETTINGSSTRUCT_HPP
#define CLIENT_SETTINGSSTRUCT_HPP

class SettingsProtocol;

enum RobotActions : int8_t {
    NoAction = 0,
    MoveX = 1,
    MoveY = 2,
    MoveZ = 3,
    RotateX = 4,
    RotateY = 5,
    RotateZ = 6,
    GrabHand = 7,
    RotateHand = 8,
    TurnOn = 9,
    TurnOff = 10
};

class ClientSettingsStruct {
public:
    ClientSettingsStruct();
    ~ClientSettingsStruct();

    friend SettingsProtocol;
};

#endif //CLIENT_SETTINGSSTRUCT_HPP
