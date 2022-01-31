#ifndef CLIENT_AUTORIZATIONWIDGET_HPP
#define CLIENT_AUTORIZATIONWIDGET_HPP

/// Без этой штуки ругается на подключение iphlpapi.h
#define WIN32_LEAN_AND_MEAN

#include <QWidget>
#include <QMainWindow>
#include <QSettings>

#include <iphlpapi.h>

#include "./Gamepad/Gamepad.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class AutorizationWidget; }
QT_END_NAMESPACE

class AutorizationWidget : public QWidget {
Q_OBJECT

public:
    explicit AutorizationWidget(QMainWindow *mainWindow, QWidget *parent = nullptr);

    ~AutorizationWidget() override;

private:
    Ui::AutorizationWidget *ui;

    std::unique_ptr<QSettings> settings_;

private slots:

    void RefreshClientIPs();

    void RefreshGamepadIDs();

    void LaunchHandler();

signals:

    void Launched(const QString& robotIP, const QString& clientIP, int gamepadID);
};


#endif //CLIENT_AUTORIZATIONWIDGET_HPP
