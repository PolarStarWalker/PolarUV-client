#ifndef CLIENT_AUTHORIZATIONWIDGET_HPP
#define CLIENT_AUTHORIZATIONWIDGET_HPP

#include "../WidgetResources.hpp"

#include <QWidget>
#include <QMainWindow>
#include <QSettings>
#include <QWindow>
#include <QOpenGLContext>

template<class Type>
concept isWidget = std::is_convertible_v<Type*, QObject*>;

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
        auto widget = new Type(parent, resources_, std::forward(args)...);
        return widget;
    }

private:
    Ui::AuthorizationWidget *ui;

    boost::asio::io_context ioContext_;
    QSettings settings_;
    WidgetResources resources_;

    QWindow renderWindow_;
    QOpenGLContext openGLContext_;
    QOpenGLFramebufferObjectFormat fboFormat_;

private slots:

    void RefreshGamepadIDs();

    void LaunchHandler();

signals:

    void StartWidget();
    void StopWidget();

};

#endif
