#include "./Resources/MainWindowResources.hpp"

MainWindowResources::MainWindowResources() {

    this->_resources = std::make_unique<Resources>();

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

const MainWindowResources &MainWindowResources::GetInstance()  {
    const static MainWindowResources instance;
    return instance;
}

NewMainWindowResources::NewMainWindowResources() {
    Background = QPixmap("Icons/Background.png");

    /// Tabs
    CameraIcon = QIcon("Icons/CameraIcon.png");
    SettingsIcon = QIcon("Icons/SettingsIcon.png");
    CodeIcon = QIcon("Icons/CodeIcon.png");

    /// Buttons
    HamburgerIcon = QIcon("Icons/HamburgerIcon.png");
    ScreenshotIcon = QIcon("Icons/ScreenshotIcon.png");
    WhiteVideoIcon = QIcon("Icons/WhiteVideoIcon.png");
    ReloadIcon = QIcon("Icons/ReloadIcon.png");
    BugIcon = QIcon("Icons/BugIcon.png");
    GreenStartIcon = QIcon("Icons/GreenStartIcon.png");
    RedStartIcon = QIcon("Icons/RedStartIcon.png");
    PauseIcon = QIcon("Icons/PauseIcon.png");
    PlayIcon = QIcon("Icons/PlayIcon.png");
    WindowIcon = QIcon("Icons/WindowIcon.png");

    /// Gamepad buttons
    AButtonIcon = QPixmap("Icons/AButtonIcon.png");
    BButtonIcon = QPixmap("Icons/BButtonIcon.png");
    XButtonIcon = QPixmap("Icons/XButtonIcon.png");
    YButtonIcon = QPixmap("Icons/YButtonIcon.png");
    DPadHorizontalIcon = QPixmap("Icons/DPadHorizontalIcon.png");
    DPadVerticalIcon = QPixmap("Icons/DPadVerticalIcon.png");
    LSHorizontalIcon = QPixmap("Icons/LSHorizontalIcon.png");
    LSVerticalIcon = QPixmap("Icons/LSVerticalIcon.png");
    LSPressIcon = QPixmap("Icons/LSPressIcon.png");
    RSHorizontalIcon = QPixmap("Icons/RSHorizontalIcon.png");
    RSVerticalIcon = QPixmap("Icons/RSVerticalIcon.png");
    RSPressIcon = QPixmap("Icons/RSPressIcon.png");
    LBLTButtonIcon = QPixmap("Icons/LBLTButtonIcon.png");
    RBRTButtonIcon = QPixmap("Icons/RBRTButtonIcon.png");
    BackButtonIcon = QPixmap("Icons/BackButtonIcon.png");
    MenuButtonIcon = QPixmap("Icons/MenuButtonIcon.png");
}
