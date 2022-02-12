#ifndef CLIENT_AUTHORIZATIONWIDGET_HPP
#define CLIENT_AUTHORIZATIONWIDGET_HPP

#include "../WidgetResources.hpp"

#include <QWidget>
#include <QMainWindow>
#include <QSettings>

template<class Type>
concept isWidget = std::is_convertible_v<Type*, QWidget*>;

QT_BEGIN_NAMESPACE
namespace Ui { class AuthorizationWidget; }
QT_END_NAMESPACE

class AuthorizationWidget : public QWidget {
Q_OBJECT

public:
    explicit AuthorizationWidget(QMainWindow *parent);

    ~AuthorizationWidget() override;

    template<isWidget Type, typename ... Args>
    [[nodiscard]]
    inline Type *CreateWithResources(QMainWindow *parent, Args&& ...args) {
        auto widget = new Type(parent, resources_, args...);
        return widget;
    }

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

};

#endif
