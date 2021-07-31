#include "DataStruct.hpp"

std::ostream &operator<<(std::ostream &s, const CommandsStruct &commandsStruct) {
    s << "VectorArray: ["
      << commandsStruct.VectorArray[0] << ", "
      << commandsStruct.VectorArray[1] << ", "
      << commandsStruct.VectorArray[2] << ", "
      << commandsStruct.VectorArray[3] << ", "
      << commandsStruct.VectorArray[4] << ", "
      << commandsStruct.VectorArray[5] << "]"
      << "\n"

      << "The Hand: ["
      << commandsStruct.TheHand[0] << ", "
      << commandsStruct.TheHand[1] << "]"
      << "\n"

      << "Camera: ["
      << commandsStruct.Camera[0] << ", "
      << commandsStruct.Camera[1] << "]"
      << "\n"

      << "MotorsLock: "
      << commandsStruct.MotorsLock << "\n"

      << "Stabilization: "
      << commandsStruct.Stabilization << std::endl;

    return s;
}

std::ostream &operator<<(std::ostream &s, const MotorsStruct &motorsStruct) {
    s << "MotorsCommand: ["
      << motorsStruct.PacketArray[0] << ", "
      << motorsStruct.PacketArray[1] << ", "
      << motorsStruct.PacketArray[2] << ", "
      << motorsStruct.PacketArray[3] << ", "
      << motorsStruct.PacketArray[4] << ", "
      << motorsStruct.PacketArray[5] << ", "
      << motorsStruct.PacketArray[6] << ", "
      << motorsStruct.PacketArray[7] << ", "
      << motorsStruct.PacketArray[8] << ", "
      << motorsStruct.PacketArray[9] << ", "
      << motorsStruct.PacketArray[10] << ", "
      << motorsStruct.PacketArray[11] << "]"
      << std::endl

      << "Time Prescaler: ["
      << motorsStruct.TimerPrescaler << "]"
      << std::endl;

    return s;
}

std::ostream &operator<<(std::ostream &ostream, const SettingsStruct &settingsStruct) {

    ostream << "ThrusterNumber: " << settingsStruct.ThrustersNumber << std::endl;

    ostream << "MoveCoefficientMatrix:" << std::endl;
    for (size_t i = 0; i < settingsStruct.ThrustersNumber; i++) {
        ostream << "[ ";
        for (size_t j = 0; j < 5; j++) {
            ostream << settingsStruct.MoveCoefficientArray[6 * i + j] << ", ";
        }
        ostream << settingsStruct.MoveCoefficientArray[6 * i + 6] << "]" << std::endl;
    }

    ostream << "HandFreedom: " << (ssize_t) settingsStruct.HandFreedom << std::endl;
    ostream << "HandCoefficientArray: [";
    for (size_t i = 0; i < settingsStruct.HandFreedom - 1; i++) {
        ostream << settingsStruct.HandCoefficientArray[i] << ", ";
    }
    ostream << settingsStruct.HandCoefficientArray[settingsStruct.HandFreedom - 1] << ", ]" << std::endl;

    std::cout << "MotorProtocol: " << (long) settingsStruct.MotorsProtocol << std::endl;
    std::cout << "MaxMotorSpeed: " << settingsStruct.MaxMotorSpeed << std::endl;

    return ostream;
}