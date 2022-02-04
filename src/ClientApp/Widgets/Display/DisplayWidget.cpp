#include "DisplayWidget.hpp"
#include "ui_DisplayWidget.h"


DisplayWidget::DisplayWidget(QMainWindow *mainWindow, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::DisplayWidget),
        stream_(){

    ui->setupUi(this);

    commandsProtocol_ = std::make_unique<CommandsProtocol>(0, this);

    connect(ui->SideBarButton, SIGNAL(clicked(bool)), this, SLOT(HideSideBarButton()));
    connect(ui->SideBarButton, SIGNAL(clicked(bool)), mainWindow, SLOT(ShowSideBar()));

    connect(ui->CameraButton, SIGNAL(clicked(bool)), this, SLOT(SwitchVideoStream()));
    connect(ui->RecordingButton, SIGNAL(clicked(bool)), this, SLOT(SwitchVideoCapture()));
    connect(ui->ScreenshotButton, SIGNAL(clicked(bool)), this, SLOT(TakeScreenshot()));

    ui->SideBarButton->hide();
    ui->ScreenshotLabel->hide();
    ui->RecordingLabel->hide();
}

DisplayWidget::~DisplayWidget() {
    delete ui;
}

void DisplayWidget::ShowSideBarButton() {
    ui->SideBarButton->show();
}

void DisplayWidget::HideSideBarButton() {
    ui->SideBarButton->hide();
}

void DisplayWidget::StopWidget() {

}

void DisplayWidget::StartWidget() {

}







