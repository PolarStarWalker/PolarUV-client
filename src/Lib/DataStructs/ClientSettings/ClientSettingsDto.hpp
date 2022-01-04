#ifndef CLIENT_SETTINGSSTRUCT_HPP
#define CLIENT_SETTINGSSTRUCT_HPP

namespace data_structs {

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

    struct ClientSettingsDto {
        ClientSettingsDto();

        ~ClientSettingsDto();

        void Save() const;

        static ClientSettingsDto Load();

        int32_t GamepadID;
        char ServerIP[16];

        int8_t dPadXAction;
        int8_t dPadYAction;
        int8_t LeftStickXAction;
        int8_t LeftStickYAction;
        int8_t RightStickXAction;
        int8_t RightStickYAction;
        int8_t LeftShoulderAction;
        int8_t RightShoulderAction;

        int8_t LeftStickPressAction;
        int8_t RightStickPressAction;

        int8_t SquareAction;
        int8_t TriangleAction;
        int8_t CircleAction;
        int8_t CrossAction;

        int8_t StartAction;
        int8_t BackAction;

        bool dPadXInverted;
        bool dPadYInverted;

        bool LeftStickXInverted;
        bool LeftStickYInverted;
        bool RightStickXInverted;
        bool RightStickYInverted;
        bool LeftShoulderInverted;
        bool RightShoulderInverted;
    };

    extern ClientSettingsDto ClientSettingsStructData;
    constexpr size_t ClientSettingsStructLen = sizeof(ClientSettingsStructData);
}
#endif
