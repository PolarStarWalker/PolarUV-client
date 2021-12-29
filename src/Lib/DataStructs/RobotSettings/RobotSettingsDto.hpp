#ifndef ROBOT_ROBOTSETTINGSSTRUCT_HPP
#define ROBOT_ROBOTSETTINGSSTRUCT_HPP

#include <iostream>
#include <cstring>
#include <cmath>
#include "../MotorsStruct/MotorsStruct.hpp"

struct BaseRobotSettingsDto {
    DShotMode MotorsProtocol;
    uint16_t MaxMotorSpeed;
    uint16_t ThrusterNumber;
    uint16_t HandFreedom;
};
///Find real size of BaseRobotSettingsDto
constexpr size_t BaseRobotSettingsDtoActualSize = sizeof(BaseRobotSettingsDto);
///Find how many bytes to allocate given eight byte alignment
const size_t BaseRobotSettingsDtoAllocatedSize =
        (std::ceil(((double) sizeof(BaseRobotSettingsDto)) / sizeof(double))) * sizeof(double);

class RobotSettingsDto {
public:

    RobotSettingsDto();

    explicit RobotSettingsDto(const BaseRobotSettingsDto &robotStatic);

    RobotSettingsDto(const RobotSettingsDto &robotSettingsStruct);

    RobotSettingsDto(RobotSettingsDto &&robotSettingsStruct) noexcept;

    ~RobotSettingsDto();

    RobotSettingsDto &operator=(const RobotSettingsDto &robotSettingsStruct) noexcept;

    RobotSettingsDto &operator=(RobotSettingsDto &&robotSettingsStruct) noexcept;

    char *Begin();

    char *End();

    size_t Size() const;

    float *ThrusterCoefficientArray();

    uint16_t ThrusterNumber();

    float *HandCoefficientArray();

    uint16_t HandFreedom();

    uint16_t &MaxMotorsSpeed();

    DShotMode &MotorsProtocol();

private:
    char *_data;
    size_t _size;

    float *_handCoefficientArrayPtr;
    float *_thrusterCoefficientArrayPtr;

    friend std::ostream &operator<<(std::ostream &ostream, const RobotSettingsDto &robotSettingsStruct);
};

std::ostream &operator<<(std::ostream &ostream, const RobotSettingsDto &robotSettingsDto);

#endif
