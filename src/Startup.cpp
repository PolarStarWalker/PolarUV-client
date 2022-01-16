#include "Startup.hpp"


int main(int argc, char *argv[]) {
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

    lib::Setup();

//    lib::logger::info << "а вот это информация" << std::endl;
//    lib::logger::warning << "это предупреждение" << std::endl;
//    lib::logger::error << "это ошибка" << std::endl;
//    lib::logger::critical << "Для обработки экзепшенов" << std::endl;

    std::cout << "предыдущая фигня должна была вывести стектрейс, которого почему-то нет" <<std::endl;

    std::clog << "test" << std::endl;

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setSamples(8);
    surfaceFormat.setSwapBehavior(QSurfaceFormat::SingleBuffer);
    QSurfaceFormat::setDefaultFormat(surfaceFormat);

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return QApplication::exec();
}
