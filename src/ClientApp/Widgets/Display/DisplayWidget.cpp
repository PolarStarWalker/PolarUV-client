#include "DisplayWidget.hpp"
#include "ui_DisplayWidget.h"


DisplayWidget::DisplayWidget(QMainWindow *mainWindow, QWidget *parent) :
        QWidget(parent), ui(new Ui::DisplayWidget) {

    ui->setupUi(this);

    videoProtocol_ = std::make_unique<VideoProtocol>();
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

void DisplayWidget::SwitchVideoStream() {
    if (!videoProtocol_->IsStreamOnline()) {
        videoProtocol_->StartAsync(RobotIP, ClientIP);
    } else {
        videoProtocol_->Stop(RobotIP);
    }
}

void DisplayWidget::SwitchVideoCapture() {
    auto function = [&]() {
        if (!videoProtocol_->IsStreamOnline()) {
            throw lib::exceptions::InvalidOperationException("Невозможно записать видео:\n трансляция не включена");
        }
        if (videoProtocol_->IsVideoWriterOnline()) {
            videoProtocol_->StopVideoWrite();
            ui->RecordingButton->setIcon(QIcon("Icons/VideoIcon.png"));
        } else {
            videoProtocol_->StartVideoWrite();
            ui->RecordingButton->setIcon(QIcon("Icons/GreenVideoIcon.png"));
        }
    };
    ExceptionHandler(nullptr, nullptr, function);
}

void DisplayWidget::TakeScreenshot() {
    auto function = [&]() {
        if (!videoProtocol_->IsStreamOnline()) {
            throw lib::exceptions::InvalidOperationException("Невозможно сделать снимок:\n трансляция не включена");
        }
        videoProtocol_->TakeScreenshot();
    };
    ExceptionHandler(nullptr, nullptr, function);
}

void DisplayWidget::SwitchSendingCommands() {
    if (!commandsProtocol_->IsStreamOnline()) {
        commandsProtocol_->Connect(RobotIP, COMMANDS_PORT);
        return;
    }
    commandsProtocol_->Stop();
}





