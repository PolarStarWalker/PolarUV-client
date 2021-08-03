#include "./SettingsProtocol/SettingsProtocol.hpp"

void SettingsProtocol::Send(const QString &address, uint16_t port, SettingsStruct &&settingsStruct) {
    uint32_t position = 0;

    position += sizeof(settingsStruct.ThrustersNumber);
    position += settingsStruct.ThrustersNumber * 6 * sizeof(double);
    position += sizeof(settingsStruct.HandFreedom);
    position += settingsStruct.HandFreedom * sizeof(double);
    position += sizeof(settingsStruct.MaxMotorSpeed);
    position += sizeof(settingsStruct.MotorsProtocol);

    QString message(position, 0);

    position = 0;

    std::memcpy(message.data() + position, &settingsStruct.ThrustersNumber,
                sizeof(settingsStruct.ThrustersNumber));
    position += sizeof(settingsStruct.ThrustersNumber);

    std::memcpy(message.data() + position, settingsStruct.MoveCoefficientArray,
                settingsStruct.ThrustersNumber * 6 * sizeof(double));
    position += settingsStruct.ThrustersNumber * 6 * sizeof(double);

    std::memcpy(message.data() + position, &settingsStruct.HandFreedom,
                sizeof(settingsStruct.HandFreedom));
    position += sizeof(settingsStruct.HandFreedom);

    std::memcpy(message.data() + position, settingsStruct.HandCoefficientArray,
                settingsStruct.HandFreedom * sizeof(double));
    position += settingsStruct.HandFreedom * sizeof(double);

    std::memcpy(message.data() + position, &settingsStruct.MaxMotorSpeed, sizeof(settingsStruct.MaxMotorSpeed));
    position += sizeof(settingsStruct.MaxMotorSpeed);

    std::memcpy(message.data() + position, &settingsStruct.MotorsProtocol, sizeof(settingsStruct.MotorsProtocol));
    position += sizeof(settingsStruct.MotorsProtocol);

    std::cout << position << std::endl;
}

void SettingsProtocol::SendAsync(const QString &address, uint16_t port, SettingsStruct &&settingsStruct) {
    if (!this->IsThreadActive()) {
        this->_transferThread = std::thread(&SettingsProtocol::Send, this, address, port, std::move(settingsStruct));
        this->_transferThread.detach();
    }

}
