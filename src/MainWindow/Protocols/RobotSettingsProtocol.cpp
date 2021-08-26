#include "./SettingsProtocol/RobotSettingsProtocol.hpp"

void RobotSettingsProtocol::Send(const QString &address, uint16_t port, RobotSettingsStruct &&robotSettingsStruct) {
    QTcpSocket _socket;
    _socket.connectToHost(address, port);
    if(!_socket.waitForConnected(1000))
        throw Exception::ConnectionException("Не удалось подключиться к роботу");

    char direction = 'w';
    _socket.write(&direction, 1);
    if(!_socket.waitForBytesWritten(1000))
        throw Exception::ConnectionException("Не удалось отправить настройки робота");

    _socket.write(robotSettingsStruct.Begin(), robotSettingsStruct.Size());
    if(!_socket.waitForBytesWritten(1000))
        throw Exception::ConnectionException("Не удалось отправить настройки робота");

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
    QTcpSocket socket;
    socket.connectToHost(address, port);
    bool connectionFlag = socket.waitForConnected(1000);

    char direction = 'r';
    socket.write(&direction, 1);
    socket.waitForBytesWritten(1000);
    ///ToDo: ConnectionException

    BaseRobotSettingsStruct baseRobotSettings{};

    if (socket.bytesAvailable() < BaseRobotSettingsStructActualSize) {
        socket.waitForReadyRead(500);
        ///ToDo: TimeOutException
    }

    socket.read((char *) &baseRobotSettings, BaseRobotSettingsStructActualSize);

    RobotSettingsStruct tmpRobotSettings(baseRobotSettings);

    if (socket.bytesAvailable() < tmpRobotSettings.Size() - BaseRobotSettingsStructActualSize) {
        socket.waitForReadyRead(500);
        ///ToDo: TimeOutException
    }

    socket.read(tmpRobotSettings.Begin() + BaseRobotSettingsStructActualSize,
                 tmpRobotSettings.Size() - BaseRobotSettingsStructActualSize);

    socket.disconnectFromHost();

    return tmpRobotSettings;
}
