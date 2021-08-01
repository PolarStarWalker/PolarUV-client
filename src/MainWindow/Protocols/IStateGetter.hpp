#ifndef CLIENT_ISTATEGETTER_HPP
#define CLIENT_ISTATEGETTER_HPP

#include <QObject>

class IStateGetter: QObject {
    Q_OBJECT

public:
    virtual void SetState() = 0;

};


#endif
