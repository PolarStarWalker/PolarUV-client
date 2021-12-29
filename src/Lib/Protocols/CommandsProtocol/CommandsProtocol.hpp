#ifndef CLIENT_COMMANDSPROTOCOL_HPP
#define CLIENT_COMMANDSPROTOCOL_HPP

#include <QObject>
#include <QTimer>
#include "synchapi.h"

#include <chrono>

#include "../Socket/Socket.hpp"
#include "../BaseProtocol/BaseProtocol.hpp"
#include "../../Gamepad/Gamepad.hpp"

#include "DataStructs/TelemetryStruct/TelemetryStruct.hpp"

class CommandsProtocol final : public QObject, public BaseProtocol {

Q_OBJECT

public:
    CommandsProtocol(int gamepadId, QObject *parent);

    ~CommandsProtocol() override;

    void SetGamepadId(size_t id);

    size_t GetGamepadId() const;

    void Stop();

    bool Connect(const QString &address, uint16_t port);

    inline bool GetError() const { return _errorStatus; }

    inline TelemetryStruct GetTelemetryStruct() {

        this->_telemetryMutex.lock_shared();
        TelemetryStruct telemetry = this->_telemetry;
        this->_telemetryMutex.unlock_shared();

        return telemetry;
    }

    bool IsStreamOnline() const final { return _socket.IsOnline(); }

public
    slots:
            void SendCommand();

private:
    TelemetryStruct _telemetry;

    Socket _socket;

    mutable std::shared_mutex _telemetryMutex;

    Control::Gamepad _gamepad;

    std::atomic<ErrorType> _errorStatus;

    QTimer _timer;

    inline void SetErrorStatus(BaseProtocol::ErrorType errorType) { _errorStatus = errorType; }

    inline void SetTelemetryStruct(const TelemetryStruct &telemetry) {
        this->_telemetryMutex.lock();
        this->_telemetry = telemetry;
        this->_telemetryMutex.unlock();
    }
};

#endif
