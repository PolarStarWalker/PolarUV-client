#ifndef CLIENT_ISTATE_HPP
#define CLIENT_ISTATE_HPP
#include <QObject>

class IState : QObject{
    Q_OBJECT

public signals:
    virtual bool SetState() = 0;
};


#endif //CLIENT_ISTATE_HPP
