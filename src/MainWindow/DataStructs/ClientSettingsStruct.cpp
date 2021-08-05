#include "./ClientSettingsStruct/ClientSettingsStruct.hpp"

ClientSettingsStruct::ClientSettingsStruct() {
    this->dPadXActionID = -1;
    this->dPadYActionID = -1;
    this->leftStickXActionID = -1;
    this->leftStickYActionID = -1;
    this->rightStickXActionID = -1;
    this->rightStickYActionID = -1;
    this->leftShoulderActionID = -1;
    this->rightShoulderActionID = -1;

    this->leftStickPressActionID = -1;
    this->rightStickPressActionID = -1;
    this->triangleActionID = -1;
    this->crossActionID = -1;
    this->rectangleActionID = -1;
    this->circleActionID = -1;
    this->startActionID = -1;
    this->backActionID = -1;

    this->dPadXInverted = false;
    this->dPadYInverted = false;
    this->leftStickXInverted = false;
    this->leftStickYInverted = false;
    this->rightStickXInverted = false;
    this->rightStickYInverted = false;
    this->leftShoulderInverted = false;
    this->rightShoulderInverted = false;

    this->serverIP = "";
    this->gamepadID = -1;
}

ClientSettingsStruct::~ClientSettingsStruct() {

}

void ClientSettingsStruct::Save() {
    std::ofstream file("../settings", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
    file.write((char *) this, ClientSettingsStructLen);
    file.close();
}

void ClientSettingsStruct::Load() {
       std::ifstream file("../settings", std::ios_base::in | std::ios_base::binary);
    file.read((char*) this, ClientSettingsStructLen);
    file.close();

/*
    this->leftShoulderActionID = settings->leftShoulderActionID;
    this->rightShoulderActionID = settings->rightShoulderActionID;
    this->leftStickXActionID = settings->leftStickXActionID;
    this->leftStickYActionID = settings->leftStickYActionID;
    this->leftStickPressActionID = settings->leftStickPressActionID;
    this->rightStickXActionID = settings->rightStickXActionID;
    this->rightStickYActionID = settings->rightStickYActionID;
    this->rightStickPressActionID = settings->rightStickPressActionID;
    this->dPadXActionID = settings->dPadXActionID;
    this->dPadYActionID = settings->dPadYActionID;
    this->triangleActionID = settings->triangleActionID;
    this->crossActionID = settings->crossActionID;
    this->rectangleActionID = settings->rectangleActionID;
    this->circleActionID = settings->circleActionID;
    this->startActionID = settings->startActionID;
    this->backActionID = settings->backActionID;*/
}


