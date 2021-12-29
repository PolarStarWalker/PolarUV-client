#include "./RobotSettings/RobotSettingsDto.hpp"
#include "./RobotSettingsMessage.pb.h"

int foo(){
    RobotSettingsMessage robotSettingsMessage;
    google::protobuf::RepeatedField<float> bar = robotSettingsMessage.thrusters_coefficient();

    return 0;
}

RobotSettingsDto::RobotSettingsDto() {
    this->_size = BaseRobotSettingsDtoAllocatedSize + 7 * sizeof(float);

    this->_data = new char[this->_size]{};

    ((BaseRobotSettingsDto *) this->_data)->MotorsProtocol = DShotMode::DShot150;
    ((BaseRobotSettingsDto *) this->_data)->MaxMotorSpeed = 1000;
    ((BaseRobotSettingsDto *) this->_data)->ThrusterNumber = 1;
    ((BaseRobotSettingsDto *) this->_data)->HandFreedom = 1;

    this->_thrusterCoefficientArrayPtr = (float *) (this->_data + BaseRobotSettingsDtoAllocatedSize);
    this->_handCoefficientArrayPtr = this->_thrusterCoefficientArrayPtr + 6;
}

RobotSettingsDto::RobotSettingsDto(const BaseRobotSettingsDto &robotStatic) {
    size_t handFreedom = robotStatic.HandFreedom == 0 ? 1 : robotStatic.HandFreedom;
    size_t thrusterNumber = robotStatic.ThrusterNumber == 0 ? 1 : robotStatic.ThrusterNumber;

    this->_size = BaseRobotSettingsDtoAllocatedSize +
                  thrusterNumber * 6 * sizeof(float) +
                  handFreedom * sizeof(float);

    this->_data = new char[this->_size]{};

    ((BaseRobotSettingsDto *) this->_data)->MotorsProtocol = robotStatic.MotorsProtocol;
    ((BaseRobotSettingsDto *) this->_data)->MaxMotorSpeed = robotStatic.MaxMotorSpeed;
    ((BaseRobotSettingsDto *) this->_data)->ThrusterNumber = thrusterNumber;
    ((BaseRobotSettingsDto *) this->_data)->HandFreedom = handFreedom;

    this->_thrusterCoefficientArrayPtr = (float *) (this->_data + BaseRobotSettingsDtoAllocatedSize);
    this->_handCoefficientArrayPtr = _thrusterCoefficientArrayPtr + robotStatic.ThrusterNumber * 6;
}

RobotSettingsDto::RobotSettingsDto(const RobotSettingsDto &robotSettingsStruct) {
    this->_size = robotSettingsStruct._size;
    this->_data = new char[this->_size];

    for (size_t i = 0; i < this->_size / 8; i++)
        ((uint64_t *) this->_data)[i] = ((uint64_t *) robotSettingsStruct._data)[i];

    size_t deltaThrusterCoefficientArray =
            robotSettingsStruct._thrusterCoefficientArrayPtr - (float *) robotSettingsStruct._data;
    this->_thrusterCoefficientArrayPtr = ((float *) this->_data) + deltaThrusterCoefficientArray;

    size_t deltaHandCoefficientArray =
            robotSettingsStruct._thrusterCoefficientArrayPtr - (float *) robotSettingsStruct._data;

    this->_thrusterCoefficientArrayPtr = _thrusterCoefficientArrayPtr + deltaHandCoefficientArray;
}

RobotSettingsDto::RobotSettingsDto(RobotSettingsDto &&robotSettingsStruct) noexcept {
    this->_size = robotSettingsStruct._size;
    this->_data = robotSettingsStruct._data;
    this->_thrusterCoefficientArrayPtr = robotSettingsStruct._thrusterCoefficientArrayPtr;
    this->_handCoefficientArrayPtr = robotSettingsStruct._handCoefficientArrayPtr;
    robotSettingsStruct._data = nullptr;
}


RobotSettingsDto::~RobotSettingsDto() {
    delete[] this->_data;
}

RobotSettingsDto &RobotSettingsDto::operator=(const RobotSettingsDto &robotSettingsStruct) noexcept {
    
    if(this == &robotSettingsStruct)
        return *this;
    
    delete[] this->_data;

    this->_size = robotSettingsStruct._size;
    this->_data = new char[this->_size];

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

RobotSettingsDto &RobotSettingsDto::operator=(RobotSettingsDto &&robotSettingsStruct) noexcept {
    delete[] this->_data;

    this->_size = robotSettingsStruct._size;
    this->_data = robotSettingsStruct._data;
    this->_thrusterCoefficientArrayPtr = robotSettingsStruct._thrusterCoefficientArrayPtr;
    this->_handCoefficientArrayPtr = robotSettingsStruct._handCoefficientArrayPtr;
    robotSettingsStruct._data = nullptr;

    return *this;
}


char *RobotSettingsDto::Begin() {
    return this->_data;
}

char *RobotSettingsDto::End() {
    return this->_data + this->_size;
}

size_t RobotSettingsDto::Size() const{
    return this->_size;
}

float *RobotSettingsDto::ThrusterCoefficientArray() {
    return this->_thrusterCoefficientArrayPtr;
}

float *RobotSettingsDto::HandCoefficientArray() {
    return this->_handCoefficientArrayPtr;
}

uint16_t RobotSettingsDto::ThrusterNumber() {
    return ((BaseRobotSettingsDto *) this->_data)->ThrusterNumber;
}

uint16_t RobotSettingsDto::HandFreedom() {
    return ((BaseRobotSettingsDto *) this->_data)->HandFreedom;
}

uint16_t &RobotSettingsDto::MaxMotorsSpeed() {
    return ((BaseRobotSettingsDto *) this->_data)->MaxMotorSpeed;
}

DShotMode &RobotSettingsDto::MotorsProtocol() {
    return ((BaseRobotSettingsDto *) this->_data)->MotorsProtocol;
}

std::ostream &operator<<(std::ostream &ostream, const RobotSettingsDto &robotSettingsDto) {

    ostream << "[RobotSettingsDto]" << std::endl;

    uint16_t thrusterNumber = ((BaseRobotSettingsDto *) robotSettingsDto._data)->ThrusterNumber;
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

    uint16_t handFreedom = ((BaseRobotSettingsDto *) robotSettingsDto._data)->HandFreedom;
    ostream << "HandFreedom: " << handFreedom << std::endl;

    float *handArray = robotSettingsDto._handCoefficientArrayPtr;
    ostream << "HandCoefficientArray: [";
    for (size_t i = 0; i < handFreedom - 1; i++) {
        ostream << handArray[i] << ", ";
    }
    ostream << handArray[handFreedom - 1] << "]" << std::endl;

    uint16_t motorsProtocol = ((BaseRobotSettingsDto *) robotSettingsDto._data)->MotorsProtocol;
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

    uint16_t maxMotorSpeed = ((BaseRobotSettingsDto *) robotSettingsDto._data)->MaxMotorSpeed;
    ostream << "MaxMotorSpeed: " << maxMotorSpeed << std::endl;

    return ostream;
}

