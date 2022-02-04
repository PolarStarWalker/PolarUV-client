#ifndef CLIENT_PYTHONENVIRONMENTWIDGET_HPP
#define CLIENT_PYTHONENVIRONMENTWIDGET_HPP

#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class PythonEnvironmentWidget; }
QT_END_NAMESPACE

class PythonEnvironmentWidget : public QWidget {
Q_OBJECT

public:
    explicit PythonEnvironmentWidget(QWidget *parent = nullptr);

    ~PythonEnvironmentWidget() override;

public slots:
    void StartWidget();
    void StopWidget();

private:
    Ui::PythonEnvironmentWidget *ui;

private slots:
    void ReleaseCode();
    void DebugCode();
};


#endif //CLIENT_PYTHONENVIRONMENTWIDGET_HPP
