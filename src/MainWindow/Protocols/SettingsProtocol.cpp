#include "./SettingsProtocol/SettingsProtocol.hpp"

void SettingsProtocol::Send(const QString &address, uint16_t port, RobotSettingsStruct &&robotSettingsStruct) {
    uint32_t position = 0;

    position += sizeof(robotSettingsStruct.ThrustersNumber);
    position += robotSettingsStruct.ThrustersNumber * 6 * sizeof(double);
    position += sizeof(robotSettingsStruct.HandFreedom);
    position += robotSettingsStruct.HandFreedom * sizeof(double);
    position += sizeof(robotSettingsStruct.MaxMotorSpeed);
    position += sizeof(robotSettingsStruct.MotorsProtocol);

    QString message(position, 0);

    position = 0;

    std::memcpy(message.data() + position, &robotSettingsStruct.ThrustersNumber,
                sizeof(robotSettingsStruct.ThrustersNumber));
    position += sizeof(robotSettingsStruct.ThrustersNumber);

    std::memcpy(message.data() + position, robotSettingsStruct.MoveCoefficientArray,
                robotSettingsStruct.ThrustersNumber * 6 * sizeof(double));
    position += robotSettingsStruct.ThrustersNumber * 6 * sizeof(double);

    std::memcpy(message.data() + position, &robotSettingsStruct.HandFreedom,
                sizeof(robotSettingsStruct.HandFreedom));
    position += sizeof(robotSettingsStruct.HandFreedom);

    std::memcpy(message.data() + position, robotSettingsStruct.HandCoefficientArray,
                robotSettingsStruct.HandFreedom * sizeof(double));
    position += robotSettingsStruct.HandFreedom * sizeof(double);

    std::memcpy(message.data() + position, &robotSettingsStruct.MaxMotorSpeed, sizeof(robotSettingsStruct.MaxMotorSpeed));
    position += sizeof(robotSettingsStruct.MaxMotorSpeed);

    std::memcpy(message.data() + position, &robotSettingsStruct.MotorsProtocol, sizeof(robotSettingsStruct.MotorsProtocol));
    position += sizeof(robotSettingsStruct.MotorsProtocol);

    std::cout << position << std::endl;
}

void SettingsProtocol::SendAsync(const QString &address, uint16_t port, RobotSettingsStruct &&settingsStruct) {
    if (!this->IsThreadActive()) {
        this->_transferThread = std::thread(&SettingsProtocol::Send, this, address, port, std::move(settingsStruct));
        this->_transferThread.detach();
    }

}
