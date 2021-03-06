#include "Exceptions/Exceptions.hpp"
#include "MainWindow.hpp"
#include "../../cmake-build-debug-msys-gcc/src/ClientApp/ClientApp_autogen/ui_mainwindow.h"

void MainWindow::SetupSlots() {
    connect(ui->Page1Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage1()));
    connect(ui->Page2Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage2()));
    connect(ui->Page3Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage3()));
    connect(ui->Page4Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage4()));
    connect(ui->Page2_1Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage2_1()));
    connect(ui->Page2_2Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage2_2()));
    connect(ui->Page2_3Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage2_3()));
    connect(ui->Page2_4Button, SIGNAL(clicked(bool)), SLOT(SwitchToPage2_4()));
    connect(ui->PrimaryStackedWidget, SIGNAL(currentChanged(int)), SLOT(SwitchSideBarButton(int)));
    connect(ui->SideBarButton, SIGNAL(clicked(bool)), SLOT(HideSideBar()));
    connect(ui->BackButton, SIGNAL(clicked(bool)), SLOT(Pause()));
    connect(ui->SideBarButton, SIGNAL(clicked(bool)), displayWidget_, SLOT(ShowSideBarButton()));

    keyF11 = new QShortcut(Qt::Key_F11,this,SLOT(SwitchWindowMode()));
    keyEsc = new QShortcut(Qt::Key_Escape,this,SLOT(SetWindowedMode()));
}

void MainWindow::Pause() {

    if (!isDebug_) {
        emit StopWidget();
        isDebug_ = false;
    }

    ui->MainStackedWidget->setCurrentIndex(0);
}

void MainWindow::SwitchSideBarButton(int currentIndex) {
    if (currentIndex == 0) {
        ui->SideBarButton->show();
        ui->Spacer1->changeSize(20, 30, QSizePolicy::Fixed, QSizePolicy::Fixed);
        return;
    }

    ui->SideBarButton->hide();
    ui->Spacer1->changeSize(20, 90, QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void MainWindow::HideSideBar() {
    ui->SideBar->hide();
}

void MainWindow::SwitchWindowMode() {
    if (this->windowState() != Qt::WindowFullScreen)
        this->setWindowState(Qt::WindowFullScreen);
    else
        this->setWindowState(Qt::WindowNoState);
}

void MainWindow::SetWindowedMode() {
    this->setWindowState(Qt::WindowNoState);
}

/// ???????????????????? ?????????????? ????????. ToDo: shushkov.d ??????????????????
QString activeButtonStyleSheet = "QPushButton { color: white; border:none; background-color: rgb(30,140,200); }"
                                 "QToolTip { color: white; background-color: rgb(30,140,200);"
                                 "border: 1px solid rgb(38,179,255); border-radius: 3px; }";
QString inactiveButtonStyleSheet = "QPushButton { color: white; border: none; background-color: transparent; }"
                                   "QPushButton:hover:!pressed { background-color: rgb(70,70,70); }"
                                   "QToolTip { color: white; background-color: rgb(30,140,200);"
                                   "border: 1px solid rgb(38,179,255); border-radius: 3px; }";

void MainWindow::SwitchToPage1() {
    ui->PrimaryStackedWidget->setCurrentIndex(0);
    ui->Page1Button->setStyleSheet(activeButtonStyleSheet);
    ui->Page2Button->setStyleSheet(inactiveButtonStyleSheet);
    ui->Page3Button->setStyleSheet(inactiveButtonStyleSheet);
    ui->Page4Button->setStyleSheet(inactiveButtonStyleSheet);
}

void MainWindow::SwitchToPage2() {
    ui->PrimaryStackedWidget->setCurrentIndex(1);
    ui->Page1Button->setStyleSheet(inactiveButtonStyleSheet);
    ui->Page2Button->setStyleSheet(activeButtonStyleSheet);
    ui->Page3Button->setStyleSheet(inactiveButtonStyleSheet);
    ui->Page4Button->setStyleSheet(inactiveButtonStyleSheet);
}

void MainWindow::SwitchToPage3() {
    ui->PrimaryStackedWidget->setCurrentIndex(2);
    ui->Page1Button->setStyleSheet(inactiveButtonStyleSheet);
    ui->Page2Button->setStyleSheet(inactiveButtonStyleSheet);
    ui->Page3Button->setStyleSheet(activeButtonStyleSheet);
    ui->Page4Button->setStyleSheet(inactiveButtonStyleSheet);
}

void MainWindow::SwitchToPage4() {
    ui->PrimaryStackedWidget->setCurrentIndex(3);
    ui->Page1Button->setStyleSheet(inactiveButtonStyleSheet);
    ui->Page2Button->setStyleSheet(inactiveButtonStyleSheet);
    ui->Page3Button->setStyleSheet(inactiveButtonStyleSheet);
    ui->Page4Button->setStyleSheet(activeButtonStyleSheet);
}

QString activeButtonStyleSheet2 = "QPushButton { color: white; border: 1px solid rgb(38,179,255); border-radius: 5px;"
                                  "background-color: rgb(30,140,200); }";
QString inactiveButtonStyleSheet2 = "QPushButton { color: white; border: none; border-radius: 5px;"
                                    "background-color: transparent; }"
                                    "QPushButton:hover:!pressed { background-color: rgb(70,70,70); }";

void MainWindow::SwitchToPage2_1() {
    ui->SettingsStackedWidget->setCurrentIndex(0);
    ui->Page2_1Button->setStyleSheet(activeButtonStyleSheet2);
    ui->Page2_2Button->setStyleSheet(inactiveButtonStyleSheet2);
    ui->Page2_3Button->setStyleSheet(inactiveButtonStyleSheet2);
    ui->Page2_4Button->setStyleSheet(inactiveButtonStyleSheet2);
}

void MainWindow::SwitchToPage2_2() {
    ui->SettingsStackedWidget->setCurrentIndex(1);
    ui->Page2_1Button->setStyleSheet(inactiveButtonStyleSheet2);
    ui->Page2_2Button->setStyleSheet(activeButtonStyleSheet2);
    ui->Page2_3Button->setStyleSheet(inactiveButtonStyleSheet2);
    ui->Page2_4Button->setStyleSheet(inactiveButtonStyleSheet2);
}

void MainWindow::SwitchToPage2_3() {
    ui->SettingsStackedWidget->setCurrentIndex(2);
    ui->Page2_1Button->setStyleSheet(inactiveButtonStyleSheet2);
    ui->Page2_2Button->setStyleSheet(inactiveButtonStyleSheet2);
    ui->Page2_3Button->setStyleSheet(activeButtonStyleSheet2);
    ui->Page2_4Button->setStyleSheet(inactiveButtonStyleSheet2);
}

void MainWindow::SwitchToPage2_4() {
    ui->SettingsStackedWidget->setCurrentIndex(3);
    ui->Page2_1Button->setStyleSheet(inactiveButtonStyleSheet2);
    ui->Page2_2Button->setStyleSheet(inactiveButtonStyleSheet2);
    ui->Page2_3Button->setStyleSheet(inactiveButtonStyleSheet2);
    ui->Page2_4Button->setStyleSheet(activeButtonStyleSheet2);
}
/// ?????????? ?????????????? ????????

/// ----- ?????????????????? ?????????? ----- ///

void MainWindow::Launch() {
    ui->MainStackedWidget->setCurrentIndex(1);
    emit StartWidget();
}

void MainWindow::LaunchDebug() {
    isDebug_ = true;
    ui->MainStackedWidget->setCurrentIndex(1);
}

void MainWindow::ShowSideBar() {
    ui->SideBar->show();
}



