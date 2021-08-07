#include "main.hpp"


int main(int argc, char *argv[]) {

    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return QApplication::exec();
}
