#include "./RobotSettingsStruct/RobotSettingsStruct.hpp"

RobotSettingsStruct::RobotSettingsStruct() {
    this->HandFreedom = -1;
    this->HandCoefficientArray = nullptr;
    this->ThrustersNumber = -1;
    this->MoveCoefficientArray = nullptr;
    this->MaxMotorSpeed = -1;
    this->MotorsProtocol = -1;
}

RobotSettingsStruct::RobotSettingsStruct(RobotSettingsStruct &&robotSettingsStruct) {
    this->HandFreedom = robotSettingsStruct.HandFreedom;
    this->ThrustersNumber = robotSettingsStruct.ThrustersNumber;
    this->MotorsProtocol = robotSettingsStruct.MotorsProtocol;
    this->MaxMotorSpeed = robotSettingsStruct.MaxMotorSpeed;

    this->MoveCoefficientArray = robotSettingsStruct.MoveCoefficientArray;
    robotSettingsStruct.MoveCoefficientArray = nullptr;

    this->HandCoefficientArray = robotSettingsStruct.HandCoefficientArray;
    robotSettingsStruct.HandCoefficientArray = nullptr;
}

RobotSettingsStruct::RobotSettingsStruct(const RobotSettingsStruct &robotSettingsStruct) {
    this->HandFreedom = robotSettingsStruct.HandFreedom;
    this->ThrustersNumber = robotSettingsStruct.ThrustersNumber;
    this->MotorsProtocol = robotSettingsStruct.MotorsProtocol;
    this->MaxMotorSpeed = robotSettingsStruct.MaxMotorSpeed;

    this->MoveCoefficientArray = new double[6 * this->ThrustersNumber];
    for (size_t i = 0; i < 6 * this->ThrustersNumber; i++) {
        this->MoveCoefficientArray[i] = robotSettingsStruct.MoveCoefficientArray[i];
    }

    this->HandCoefficientArray = new double[this->HandFreedom];
    for (size_t i = 0; i < this->HandFreedom; i++) {
        this->HandCoefficientArray[i] = robotSettingsStruct.HandCoefficientArray[i];
    }
}

RobotSettingsStruct::~RobotSettingsStruct() {
    delete[] this->MoveCoefficientArray;
    delete[] this->HandCoefficientArray;
}

void RobotSettingsStruct::SetMoveCoefficientArray(const std::vector<double> &copyMoveArray) {
    delete MoveCoefficientArray;

    this->ThrustersNumber = copyMoveArray.size() / 6;
    this->MoveCoefficientArray = new double[copyMoveArray.size()];

    for (size_t i = 0; i < this->ThrustersNumber; i++) {
        for (size_t j = 0; j < 6; j++) {
            this->MoveCoefficientArray[i * 6 + j] = copyMoveArray[i * 6 + j];
        }
    };
}

void RobotSettingsStruct::SetHandCoefficientArray(const std::vector<double> &copyHandArray) {
    delete HandCoefficientArray;

    this->HandFreedom = copyHandArray.size();
    this->HandCoefficientArray = new double[this->HandFreedom];
    for (size_t i = 0; i < this->HandFreedom; i++) {
        this->HandCoefficientArray[i] = copyHandArray[i];
    }
}

std::ostream &operator<<(std::ostream &ostream, const RobotSettingsStruct &robotSettingStruct) {

    ostream << "ThrustersNumber: " << (int32_t) robotSettingStruct.ThrustersNumber << std::endl;

    ostream << "MoveCoefficientMatrix:" << std::endl;
    for (size_t i = 0; i < robotSettingStruct.ThrustersNumber; i++) {
        ostream << "[ ";
        for (size_t j = 0; j < 5; j++) {
            ostream << robotSettingStruct.MoveCoefficientArray[6 * i + j] << ", ";
        }
        ostream << robotSettingStruct.MoveCoefficientArray[6 * i + 5] << "]" << std::endl;
    }

    ostream << "HandFreedom: " << (ssize_t) robotSettingStruct.HandFreedom << std::endl;
    ostream << "HandCoefficientArray: [";
    for (size_t i = 0; i < robotSettingStruct.HandFreedom - 1; i++) {
        ostream << robotSettingStruct.HandCoefficientArray[i] << ", ";
    }
    ostream << robotSettingStruct.HandCoefficientArray[robotSettingStruct.HandFreedom - 1] << "]" << std::endl;

    ostream << "MotorProtocol: ";
    switch (robotSettingStruct.MotorsProtocol) {
        case 1:
            std::cout << "DShot150";
            break;
        case 2:
            std::cout << "DShot300";
            break;
        case 4:
            std::cout << "DShot600";
            break;
        case 8:
            std::cout << "DShot1200";
            break;
    }
    ostream << std::endl;

    ostream << "MaxMotorSpeed: " << robotSettingStruct.MaxMotorSpeed << std::endl;

    return ostream;
}

const double *RobotSettingsStruct::GetMoveCoefficientArray() {
    return this->MoveCoefficientArray;
}

int8_t RobotSettingsStruct::GetThrusterNumber() {
    return this->ThrustersNumber;
}

const double *RobotSettingsStruct::GetHandCoefficientArray() {
    return this->HandCoefficientArray;
}

int8_t RobotSettingsStruct::GetHandFreedom() {
    return this->HandFreedom;
}


