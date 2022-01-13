#ifndef CLIENT_MAIN_WINDOW_RESOURCES_HPP
#define CLIENT_MAIN_WINDOW_RESOURCES_HPP

#include <QPixmap>
#include <QIcon>

class MainWindowResources {
private:
    struct Resources {
        QPixmap Background;

        /// Tabs
        QIcon CameraIcon;
        QIcon SettingsIcon;
        QIcon CodeIcon;

        /// Buttons
        QIcon HamburgerIcon;
        QIcon ScreenshotIcon;
        QIcon WhiteVideoIcon;
        QIcon ReloadIcon;
        QIcon BugIcon;
        QIcon GreenStartIcon;
        QIcon RedStartIcon;
        QIcon PauseIcon;
        QIcon PlayIcon;
        QIcon WindowIcon;

        /// Gamepad buttons
        QPixmap AButtonIcon;
        QPixmap BButtonIcon;
        QPixmap XButtonIcon;
        QPixmap YButtonIcon;
        QPixmap DPadHorizontalIcon;
        QPixmap DPadVerticalIcon;
        QPixmap LSHorizontalIcon;
        QPixmap LSVerticalIcon;
        QPixmap LSPressIcon;
        QPixmap RSHorizontalIcon;
        QPixmap RSVerticalIcon;
        QPixmap RSPressIcon;
        QPixmap LBLTButtonIcon;
        QPixmap RBRTButtonIcon;
        QPixmap BackButtonIcon;
        QPixmap MenuButtonIcon;
    };

    std::unique_ptr<Resources> _resources;

    MainWindowResources();
    ~MainWindowResources() = default;

public:

    MainWindowResources(const MainWindowResources& resources) = delete;
    MainWindowResources(MainWindowResources&& resources) = delete;

    static const MainWindowResources& GetInstance();

    [[nodiscard]] inline const QPixmap &GetBackground() const { return this->_resources->Background; }

    [[nodiscard]] inline const QIcon &GetMainWindowIcon() const { return this->_resources->WindowIcon; }

    /// Tabs

    [[nodiscard]] inline const QIcon &GetCameraIcon() const { return this->_resources->CameraIcon; }

    [[nodiscard]] inline const QIcon &GetSettingsIcon() const { return this->_resources->SettingsIcon; }

    [[nodiscard]] inline const QIcon &GetCodeIcon() const { return this->_resources->CodeIcon; }

    /// Buttons

    [[nodiscard]] inline const QIcon &GetHamburgerIcon() const { return this->_resources->HamburgerIcon; }

    [[nodiscard]] inline const QIcon &GetScreenshotIcon() const { return this->_resources->ScreenshotIcon; }

    [[nodiscard]] inline const QIcon &GetWhiteVideoIcon() const { return this->_resources->WhiteVideoIcon; }

    [[nodiscard]] inline const QIcon &GetReloadIcon() const { return this->_resources->ReloadIcon; }

    [[nodiscard]] inline const QIcon &GetBugIcon() const { return this->_resources->BugIcon; }

    [[nodiscard]] inline const QIcon &GetGreenStartIcon() const { return this->_resources->GreenStartIcon; }

    [[nodiscard]] inline const QIcon &GetRedStartIcon() const { return this->_resources->RedStartIcon; }

    [[nodiscard]] inline const QIcon &GetPauseIcon() const { return this->_resources->PauseIcon; }

    [[nodiscard]] inline const QIcon &GetPlayIcon() const { return this->_resources->PlayIcon; }

    /// Gamepad buttons
    [[nodiscard]] inline const QPixmap &GetAButtonIcon() const { return this->_resources->AButtonIcon; }

    [[nodiscard]] inline const QPixmap &GetBButtonIcon() const { return this->_resources->BButtonIcon; }

    [[nodiscard]] inline const QPixmap &GetXButtonIcon() const { return this->_resources->XButtonIcon; }

    [[nodiscard]] inline const QPixmap &GetYButtonIcon() const { return this->_resources->YButtonIcon; }

    [[nodiscard]] inline const QPixmap &GetDPadHorizontalIcon() const { return this->_resources->DPadHorizontalIcon; }

    [[nodiscard]] inline const QPixmap &GetDPadVerticalIcon() const { return this->_resources->DPadVerticalIcon; }

    [[nodiscard]] inline const QPixmap &GetLSHorizontalIcon() const { return this->_resources->LSHorizontalIcon; }

    [[nodiscard]] inline const QPixmap &GetLSVerticalIcon() const { return this->_resources->LSVerticalIcon; }

    [[nodiscard]] inline const QPixmap &GetLSPressIcon() const { return this->_resources->LSPressIcon; }

    [[nodiscard]] inline const QPixmap &GetRSHorizontalIcon() const { return this->_resources->RSHorizontalIcon; }

    [[nodiscard]] inline const QPixmap &GetRSVerticalIcon() const { return this->_resources->RSVerticalIcon; }

    [[nodiscard]] inline const QPixmap &GetRSPressIcon() const { return this->_resources->RSPressIcon; }

    [[nodiscard]] inline const QPixmap &GetLBLTButtonIcon() const { return this->_resources->LBLTButtonIcon; }

    [[nodiscard]] inline const QPixmap &GetRBRTButtonIcon() const { return this->_resources->RBRTButtonIcon; }

    [[nodiscard]] inline const QPixmap &GetBackButtonIcon() const { return this->_resources->BackButtonIcon; }

    [[nodiscard]] inline const QPixmap &GetMenuButtonIcon() const { return this->_resources->MenuButtonIcon; }
};

#endif
