#ifndef CLIENT_COMMANSSETTINGSWIDGET_HPP
#define CLIENT_COMMANSSETTINGSWIDGET_HPP

#include <QWidget>
#include <QSettings>

#include "../WidgetResources.hpp"
#include "CommandsSettingsStruct.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CommandsSettingsWidget; }
QT_END_NAMESPACE

class CommandsSettingsWidget : public QWidget {
Q_OBJECT

public:
    CommandsSettingsWidget(QWidget *parent);

    ~CommandsSettingsWidget() override;

    ControlsSettings GetControlsSettings();

private:

    Ui::CommandsSettingsWidget *ui;

    std::unique_ptr<QSettings> settings_;

private slots:

    void LoadSettings();

    void SaveSettings();
};

#endif
