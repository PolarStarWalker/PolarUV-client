#ifndef ROBOT_ROBOTSETTINGSSTRUCT_HPP
#define ROBOT_ROBOTSETTINGSSTRUCT_HPP

#include <iostream>
#include <cstring>
#include <cmath>

#include <vector>
#include <array>

namespace data_structs {

#include "../MotorsStruct/MotorsStruct.hpp"

    struct [[deprecated("switch to protobuf struct")]] BaseRobotSettingsDto {
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

    class [[deprecated("switch to protobuf struct")]] OldRobotSettingsDto {
    public:

        OldRobotSettingsDto();

        explicit OldRobotSettingsDto(const BaseRobotSettingsDto &robotStatic);

        OldRobotSettingsDto(const OldRobotSettingsDto &robotSettingsStruct);

        OldRobotSettingsDto(OldRobotSettingsDto &&robotSettingsStruct) noexcept;

        ~OldRobotSettingsDto();

        OldRobotSettingsDto &operator=(const OldRobotSettingsDto &robotSettingsStruct) noexcept;

        OldRobotSettingsDto &operator=(OldRobotSettingsDto &&robotSettingsStruct) noexcept;

        char *Begin();

        char *End();

        size_t Size() const;

        float *ThrusterCoefficientArray();

        uint16_t ThrusterNumber();

        float *HandCoefficientArray();

        uint16_t HandFreedom();

        uint16_t &MaxMotorsSpeed();

        DShotMode &MotorsProtocol();

    protected:
        size_t _size;

        float *_handCoefficientArrayPtr;
        float *_thrusterCoefficientArrayPtr;

        friend std::ostream &operator<<(std::ostream &ostream, const OldRobotSettingsDto &robotSettingsDto);

        std::byte *_data;
    };

    std::ostream &operator<<(std::ostream &ostream, const OldRobotSettingsDto &robotSettingsDto);


    class RobotSettingsDto{
    public:

        RobotSettingsDto(): _thrusterMatrix(12 * 6){}

        friend std::ostream &operator<<(std::ostream& ostream, const RobotSettingsDto& robotSettingsDto);


        void SetThrusterMatrix(const std::vector<float>& matrix){
            _thrusterMatrix.resize(matrix.size());
            std::copy(matrix.begin(), matrix.end(), _thrusterMatrix.begin());
        }

    private:

        std::vector<float> _thrusterMatrix;
        std::vector<float> _handArray;
    };

    std::ostream &operator<<(std::ostream& ostream, const RobotSettingsDto& robotSettingsDto);
};

#endif
