#include "DisplayWidget.hpp"
#include "ui_DisplayWidget.h"


DisplayWidget::DisplayWidget(QMainWindow *mainWindow, WidgetResources &resources) :
        QWidget(mainWindow),
        ui(new Ui::DisplayWidget),
        resources_(resources),
        stream_(){

    ui->setupUi(this);

    geometry_ = geometry();

    commandsProtocol_ = std::make_unique<CommandsProtocol>(0, this);

    //yawIndicator_ = std::make_unique<YawIndicator>(ui->CentralWidget);

    placeholderPixmap_ = QPixmap("Icons/Background.png");
    updateTimer_ = std::make_unique<QTimer>();
    updateTimer_->start(1000/60);
    connect(updateTimer_.get(), SIGNAL(timeout()), this, SLOT(UpdateBackgroundImage()));

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







