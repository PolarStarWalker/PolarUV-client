#ifndef CLIENT_ROBOTSETTINGSWIDGET_HPP
#define CLIENT_ROBOTSETTINGSWIDGET_HPP

//this must be first include
#include <TcpSession/TcpSession.hpp>

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class RobotSettingsWidget; }
QT_END_NAMESPACE

class RobotSettingsWidget : public QWidget {
Q_OBJECT

public:
    explicit RobotSettingsWidget(QWidget *parent = nullptr);

    ~RobotSettingsWidget() override;

private:

    Ui::RobotSettingsWidget *ui;

    [[nodiscard]] std::string Serialize() const noexcept;

    void Deserialize(const std::string &data) noexcept;

    const lib::network::TcpSession& _transmitter;

public slots:
    void UpdateGeometry(QSize newParentSize);

private slots:
    void SendSettings() const;

    void ReceiveSettings();

    void UpdateMotorsTable(int value);

    void UpdateHandTable(int value);

    void UpdateMaxSpeedEdit(int value);

    void UpdateMaxSpeedSlider(const QString& string);
};

#endif