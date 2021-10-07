#ifndef CLIENT_MAIN_WINDOW_RESOURCES_HPP
#define CLIENT_MAIN_WINDOW_RESOURCES_HPP

#include <QPixmap>
#include <QIcon>

class MainWindowResources {
private:
    struct Resources {
        QPixmap Background;
        QIcon CameraIcon;
        QIcon RobotIcon;
        QIcon ClientIcon;
        QIcon CodeIcon;
        QIcon FullScreenIcon;
        QIcon ShowTabBarIcon;
        QIcon HideTabBarIcon;
        QIcon ScreenshotIcon;
        QIcon WhiteVideoIcon;
        QIcon ReloadIcon;
        QIcon BugIcon;
        QIcon GreenStartIcon;
        QIcon RedStartIcon;
        QIcon PauseIcon;
        QIcon PlayIcon;
        QIcon ApplicationIcon;
        QIcon WindowIcon;
    };

    MainWindowResources();

    Resources *_resources;

public:

    ~MainWindowResources();

    static MainWindowResources *GetInstance() {
        static MainWindowResources instance;
        return &instance;
    }

    inline const QPixmap &GetBackground() {
        return this->_resources->Background;
    }

    inline const QIcon &GetMainWindowIcon() {
        return this->_resources->WindowIcon;
    }

    inline const QIcon &GetCameraIcon() {
        return this->_resources->CameraIcon;
    }

    inline const QIcon &GetRobotIcon() {
        return this->_resources->RobotIcon;
    }

    inline const QIcon &GetClientIcon() {
        return this->_resources->ClientIcon;
    }

    inline const QIcon &GetCodeIcon() {
        return this->_resources->CodeIcon;
    }

    inline const QIcon &GetFullScreenIcon() {
        return this->_resources->FullScreenIcon;
    }

    inline const QIcon &GetShowTabBarIcon() {
        return this->_resources->ShowTabBarIcon;
    }

    inline const QIcon &GetHideTabBarIcon() {
        return this->_resources->HideTabBarIcon;
    }

    inline const QIcon &GetScreenshotIcon() {
        return this->_resources->ScreenshotIcon;
    }

    inline const QIcon &GetWhiteVideoIcon() {
        return this->_resources->WhiteVideoIcon;
    }

    inline const QIcon &GetReloadIcon() {
        return this->_resources->ReloadIcon;
    }

    inline const QIcon &GetBugIcon() {
        return this->_resources->BugIcon;
    }

    inline const QIcon &GetGreenStartIcon() {
        return this->_resources->GreenStartIcon;
    }

    inline const QIcon &GetRedStartIcon() {
        return this->_resources->RedStartIcon;
    }

    inline const QIcon &GetPauseIcon() {
        return this->_resources->PauseIcon;
    }

    inline const QIcon &GetPlayIcon() {
        return this->_resources->PlayIcon;
    }

    inline const QIcon &GetApplicationIcon() {
        return this->_resources->ApplicationIcon;
    }

};

#endif
