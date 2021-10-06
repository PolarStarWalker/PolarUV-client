#include "./Resources/Resources.hpp"

Resources::Resources() {
    this->background = new QPixmap("Icons/Background.png");

    this->cameraIcon = new QIcon("Icons/CameraIcon.png");
    this->robotIcon = new QIcon("Icons/RobotIcon.png");
    this->clientIcon = new QIcon("Icons/ClientIcon.png");
    this->codeIcon = new QIcon("Icons/CodeIcon.png");
    this->fullScreenIcon = new QIcon("Icons/FullScreenIcon.png");
    this->showTabBarIcon = new QIcon("Icons/ShowTabBarIcon.png");
    this->hideTabBarIcon = new QIcon("Icons/HideTabBarIcon.png");
    this->screenshotIcon = new QIcon("Icons/ScreenshotIcon.png");
    this->whiteVideoIcon = new QIcon("Icons/WhiteVideoIcon.png");
    this->reloadIcon = new QIcon("Icons/ReloadIcon.png");
    this->bugIcon = new QIcon("Icons/BugIcon.png");
    this->greenStartIcon = new QIcon("Icons/GreenStartIcon.png");
    this->redStartIcon = new QIcon("Icons/RedStartIcon.png");
    this->pauseIcon = new QIcon("Icons/PauseIcon.png");
    this->playIcon = new QIcon("Icons/PlayIcon.png");
}

