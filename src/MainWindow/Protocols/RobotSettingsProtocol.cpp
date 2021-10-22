#include "./SettingsProtocol/RobotSettingsProtocol.hpp"

void RobotSettingsProtocol::Send(const QString &address, uint16_t port, RobotSettingsStruct &&robotSettingsStruct) {
    QTcpSocket _socket;
    _socket.connectToHost(address, port);
    if (!_socket.waitForConnected(50))
        throw Exception::ConnectionException("Не удалось подключиться к роботу");

    char direction = 'w';
    _socket.write(&direction, 1);
    if (!_socket.waitForBytesWritten(50))
        throw Exception::ConnectionException("Не удалось отправить настройки робота");

    _socket.write(robotSettingsStruct.Begin(), robotSettingsStruct.Size());
    if (!_socket.waitForBytesWritten(100))
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
    if (!socket.waitForConnected(50))
        throw Exception::ConnectionException("Не удалось подключиться к роботу");

    char direction = 'r';
    socket.write(&direction, 1);
    if (!socket.waitForBytesWritten(1000))
        throw Exception::ConnectionException("Не удалось отправить данные");

    BaseRobotSettingsStruct baseRobotSettings{};

    baseRobotSettings.HandFreedom = 2;
    baseRobotSettings.ThrusterNumber = 8;

    socket.read((char *) &baseRobotSettings, BaseRobotSettingsStructActualSize);
    if (socket.bytesAvailable() < BaseRobotSettingsStructActualSize)
        if (!socket.waitForReadyRead(500))
            throw Exception::ConnectionException("Не удалось считать данные");

    RobotSettingsStruct tmpRobotSettings(baseRobotSettings);

    socket.read(tmpRobotSettings.Begin() + BaseRobotSettingsStructActualSize,
                tmpRobotSettings.Size() - BaseRobotSettingsStructActualSize);

    if (socket.bytesAvailable() < (tmpRobotSettings.Size() - BaseRobotSettingsStructActualSize))
        if (!socket.waitForReadyRead(500))
            throw Exception::ConnectionException("Не удалось считать данные");


    socket.disconnectFromHost();

    return tmpRobotSettings;
}
