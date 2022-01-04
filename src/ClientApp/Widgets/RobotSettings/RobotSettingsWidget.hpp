#ifndef CLIENT_ROBOTSETTINGSWIDGET_HPP
#define CLIENT_ROBOTSETTINGSWIDGET_HPP

//this must be first include
#include <TcpSession/TcpSession.hpp>

#include <QOpenGLWidget>

class RobotSettingsWidget : public QOpenGLWidget {

public:
    RobotSettingsWidget();

    void SendSettings() const;

    void ReceiveSettings();


private:
    [[nodiscard]] std::string Serialize() const;

    void Deserialize(const std::string &data);

    const lib::network::TcpSession& _transmitter;
};

#endif