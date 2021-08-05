#include "main.hpp"


int main(int argc, char *argv[]) {

    std::cout << SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS) << std::endl;

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return QApplication::exec();
}
