#ifndef CLIENT_GAMEPAD_HPP
#define CLIENT_GAMEPAD_HPP

#include <memory>
#include <cstring>

#include <xinput.h>
#include <minwindef.h>
#include <windows.h>

//#include "../DataProtocol/IDataStream.hpp"
#include "../../DataStruct.hpp"

#define MAGIC_NUMBER_ONE 0x7FFF
#define MAGIC_NUMBER_TWO 0xFF

class Gamepad{


public:
    Gamepad(size_t id);
    ~Gamepad();
    CommandsStruct GetCommandsStruct() const;
    void SetVibration(uint16_t left, uint16_t right) const;

private:
    size_t _id;

    static inline float GasFunction(double){

    }

};


#endif
