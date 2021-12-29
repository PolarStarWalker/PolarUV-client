#include "./Resources/MainWindowResources.hpp"

MainWindowResources::MainWindowResources() {

    this->_resources = std::unique_ptr<Resources>(new Resources);

    this->_resources->Background = QPixmap("Icons/Background.png");

    /// Tabs
    this->_resources->CameraIcon = QIcon("Icons/CameraIcon.png");
    this->_resources->SettingsIcon = QIcon("Icons/SettingsIcon.png");
    this->_resources->CodeIcon = QIcon("Icons/CodeIcon.png");

    /// Buttons
    this->_resources->HamburgerIcon = QIcon("Icons/HamburgerIcon.png");
    this->_resources->ScreenshotIcon = QIcon("Icons/ScreenshotIcon.png");
    this->_resources->WhiteVideoIcon = QIcon("Icons/WhiteVideoIcon.png");
    this->_resources->ReloadIcon = QIcon("Icons/ReloadIcon.png");
    this->_resources->BugIcon = QIcon("Icons/BugIcon.png");
    this->_resources->GreenStartIcon = QIcon("Icons/GreenStartIcon.png");
    this->_resources->RedStartIcon = QIcon("Icons/RedStartIcon.png");
    this->_resources->PauseIcon = QIcon("Icons/PauseIcon.png");
    this->_resources->PlayIcon = QIcon("Icons/PlayIcon.png");
    this->_resources->WindowIcon = QIcon("Icons/WindowIcon.png");

    /// Gamepad buttons
    this->_resources->AButtonIcon = QPixmap("Icons/AButtonIcon.png");
    this->_resources->BButtonIcon = QPixmap("Icons/BButtonIcon.png");
    this->_resources->XButtonIcon = QPixmap("Icons/XButtonIcon.png");
    this->_resources->YButtonIcon = QPixmap("Icons/YButtonIcon.png");
    this->_resources->DPadHorizontalIcon = QPixmap("Icons/DPadHorizontalIcon.png");
    this->_resources->DPadVerticalIcon = QPixmap("Icons/DPadVerticalIcon.png");
    this->_resources->LSHorizontalIcon = QPixmap("Icons/LSHorizontalIcon.png");
    this->_resources->LSVerticalIcon = QPixmap("Icons/LSVerticalIcon.png");
    this->_resources->LSPressIcon = QPixmap("Icons/LSPressIcon.png");
    this->_resources->RSHorizontalIcon = QPixmap("Icons/RSHorizontalIcon.png");
    this->_resources->RSVerticalIcon = QPixmap("Icons/RSVerticalIcon.png");
    this->_resources->RSPressIcon = QPixmap("Icons/RSPressIcon.png");
    this->_resources->LBLTButtonIcon = QPixmap("Icons/LBLTButtonIcon.png");
    this->_resources->RBRTButtonIcon = QPixmap("Icons/RBRTButtonIcon.png");
    this->_resources->BackButtonIcon = QPixmap("Icons/BackButtonIcon.png");
    this->_resources->MenuButtonIcon = QPixmap("Icons/MenuButtonIcon.png");
}