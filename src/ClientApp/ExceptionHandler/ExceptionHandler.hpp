#ifndef CLIENT_EXCEPTIONHANDLER_HPP
#define CLIENT_EXCEPTIONHANDLER_HPP

#include <QMessageBox>
#include <functional>

#include "../MainWindow.hpp"

class ExceptionHandler {
public:
    ExceptionHandler(MainWindow *object,
                     std::function<void(MainWindow *object)> function,
                     const QString &successTitle,
                     const QString &successMessage);
};


#endif
