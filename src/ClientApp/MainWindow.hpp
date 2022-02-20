#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./Widgets/widgets.hpp"

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QShortcut>
#include <QGraphicsDropShadowEffect>
#include <QGridLayout>
#include <QResizeEvent>

template<class Type>
concept CanRegistry = requires(Type obj){
    obj.StopWidget();
    obj.StartWidget();
} && std::is_convertible_v<Type *, QWidget *>;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() final;

protected:

    [[nodiscard]]
    inline AuthorizationWidget *CreateAuthorizationWidget(QWidget *dst) {
        auto widget = new AuthorizationWidget(this);
        dst->layout()->addWidget(widget);
        return widget;
    }

    template<CanRegistry Type, typename ... Args>
    [[nodiscard]]
    inline Type *AddWidget(QWidget *dst, Args &&... args) {
        auto widget = authorizationWidget_->template CreateWithResources<Type>(this, std::forward(args)...);

        dst->layout()->addWidget(widget);

        connect(this, SIGNAL(StartWidget()), widget, SLOT(StartWidget()));
        connect(this, SIGNAL(StopWidget()), widget, SLOT(StopWidget()));

        widget->StopWidget();

        return widget;
    }

    void SetupSlots();


public slots:

    void Launch();

    void LaunchDebug();

    void ShowSideBar();

private slots:

    void SwitchToPage1();

    void SwitchToPage2();

    void SwitchToPage2_1();

    void SwitchToPage2_2();

    void SwitchToPage2_3();

    void SwitchToPage3();

    void SwitchToPage4();

    void SwitchSideBarButton(int currentIndex);

    void HideSideBar();

    void Pause();

signals:

    void StartWidget();

    void StopWidget();

private:

    Ui::MainWindow *ui;

    ///Первым в объявлении всегда должен быть виджет авторизации, поскольку он последним будет уничтожаться
    AuthorizationWidget *authorizationWidget_;
    DisplayWidget *displayWidget_;
    MoveSettingsWidget *moveSettingsWidget_;
    SensorsSettingsWidget *sensorsSettingsWidget_;
    CommandsSettingsWidget *controlSettingsWidget_;
    PythonEnvironmentWidget *pythonIDEWidget_;
    CommandsWidget *commandsWidget_;
    SensorsWidget *sensorsWidget_;

    bool isDebug_;
};

#endif

