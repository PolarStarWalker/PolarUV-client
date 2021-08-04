#ifndef ROBOT_SETTINGSSTRUCT_HPP
#define ROBOT_SETTINGSSTRUCT_HPP

#include <iostream>
#include <vector>

///ToDo: переделать в класс с функциями для изменения массива, а то вот так динамическая память может утечь
/// А ещё move semantics
class SettingsProtocol;

class RobotSettingsStruct {
public:
    RobotSettingsStruct();
    RobotSettingsStruct(RobotSettingsStruct &&robotSettingsStruct);
    RobotSettingsStruct(const RobotSettingsStruct &robotSettingsStruct);
    ~RobotSettingsStruct();

    void SetMoveCoefficientArray(const std::vector<double> &copyMoveArray);
    void SetHandCoefficientArray(const std::vector<double> &copyHandArray);
    std::vector<double> GetMoveCoefficientVector();
    std::vector<double> GetHandCoefficientVector();

private:
    double* MoveCoefficientArray = nullptr;
    double* HandCoefficientArray = nullptr;
public:
    int32_t MaxMotorSpeed = -1;
private:
    int8_t ThrustersNumber = -1;
    int8_t HandFreedom = -1;
public:
    int8_t MotorsProtocol = -1;

    friend std::ostream &operator<<(std::ostream &ostream, const RobotSettingsStruct &settingStruct);
    friend SettingsProtocol;
};

extern RobotSettingsStruct RobotSettingsStructData;
constexpr size_t RobotSettingsStructLen = sizeof(RobotSettingsStructData);

std::ostream &operator<<(std::ostream &ostream, const RobotSettingsStruct &robotSettingsStruct);


#endif
