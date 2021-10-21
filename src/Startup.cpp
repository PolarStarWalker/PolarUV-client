#include "Startup.hpp"


int main(int argc, char *argv[]) {

    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setSamples(8);
    surfaceFormat.setSwapBehavior(QSurfaceFormat::SingleBuffer);
    QSurfaceFormat::setDefaultFormat(surfaceFormat);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return QApplication::exec();
}
