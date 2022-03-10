#include "Startup.hpp"

int main(int argc, char *argv[]) {

    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setSamples(4);
    surfaceFormat.setSwapBehavior(QSurfaceFormat::SingleBuffer);
    QSurfaceFormat::setDefaultFormat(surfaceFormat);

    QApplication app(argc, argv);

    lib::Setup();

    MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}
