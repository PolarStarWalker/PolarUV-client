#ifndef CLIENT_SENSORSSETTINGSWIDGET_HPP
#define CLIENT_SENSORSSETTINGSWIDGET_HPP

//this must be first include
#include "../WidgetResources.hpp"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SensorsSettingsWidget; }
QT_END_NAMESPACE

class SensorsSettingsWidget : public QWidget {
Q_OBJECT

public:
    explicit SensorsSettingsWidget(QWidget *parent);

    ~SensorsSettingsWidget() override;

private:
    Ui::SensorsSettingsWidget *ui;
};


#endif //CLIENT_SENSORSSETTINGSWIDGET_HPP
