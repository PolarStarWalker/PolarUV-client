#include "./SettingsProtocol/RobotSettingsProtocol.hpp"

void RobotSettingsProtocol::Send(const QString &address, uint16_t port, RobotSettingsStruct &&robotSettingsStruct) {
    QTcpSocket _socket;
    _socket.connectToHost(address, port);
    bool connectionFlag = _socket.waitForConnected(1000);

    char direction = 'w';
    _socket.write(&direction, 1);
    _socket.waitForBytesWritten(1000);

    _socket.write(robotSettingsStruct.Begin(), robotSettingsStruct.Size());
    _socket.waitForBytesWritten(1000);
    _socket.disconnectFromHost();
}


void RobotSettingsProtocol::SendAsync(const QString &address, uint16_t port, RobotSettingsStruct &&settingsStruct) {
    if (!this->IsThreadActive()) {
        this->_transferThread = std::thread(&RobotSettingsProtocol::Send, this, address, port,
                                            std::move(settingsStruct));
        this->_transferThread.detach();
    }
}

RobotSettingsStruct RobotSettingsProtocol::Recv(const QString &address, uint16_t port) {
    QTcpSocket _socket;
    _socket.connectToHost(address, port);
    bool connectionFlag = _socket.waitForConnected(1000);

    char direction = 'r';
    _socket.write(&direction, 1);
    _socket.waitForBytesWritten(1000);
    ///ToDo: ConnectionException

    BaseRobotSettingsStruct baseRobotSettings{};

    if (_socket.bytesAvailable() < BaseRobotSettingsStructActualSize) {
        _socket.waitForReadyRead(500);
        ///ToDo: TimeOutException
    }

    _socket.read((char *) &baseRobotSettings, BaseRobotSettingsStructActualSize);

    RobotSettingsStruct tmpRobotSettings(baseRobotSettings);

    if (_socket.bytesAvailable() < tmpRobotSettings.Size() - BaseRobotSettingsStructActualSize) {
        _socket.waitForReadyRead(500);
        ///ToDo: TimeOutException
    }

    _socket.read(tmpRobotSettings.Begin() + BaseRobotSettingsStructActualSize,
                 tmpRobotSettings.Size() - BaseRobotSettingsStructActualSize);

    _socket.disconnectFromHost();

    return tmpRobotSettings;
}
