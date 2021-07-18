#include "Socket.hpp"

///ToDo: строка это так-то тяжёлая штука, лучше передавать её по константной ссылке
/// (если у нас есть гарантия что строка в процессе выполнения функции не изменится извне)
bool Socket::ConnectToServer(const QString &address, uint16_t port) {
    ///lock_guard в конструкторе захватывает мьютекс и лочит его, в деструктуре разлочивает
    ///(без него не получистя, ибо нужно разлочить мьютекс после return, когда совершён выход из функции)
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.connectToHost(address, port);
    this->_isOnline = _qTcpSocket.waitForConnected();
    return this->_isOnline;
}

void Socket::Disconnect() {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.disconnectFromHost();
    this->_isOnline = false;
}

///ToDo: ну типа поле называется isOnline, а метод нет. Было бы удобнее если бы метод назывался IsOnline
/// А ещё нужно добавить константность, мол  мы ничего в объекте не меняем
bool Socket::IsOnline() const {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    return this->_isOnline;
}

///ToDo: крч, функция waitForBytesWritten возвращает false в случае если сокет наебнулся
/// поэтому я думаю стоит менять _isOnline по этой функции (не возвращать, а менять состояние)
/// кста, тут тоже лучше передовать строку по константной ссылке
void Socket::SendCommand(const QByteArray &command) {
    std::lock_guard<std::mutex> guard(this->_socketMutex);
    this->_qTcpSocket.write(command);
    this->_isOnline = this->_qTcpSocket.waitForBytesWritten();
}