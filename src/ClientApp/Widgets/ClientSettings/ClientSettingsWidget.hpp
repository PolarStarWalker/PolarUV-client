#ifndef CLIENT_CLIENTSETTINGSWIDGET_HPP
#define CLIENT_CLIENTSETTINGSWIDGET_HPP

#include <QWidget>
#include <QSettings>


QT_BEGIN_NAMESPACE
namespace Ui { class ClientSettingsWidget; }
QT_END_NAMESPACE

class ClientSettingsWidget : public QWidget {
Q_OBJECT

public:
    explicit ClientSettingsWidget(QWidget *parent = nullptr);

    ~ClientSettingsWidget() override;

private:
    Ui::ClientSettingsWidget *ui;

    std::unique_ptr<QSettings> settings_;

private slots:

    void LoadSettings();
    void SaveSettings();
};

enum AnalogActions : int8_t {
    NoAnalogAction = 0,
    MoveX = 1,
    MoveY = 2,
    MoveZ = 3,
    RotateX = 4,
    RotateY = 5,
    RotateZ = 6,
    GrabHand = 7,
    RotateHand = 8,
};

enum DiscreteActions : int8_t {
    NoDiscreteAction = 0,
    TurnOn = 1,
    TurnOff = 2
};

#endif //CLIENT_CLIENTSETTINGSWIDGET_HPP
