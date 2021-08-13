#include "./SettingsProtocol/RobotSettingsProtocol.hpp"


void RobotSettingsProtocol::Send(const QString &address, uint16_t port, RobotSettingsStruct &&robotSettingsStruct) {
    QTcpSocket _socket;
    _socket.connectToHost(address, port);
    _socket.waitForConnected(1000);

    char direction = 'w';
    _socket.write(&direction, 1);
    _socket.waitForBytesWritten(1000);

    _socket.write(robotSettingsStruct.Begin(), robotSettingsStruct.Size());
    _socket.waitForBytesWritten(1000);
}


void RobotSettingsProtocol::SendAsync(const QString &address, uint16_t port, RobotSettingsStruct &&settingsStruct) {
    if (!this->IsThreadActive()) {
        this->_transferThread = std::thread(&RobotSettingsProtocol::Send, this, address, port,
                                            std::move(settingsStruct));
        this->_transferThread.detach();
    }
}

void RobotSettingsProtocol::Recv(const QString &address, uint16_t port, RobotSettingsStruct &robotSettingsStruct) {
    QTcpSocket _socket;
    _socket.connectToHost(address, port);
    _socket.waitForConnected(1000);

    char direction = 'r';
    _socket.write(&direction, 1);
    _socket.waitForBytesWritten(1000);

    int16_t robotStatic[ArraysOffset / 2]{};
    _socket.read((char *) robotStatic, 8);
    _socket.waitForBytesWritten(1000);

    RobotSettingsStruct tmpRobotSettings(robotStatic[2], robotStatic[3]);
    *((int64_t *) (tmpRobotSettings.Begin())) = *((int64_t *) robotStatic);

    char *arrays = tmpRobotSettings.Begin() + ArraysOffset;
    _socket.read(arrays, robotStatic[2] * 6 * sizeof(double) + robotStatic[3] * sizeof(double));

    robotSettingsStruct = std::move(tmpRobotSettings);
}
