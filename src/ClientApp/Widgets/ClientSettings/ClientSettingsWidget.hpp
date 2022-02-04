#ifndef CLIENT_CLIENTSETTINGSWIDGET_HPP
#define CLIENT_CLIENTSETTINGSWIDGET_HPP

#include <QWidget>
#include <QSettings>

#include "ControlsSettingsStruct.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class ClientSettingsWidget; }
QT_END_NAMESPACE

class ClientSettingsWidget : public QWidget {
Q_OBJECT

public:
    explicit ClientSettingsWidget(QWidget *parent = nullptr);

    ~ClientSettingsWidget() override;

    ControlsSettings GetControlsSettings();

public slots:
    void StartWidget();
    void StopWidget();

private:
    Ui::ClientSettingsWidget *ui;

    std::unique_ptr<QSettings> settings_;

private slots:

    void LoadSettings();

    void SaveSettings();
};

#endif
