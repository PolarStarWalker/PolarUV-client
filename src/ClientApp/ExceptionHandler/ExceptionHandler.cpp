#include "ExceptionHandler.hpp"

ExceptionHandler::ExceptionHandler(MainWindow *object, std::function<void(MainWindow *object)> function,
                                   const QString &successTitle,
                                   const QString &successMessage) {
    try {
        function(object);
        if (!(successTitle == nullptr) && !(successMessage == nullptr)) {
            QMessageBox::about(object, successTitle, successMessage);
        }
    } catch (const Exception::ConnectionException &exception) {
        QMessageBox::warning(object, exception.GetError().c_str(), exception.GetDetails().c_str());

    } catch (const Exception::InvalidOperationException &invalidOperation) {
        QMessageBox::information(object, invalidOperation.GetError().c_str(), invalidOperation.GetDetails().c_str());

    } catch (...) {
        QMessageBox::critical(object, "Неизвестная ошибка", "Неизвестная ошибка");
    }
}
