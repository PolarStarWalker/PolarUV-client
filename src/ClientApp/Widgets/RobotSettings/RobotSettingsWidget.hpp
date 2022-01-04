#ifndef CLIENT_ROBOTSETTINGSWIDGET_HPP
#define CLIENT_ROBOTSETTINGSWIDGET_HPP

//this must be first include
#include <TcpSession/TcpSession.hpp>

#include <QOpenGLWidget>

class RobotSettingsWidget : public QOpenGLWidget {
    class Data {

    };


public:
    void SendSettings();

    void GetSettings();


private:
    std::string Serialize() const;

    void Deserialize(const std::string &data);

};

#endif