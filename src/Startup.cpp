#include "Startup.hpp"


int main(int argc, char *argv[]) {


    Py_Initialize();

    PyRun_SimpleString("print('Hello!')");

    Py_Finalize();

    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return QApplication::exec();
}
