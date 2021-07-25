#ifndef CLIENT_GAMEPAD_HPP
#define CLIENT_GAMEPAD_HPP

#include <memory>
#include <cstring>
#include <cmath>

#include <xinput.h>
#include <minwindef.h>
#include <windows.h>

#include "../DataProtocol/IDataStream.hpp"
#include "../../DataStruct.hpp"

#define MAGIC_NUMBER_ONE 0x7FFF
#define MAGIC_NUMBER_TWO 0xFF

class Gamepad final : public IDataStream{


public:
    explicit Gamepad(size_t id);
    [[nodiscard]] Stream GetStream() const final;
    std::ostream& Print(IDataStream::Stream&) const final;

    void SetVibration(uint16_t left, uint16_t right) const;



private:
    size_t _id;

    [[nodiscard]] CommandsStruct * GetCommandsStruct() const;

    static inline float GasFunction(double X){
        if (X > 0) {
            return 0.278112 * X + 0.06916 * X * X + 0.648397 * X * X * X;
        } else {
            return 0.278112 * X - 0.06916 * X * X + 0.648397 * X * X * X;
        }
    }

};


#endif
