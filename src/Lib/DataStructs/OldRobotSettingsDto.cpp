#include "./RobotSettings/OldRobotSettingsDto.hpp"
#include "./RobotSettingsMessage.pb.h"

using namespace data_structs;

int foo(){
    RobotSettingsMessage robotSettingsMessage;
    const google::protobuf::RepeatedField<float>& bar = robotSettingsMessage.thrusters_coefficient();

    return 0;
}

OldRobotSettingsDto::OldRobotSettingsDto() {
    this->_size = BaseRobotSettingsDtoAllocatedSize + 7 * sizeof(float);

    this->_data = new std::byte[this->_size]{};

    ((BaseRobotSettingsDto *) this->_data)->MotorsProtocol = DShotMode::DShot150;
    ((BaseRobotSettingsDto *) this->_data)->MaxMotorSpeed = 1000;
    ((BaseRobotSettingsDto *) this->_data)->ThrusterNumber = 1;
    ((BaseRobotSettingsDto *) this->_data)->HandFreedom = 1;

    this->_thrusterCoefficientArrayPtr = (float *) (this->_data + BaseRobotSettingsDtoAllocatedSize);
    this->_handCoefficientArrayPtr = this->_thrusterCoefficientArrayPtr + 6;
}

OldRobotSettingsDto::OldRobotSettingsDto(const BaseRobotSettingsDto &robotStatic) {
    size_t handFreedom = robotStatic.HandFreedom == 0 ? 1 : robotStatic.HandFreedom;
    size_t thrusterNumber = robotStatic.ThrusterNumber == 0 ? 1 : robotStatic.ThrusterNumber;

    this->_size = BaseRobotSettingsDtoAllocatedSize +
                  thrusterNumber * 6 * sizeof(float) +
                  handFreedom * sizeof(float);

    this->_data = new std::byte[this->_size]{};

    ((BaseRobotSettingsDto *) this->_data)->MotorsProtocol = robotStatic.MotorsProtocol;
    ((BaseRobotSettingsDto *) this->_data)->MaxMotorSpeed = robotStatic.MaxMotorSpeed;
    ((BaseRobotSettingsDto *) this->_data)->ThrusterNumber = thrusterNumber;
    ((BaseRobotSettingsDto *) this->_data)->HandFreedom = handFreedom;

    this->_thrusterCoefficientArrayPtr = (float *) (this->_data + BaseRobotSettingsDtoAllocatedSize);
    this->_handCoefficientArrayPtr = _thrusterCoefficientArrayPtr + robotStatic.ThrusterNumber * 6;
}

OldRobotSettingsDto::OldRobotSettingsDto(const OldRobotSettingsDto &robotSettingsStruct) {
    this->_size = robotSettingsStruct._size;
    this->_data = new std::byte[this->_size];

    for (size_t i = 0; i < this->_size / 8; i++)
        ((uint64_t *) this->_data)[i] = ((uint64_t *) robotSettingsStruct._data)[i];

    size_t deltaThrusterCoefficientArray =
            robotSettingsStruct._thrusterCoefficientArrayPtr - (float *) robotSettingsStruct._data;
    this->_thrusterCoefficientArrayPtr = ((float *) this->_data) + deltaThrusterCoefficientArray;

    size_t deltaHandCoefficientArray =
            robotSettingsStruct._thrusterCoefficientArrayPtr - (float *) robotSettingsStruct._data;

    this->_thrusterCoefficientArrayPtr = _thrusterCoefficientArrayPtr + deltaHandCoefficientArray;
}

OldRobotSettingsDto::OldRobotSettingsDto(OldRobotSettingsDto &&robotSettingsStruct) noexcept {
    this->_size = robotSettingsStruct._size;
    this->_data = robotSettingsStruct._data;
    this->_thrusterCoefficientArrayPtr = robotSettingsStruct._thrusterCoefficientArrayPtr;
    this->_handCoefficientArrayPtr = robotSettingsStruct._handCoefficientArrayPtr;
    robotSettingsStruct._data = nullptr;
}


OldRobotSettingsDto::~OldRobotSettingsDto() {
    delete[] this->_data;
}

OldRobotSettingsDto &OldRobotSettingsDto::operator=(const OldRobotSettingsDto &robotSettingsStruct) noexcept {
    
    if(this == &robotSettingsStruct)
        return *this;
    
    delete[] this->_data;

    this->_size = robotSettingsStruct._size;
    this->_data = new std::byte[this->_size];

    for (size_t i = 0; i < this->_size / 8; i++)
        ((uint64_t *) this->_data)[i] = ((uint64_t *) robotSettingsStruct._data)[i];

    size_t deltaThrusterCoefficientArray =
            robotSettingsStruct._thrusterCoefficientArrayPtr - (float *) robotSettingsStruct._data;
    this->_thrusterCoefficientArrayPtr = ((float *) this->_data) + deltaThrusterCoefficientArray;

    size_t deltaHandCoefficientArray =
            robotSettingsStruct._thrusterCoefficientArrayPtr - (float *) robotSettingsStruct._data;

    this->_thrusterCoefficientArrayPtr = _thrusterCoefficientArrayPtr + deltaHandCoefficientArray;

    return *this;
}

OldRobotSettingsDto &OldRobotSettingsDto::operator=(OldRobotSettingsDto &&robotSettingsStruct) noexcept {
    delete[] this->_data;

    this->_size = robotSettingsStruct._size;
    this->_data = robotSettingsStruct._data;
    this->_thrusterCoefficientArrayPtr = robotSettingsStruct._thrusterCoefficientArrayPtr;
    this->_handCoefficientArrayPtr = robotSettingsStruct._handCoefficientArrayPtr;
    robotSettingsStruct._data = nullptr;

    return *this;
}


char *OldRobotSettingsDto::Begin() {
    return (char*) this->_data;
}

char *OldRobotSettingsDto::End() {
    return (char*) this->_data + this->_size;
}

size_t OldRobotSettingsDto::Size() const{
    return this->_size;
}

float *OldRobotSettingsDto::ThrusterCoefficientArray() {
    return this->_thrusterCoefficientArrayPtr;
}

float *OldRobotSettingsDto::HandCoefficientArray() {
    return this->_handCoefficientArrayPtr;
}

uint16_t OldRobotSettingsDto::ThrusterNumber() {
    return ((BaseRobotSettingsDto *) this->_data)->ThrusterNumber;
}

uint16_t OldRobotSettingsDto::HandFreedom() {
    return ((BaseRobotSettingsDto *) this->_data)->HandFreedom;
}

uint16_t &OldRobotSettingsDto::MaxMotorsSpeed() {
    return ((BaseRobotSettingsDto *) this->_data)->MaxMotorSpeed;
}

DShotMode &OldRobotSettingsDto::MotorsProtocol() {
    return ((BaseRobotSettingsDto *) this->_data)->MotorsProtocol;
}

std::ostream& data_structs::operator<<(std::ostream &ostream, const data_structs::OldRobotSettingsDto &robotSettingsDto){

    const BaseRobotSettingsDto& baseRobotSettings = *((BaseRobotSettingsDto *) robotSettingsDto._data);

    ostream << "[OldRobotSettingsDto]" << std::endl;

    uint16_t thrusterNumber = baseRobotSettings.ThrusterNumber;
    ostream << "ThrustersNumber: " << thrusterNumber << std::endl;

    float *thrusterCoefficientArray = robotSettingsDto._thrusterCoefficientArrayPtr;
    ostream << "MoveCoefficientMatrix:" << std::endl;
    for (size_t i = 0; i < thrusterNumber; i++) {
        ostream << "[ ";
        for (size_t j = 0; j < 5; j++) {
            ostream << thrusterCoefficientArray[6 * i + j] << ", ";
        }
        ostream << thrusterCoefficientArray[6 * i + 5] << "]" << std::endl;
    }

    uint16_t handFreedom = baseRobotSettings.HandFreedom;
    ostream << "HandFreedom: " << handFreedom << std::endl;

    float *handArray = robotSettingsDto._handCoefficientArrayPtr;
    ostream << "HandCoefficientArray: [";
    for (size_t i = 0; i < handFreedom - 1; i++) {
        ostream << handArray[i] << ", ";
    }
    ostream << handArray[handFreedom - 1] << "]" << std::endl;

    uint16_t motorsProtocol = baseRobotSettings.MotorsProtocol;
    ostream << "MotorProtocol: ";
    switch (motorsProtocol) {
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
        default:
            std::cout << "Undefined type";
    }
    ostream << std::endl;

    uint16_t maxMotorSpeed = baseRobotSettings.MaxMotorSpeed;
    ostream << "MaxMotorSpeed: " << maxMotorSpeed << std::endl;

    return ostream;
}

