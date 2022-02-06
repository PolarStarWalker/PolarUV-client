#ifndef CLIENT_AUTHORIZATIONWIDGET_HPP
#define CLIENT_AUTHORIZATIONWIDGET_HPP

#include <TcpSession/TcpSession.hpp>

#include <QWidget>
#include <QMainWindow>
#include <QSettings>

#include "../WidgetResources.hpp"

template<class Type>
concept can_registry = requires(Type obj){
    obj.StopWidget();
    obj.StartWidget();
} && std::is_convertible_v<Type*, QWidget*>;


QT_BEGIN_NAMESPACE
namespace Ui { class AuthorizationWidget; }
QT_END_NAMESPACE

class AuthorizationWidget : public QWidget {
Q_OBJECT

public:
    explicit AuthorizationWidget(QMainWindow *mainWindow, QWidget *parent = nullptr);

    ~AuthorizationWidget() override;

    template<can_registry Type, typename ... Args>
    [[nodiscard]]
    Type* Registry(QMainWindow *parent, Args&& ...args);

private:
    Ui::AuthorizationWidget *ui;

    boost::asio::io_context ioContext_;
    QSettings settings_;
    WidgetResources resources_;

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
inline Type *AuthorizationWidget::Registry(QMainWindow *parent, Args&& ...args) {
    auto widget = new Type(parent, resources_, args...);
    connect(this, SIGNAL(StartWidget()), widget, SLOT(StartWidget()));
    connect(this, SIGNAL(StopWidget()), widget, SLOT(StopWidget()));
    widget->StopWidget();
    return widget;
}

#endif
