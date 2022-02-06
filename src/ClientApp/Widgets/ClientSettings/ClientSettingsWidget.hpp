#ifndef CLIENT_CLIENTSETTINGSWIDGET_HPP
#define CLIENT_CLIENTSETTINGSWIDGET_HPP

#include <QWidget>
#include <QSettings>

#include "../WidgetResources.hpp"
#include "ControlsSettingsStruct.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientSettingsWidget; }
QT_END_NAMESPACE

class ClientSettingsWidget : public QWidget {
Q_OBJECT

public:
    ClientSettingsWidget(QWidget *parent, WidgetResources& resources);

    ~ClientSettingsWidget() override;

    ControlsSettings GetControlsSettings();

public slots:
    void StartWidget();
    void StopWidget();

private:

    WidgetResources& resources_;

    Ui::ClientSettingsWidget *ui;

    std::unique_ptr<QSettings> settings_;

private slots:

    void LoadSettings();

    void SaveSettings();
};

#endif
