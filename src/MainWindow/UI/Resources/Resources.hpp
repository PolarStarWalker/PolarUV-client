#ifndef CLIENT_RESOURCES_HPP
#define CLIENT_RESOURCES_HPP

#include <QPixmap>
#include <QIcon>

class Resources {

public:
    Resources();

    QPixmap *background;

    QIcon *cameraIcon;
    QIcon *robotIcon;
    QIcon *clientIcon;
    QIcon *codeIcon;
    QIcon *fullScreenIcon;
    QIcon *showTabBarIcon;
    QIcon *hideTabBarIcon;
    QIcon *screenshotIcon;
    QIcon *whiteVideoIcon;
    QIcon *reloadIcon;
    QIcon *bugIcon;
    QIcon *greenStartIcon;
    QIcon *redStartIcon;
    QIcon *pauseIcon;
    QIcon *playIcon;
};

#endif //CLIENT_RESOURCES_HPP
