#include "ExceptionHandler.hpp"
#include <Exceptions/Exceptions.hpp>

ExceptionHandler::ExceptionHandler(const std::function<void()> function,
                                   const QString &successTitle,
                                   const QString &successMessage) {
    try {
        function();
    } catch (const Exception::ConnectionException &exception) {
        QMessageBox::warning(nullptr, exception.GetError().c_str(), exception.GetDetails().c_str());
    } catch (const Exception::InvalidOperationException &invalidOperation) {
        QMessageBox::information(nullptr, invalidOperation.GetError().c_str(), invalidOperation.GetDetails().c_str());
    } catch (...) {
        QMessageBox::critical(nullptr, "Неизвестная ошибка", "Неизвестная ошибка");
    }

    if (successTitle != nullptr && successMessage != nullptr)
        QMessageBox::about(nullptr, successTitle, successMessage);

}
