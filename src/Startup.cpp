#include "Startup.hpp"

int main(int argc, char *argv[]) {

    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

    QApplication app(argc, argv);

    lib::Setup();

    MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}
