#include "main.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowState(Qt::WindowFullScreen);
    w.show();

    return QApplication::exec();
}
