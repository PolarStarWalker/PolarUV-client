#ifndef CLIENT_AUTORIZATIONWIDGET_HPP
#define CLIENT_AUTORIZATIONWIDGET_HPP

#include <TcpSession/TcpSession.hpp>

#include <QWidget>
#include <QMainWindow>
#include <QSettings>

#include <Gamepad/Gamepad.hpp>

#include "./Settings.hpp"

template<class Type>
concept can_registry = requires(Type obj){
    obj.StopWidget();
    obj.StartWidget();
} && std::is_convertible_v<Type*, QWidget*>;


QT_BEGIN_NAMESPACE
namespace Ui { class AutorizationWidget; }
QT_END_NAMESPACE

class AutorizationWidget : public QWidget {
Q_OBJECT

public:
    explicit AutorizationWidget(QMainWindow *mainWindow, QWidget *parent = nullptr);

    ~AutorizationWidget() override;

    template<can_registry Type, typename ... Args>
    Type* Registry(QMainWindow *parent, Args&& ...args);

private:
    Ui::AutorizationWidget *ui;

    QSettings settings_;

private slots:

    void RefreshClientIPs();

    void RefreshGamepadIDs();

    void LaunchHandler();

signals:

    void StartWidget();
    void StopWidget();

    void Launched(const QString& robotIP, const QString& clientIP, int gamepadID);
};



template<can_registry Type, typename... Args>
Type *AutorizationWidget::Registry(QMainWindow *parent, Args&& ...args) {
    auto widget = new Type(parent, args...);
    connect(this, SIGNAL(StartWidget()), widget, SLOT(StartWidget()));
    connect(this, SIGNAL(StopWidget()), widget, SLOT(StopWidget()));
    return widget;
}

#endif //CLIENT_AUTORIZATIONWIDGET_HPP
