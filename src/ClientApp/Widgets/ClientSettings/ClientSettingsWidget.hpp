#ifndef CLIENT_CLIENTSETTINGSWIDGET_HPP
#define CLIENT_CLIENTSETTINGSWIDGET_HPP

#include <QWidget>


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

public slots:
    void UpdateGeometry(QSize newParentSize);

private slots:
//    void SaveClientSettings();
//
//    void LoadClientSettings();
//
//    void RefreshGamepads();
//
//    void RefreshClientIps();
};


#endif //CLIENT_CLIENTSETTINGSWIDGET_HPP
