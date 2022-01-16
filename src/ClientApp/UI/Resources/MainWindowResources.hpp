#ifndef CLIENT_MAIN_WINDOW_RESOURCES_HPP
#define CLIENT_MAIN_WINDOW_RESOURCES_HPP

#include <QPixmap>
#include <QIcon>
#include <Singleton.hpp>

class MainWindowResources {
public:
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
        QIcon MainWindowIcon;

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

private:
    std::unique_ptr<Resources> _resources;

    MainWindowResources();
    ~MainWindowResources() = default;

public:

    MainWindowResources(const MainWindowResources& resources) = delete;
    MainWindowResources(MainWindowResources&& resources) = delete;

    static const Resources& GetInstance();
};

#endif
