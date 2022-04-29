#include "Startup.hpp"

int main(int argc, char *argv[]) {

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setSamples(4);
    surfaceFormat.setSwapBehavior(QSurfaceFormat::SingleBuffer);
    QSurfaceFormat::setDefaultFormat(surfaceFormat);

    lib::Setup();

    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}
