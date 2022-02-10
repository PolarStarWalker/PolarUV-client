#ifndef CLIENT_ROBOTSETTINGSWIDGET_HPP
#define CLIENT_ROBOTSETTINGSWIDGET_HPP

//this must be first include
#include "../WidgetResources.hpp"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class RobotSettingsWidget; }
QT_END_NAMESPACE

class RobotSettingsWidget : public QWidget {
Q_OBJECT

public:
    RobotSettingsWidget(QWidget *parent, WidgetResources& resources);

    ~RobotSettingsWidget() override;

    void SetRobotIP(const QString& ip) {this->RobotIP = ip;};
    void SetClientIP(const QString& ip) {this->ClientIP = ip;};

public slots:
    void StartWidget();
    void StopWidget();
    
private:

    WidgetResources& resources_;

    Ui::RobotSettingsWidget *ui;

    [[nodiscard]] std::string Serialize() const noexcept;

    void Deserialize(const std::string &data) noexcept;

    QString RobotIP{};
    QString ClientIP{};

private slots:

    void SendSettings();

    void ReceiveSettings();

    void UpdateMotorsTable(int value);

    void UpdateHandTable(int value);

    void UpdateMaxSpeedEdit(int value);

    void UpdateMaxSpeedSlider(const QString& string);
};

#endif