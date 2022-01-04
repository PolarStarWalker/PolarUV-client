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


    static const MainWindowResources& GetInstance() {
        const static MainWindowResources instance;
        return instance;
    }

    inline const QPixmap &GetBackground() const { return this->_resources->Background; }

    inline const QIcon &GetMainWindowIcon() const { return this->_resources->WindowIcon; }

    /// Tabs

    inline const QIcon &GetCameraIcon() const { return this->_resources->CameraIcon; }

    inline const QIcon &GetSettingsIcon() const { return this->_resources->SettingsIcon; }

    inline const QIcon &GetCodeIcon() const { return this->_resources->CodeIcon; }

    /// Buttons

    inline const QIcon &GetHamburgerIcon() const { return this->_resources->HamburgerIcon; }

    inline const QIcon &GetScreenshotIcon() const { return this->_resources->ScreenshotIcon; }

    inline const QIcon &GetWhiteVideoIcon() const { return this->_resources->WhiteVideoIcon; }

    inline const QIcon &GetReloadIcon() const { return this->_resources->ReloadIcon; }

    inline const QIcon &GetBugIcon() const { return this->_resources->BugIcon; }

    inline const QIcon &GetGreenStartIcon() const { return this->_resources->GreenStartIcon; }

    inline const QIcon &GetRedStartIcon() const { return this->_resources->RedStartIcon; }

    inline const QIcon &GetPauseIcon() const { return this->_resources->PauseIcon; }

    inline const QIcon &GetPlayIcon() const { return this->_resources->PlayIcon; }

    /// Gamepad buttons
    inline const QPixmap &GetAButtonIcon() const { return this->_resources->AButtonIcon; }

    inline const QPixmap &GetBButtonIcon() const { return this->_resources->BButtonIcon; }

    inline const QPixmap &GetXButtonIcon() const { return this->_resources->XButtonIcon; }

    inline const QPixmap &GetYButtonIcon() const { return this->_resources->YButtonIcon; }

    inline const QPixmap &GetDPadHorizontalIcon() const { return this->_resources->DPadHorizontalIcon; }

    inline const QPixmap &GetDPadVerticalIcon() const { return this->_resources->DPadVerticalIcon; }

    inline const QPixmap &GetLSHorizontalIcon() const { return this->_resources->LSHorizontalIcon; }

    inline const QPixmap &GetLSVerticalIcon() const { return this->_resources->LSVerticalIcon; }

    inline const QPixmap &GetLSPressIcon() const { return this->_resources->LSPressIcon; }

    inline const QPixmap &GetRSHorizontalIcon() const { return this->_resources->RSHorizontalIcon; }

    inline const QPixmap &GetRSVerticalIcon() const { return this->_resources->RSVerticalIcon; }

    inline const QPixmap &GetRSPressIcon() const { return this->_resources->RSPressIcon; }

    inline const QPixmap &GetLBLTButtonIcon() const { return this->_resources->LBLTButtonIcon; }

    inline const QPixmap &GetRBRTButtonIcon() const { return this->_resources->RBRTButtonIcon; }

    inline const QPixmap &GetBackButtonIcon() const { return this->_resources->BackButtonIcon; }

    inline const QPixmap &GetMenuButtonIcon() const { return this->_resources->MenuButtonIcon; }
};

#endif
