#include "./Resources/MainWindowResources.hpp"

MainWindowResources::MainWindowResources() {

    this->_resources = new Resources;

    this->_resources->Background = QPixmap("Icons/Background.png");
    this->_resources->CameraIcon = QIcon("Icons/CameraIcon.png");
    this->_resources->RobotIcon = QIcon("Icons/RobotIcon.png");
    this->_resources->ClientIcon = QIcon("Icons/ClientIcon.png");
    this->_resources->CodeIcon = QIcon("Icons/CodeIcon.png");
    this->_resources->FullScreenIcon = QIcon("Icons/FullScreenIcon.png");
    this->_resources->ShowTabBarIcon = QIcon("Icons/ShowTabBarIcon.png");
    this->_resources->HideTabBarIcon = QIcon("Icons/HideTabBarIcon.png");
    this->_resources->ScreenshotIcon = QIcon("Icons/ScreenshotIcon.png");
    this->_resources->WhiteVideoIcon = QIcon("Icons/WhiteVideoIcon.png");
    this->_resources->ReloadIcon = QIcon("Icons/ReloadIcon.png");
    this->_resources->BugIcon = QIcon("Icons/BugIcon.png");
    this->_resources->GreenStartIcon = QIcon("Icons/GreenStartIcon.png");
    this->_resources->RedStartIcon = QIcon("Icons/RedStartIcon.png");
    this->_resources->PauseIcon = QIcon("Icons/PauseIcon.png");
    this->_resources->PlayIcon = QIcon("Icons/PlayIcon.png");
    this->_resources->WindowIcon = QIcon("Icons/WindowIcon.png");
}

MainWindowResources::~MainWindowResources() {
    delete this->_resources;
}