#ifndef CLIENT_INPUT_HPP
#define CLIENT_INPUT_HPP
#include <QGamepad>
#include "../../DataStruct.hpp"

class Input{
public:
    Input();
    ~Input();
    CommandsStruct GetCommandsStruct();

class Gamepad{
public:

private:

};

private:
QGamepad* _qGamepad = nullptr;

    static inline float GasFunction(double);
};


#endif
