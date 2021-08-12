#ifndef ROBOT_ROBOTSETTINGSSTRUCT_HPP
#define ROBOT_ROBOTSETTINGSSTRUCT_HPP

#include <iostream>
#include <vector>
#include <cstring>

///ToDo: переделать в класс с функциями для изменения массива, а то вот так динамическая память может утечь
/// А ещё move semantics

namespace {
    enum Offset : size_t{
        MotorsProtocolOffset = 0,
        MaxMotorSpeedOffset = 2,
        ThrusterNumberOffset = 4,
        HandFreedomOffset = 6,
        ArraysOffset = 8
    };
}

class RobotSettingsStruct {
public:
    RobotSettingsStruct(const std::vector<double> &copyMoveArray, const std::vector<double> &copyHandArray);
    explicit RobotSettingsStruct(size_t thrustersNumber, size_t handFreedom);
    RobotSettingsStruct(RobotSettingsStruct &&robotSettingsStruct);
    RobotSettingsStruct(const RobotSettingsStruct &robotSettingsStruct);
    ~RobotSettingsStruct();

    RobotSettingsStruct& operator=(const RobotSettingsStruct& robotSettingsStruct) noexcept;
    RobotSettingsStruct& operator=(RobotSettingsStruct&& robotSettingsStruct) noexcept;

    char* Begin();
    char* End();

    size_t Size();

    const double *const GetThrusterCoefficientArray();
    int16_t ThrusterNumber();

    const double *const GetHandCoefficientArray();
    int16_t HandFreedom();

    int16_t & MaxMotorsSpeed();
    int16_t & MotorsProtocol();

    friend std::ostream &operator<<(std::ostream &ostream, const RobotSettingsStruct &settingStruct);

private:
    char* _data;
    size_t _handArrayOffset;
    size_t _length;
};

std::ostream &operator<<(std::ostream &ostream, const RobotSettingsStruct &robotSettingsStruct);

#endif
