#ifndef CLIENT_MOVESETTINGSWIDGET_HPP
#define CLIENT_MOVESETTINGSWIDGET_HPP

//this must be first include
#include "../WidgetResources.hpp"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MoveSettingsWidget; }
QT_END_NAMESPACE

class MoveSettingsWidget : public QWidget {
Q_OBJECT

public:
    MoveSettingsWidget(QWidget *parent, WidgetResources& resources);

    ~MoveSettingsWidget() override;

public slots:
    void StartWidget();
    void StopWidget();
    
private:

    WidgetResources& resources_;

    Ui::MoveSettingsWidget *ui;

    [[nodiscard]] std::string Serialize() const noexcept;

    void Deserialize(const std::string &data) noexcept;

private slots:

    void SendSettings();

    void ReceiveSettings();

    void UpdateMotorsTable(int value);

    void UpdateHandTable(int value);

    void UpdateMaxSpeedEdit(int value);

    void UpdateMaxSpeedSlider(const QString& string);
};

#endif