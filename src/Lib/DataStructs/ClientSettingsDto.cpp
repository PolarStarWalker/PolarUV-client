#include "./ClientSettings/ClientSettingsDto.hpp"
#include "ClientSettingsMessage.pb.h"

#include <fstream>
#include <cstring>

using namespace data_structs;

ClientSettingsDto::ClientSettingsDto() {

    std::memset(this->ServerIP, 0, sizeof(this->ServerIP));
    this->GamepadID = -1;

    this->DPadXAction = RotateHand;
    this->DPadYAction = GrabHand;

    this->LeftStickXAction = MoveY;
    this->LeftStickYAction = MoveZ;
    this->RightStickXAction = RotateZ;
    this->RightStickYAction = MoveX;

    this->LeftShoulderAction = RotateX;
    this->RightShoulderAction = RotateY;

    this->LeftStickPressAction = NoDiscreteAction;
    this->RightStickPressAction = NoDiscreteAction;
    this->TriangleAction = NoDiscreteAction;
    this->CrossAction = NoDiscreteAction;
    this->SquareAction = NoDiscreteAction;
    this->CircleAction = NoDiscreteAction;

    this->StartAction = TurnOn;
    this->BackAction = TurnOff;

    this->dPadXInverted = false;
    this->dPadYInverted = false;
    this->LeftStickXInverted = false;
    this->LeftStickYInverted = false;
    this->RightStickXInverted = false;
    this->RightStickYInverted = false;
    this->LeftShoulderInverted = false;
    this->RightShoulderInverted = false;

}

ClientSettingsDto::~ClientSettingsDto() = default;

void ClientSettingsDto::Save() const {

    using DiscreteActions = ClientSettingsMessage::RobotDiscreteActions;
    using AnalogActions = ClientSettingsMessage::RobotAnalogActions;

    ClientSettingsMessage message;

    message.set_server_ip(ServerIP);
    message.set_gamepad_id(GamepadID);

    message.set_dpad_x_action((AnalogActions) DPadXAction);
    message.set_dpad_y_action((AnalogActions) DPadYAction);

    message.set_left_stick_x_action((AnalogActions) LeftStickXAction);
    message.set_left_stick_y_action((AnalogActions) LeftStickYAction);
    message.set_right_stick_x_action((AnalogActions) RightStickXAction);
    message.set_right_stick_y_action((AnalogActions) RightStickYAction);
    message.set_left_shoulder_action((AnalogActions) LeftShoulderAction);
    message.set_right_shoulder_action((AnalogActions) RightShoulderAction);

    message.set_triangle_action((DiscreteActions) TriangleAction);
    message.set_circle_action((DiscreteActions) CircleAction);
    message.set_cross_action((DiscreteActions) CrossAction);
    message.set_square_action((DiscreteActions) SquareAction);
    message.set_start_action((DiscreteActions) StartAction);
    message.set_back_action((DiscreteActions) BackAction);

    message.set_dpad_x_inverted(dPadXInverted);
    message.set_dpad_y_inverted(dPadYInverted);

    message.set_left_stick_x_inverted(LeftStickXInverted);
    message.set_left_stick_y_inverted(LeftStickYInverted);
    message.set_right_stick_x_inverted(RightStickXInverted);
    message.set_right_stick_y_inverted(RightStickYInverted);
    message.set_left_shoulder_inverted(LeftShoulderInverted);
    message.set_right_shoulder_inverted(RightShoulderInverted);

    std::ofstream file("settings", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
    message.SerializeToOstream(&file);
    file.close();
}

ClientSettingsDto ClientSettingsDto::Load() {

    std::ifstream file("settings", std::ios_base::in | std::ios_base::binary);
    ClientSettingsMessage message;
    message.ParseFromIstream(&file);
    file.close();

    ClientSettingsDto settings;

    std::memcpy(settings.ServerIP, message.server_ip().c_str(), sizeof(ServerIP));
    settings.GamepadID = message.gamepad_id();

    settings.DPadXAction = message.dpad_x_action();
    settings.DPadYAction = message.dpad_y_action();

    settings.LeftStickXAction = message.left_stick_x_action();
    settings.LeftStickYAction = message.left_stick_y_action();
    settings.RightStickXAction = message.right_stick_x_action();
    settings.RightStickYAction = message.right_stick_y_action();
    settings.LeftShoulderAction = message.left_shoulder_action();
    settings.RightShoulderAction = message.right_shoulder_action();

    settings.TriangleAction = message.triangle_action();
    settings.CircleAction = message.circle_action();
    settings.CrossAction = message.cross_action();
    settings.SquareAction = message.square_action();
    settings.StartAction = message.start_action();
    settings.BackAction = message.back_action();

    settings.dPadXInverted = message.dpad_x_inverted();
    settings.dPadYInverted = message.dpad_y_inverted();

    settings.LeftStickXInverted = message.left_stick_x_inverted();
    settings.LeftStickYInverted = message.left_stick_y_inverted();
    settings.RightStickXInverted = message.right_stick_x_inverted();
    settings.RightStickYInverted = message.right_stick_y_inverted();
    settings.LeftShoulderInverted = message.left_shoulder_inverted();
    settings.RightShoulderInverted = message.right_shoulder_inverted();

    return settings;
}


