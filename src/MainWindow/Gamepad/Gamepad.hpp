#ifndef CLIENT_GAMEPAD_HPP
#define CLIENT_GAMEPAD_HPP

#include <memory>
#include <cstring>
#include <cmath>
#include <list>

#include <xinput.h>
#include <minwindef.h>
#include <windows.h>

#include "../DataProtocol/IDataStream.hpp"
#include "../../DataStruct.hpp"

#define MAGIC_NUMBER_ONE 0x7FFF
#define MAGIC_NUMBER_TWO 0xFF

namespace Control {

    namespace {

        enum ButtonMask : DWORD {
            DPadUp = XINPUT_GAMEPAD_DPAD_UP,
            DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
            DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
            DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
            Start = XINPUT_GAMEPAD_START,
            Stop = XINPUT_GAMEPAD_BACK,
            LeftStick = XINPUT_GAMEPAD_LEFT_THUMB,
            RightStick = XINPUT_GAMEPAD_RIGHT_THUMB,
            LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
            RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
            Cross = XINPUT_GAMEPAD_A,
            Circle = XINPUT_GAMEPAD_B,
            Rectangle = XINPUT_GAMEPAD_X,
            Triangle = XINPUT_GAMEPAD_Y
        };

        class ButtonsStates {
        private:

            [[nodiscard]] inline bool GetButtonState(ButtonMask mask) const {
                return this->state & mask;
            }

            inline void ChangeButtonState(ButtonMask mask){
                this->state = (this->state & ~mask) | ( ~(this->state & mask));
            }

            DWORD state;

        public:
            [[nodiscard]] inline bool IsDPadUpPressed() const {
                return GetButtonState(DPadUp);
            }

            [[nodiscard]] inline bool IsDPadDownPressed() const {
                return GetButtonState(DPadDown);
            }

            [[nodiscard]] inline bool IsDPadLeftPressed() const {
                return GetButtonState(DPadLeft);
            }

            [[nodiscard]] inline bool IsDPadRightPressed() const {
                return GetButtonState(DPadRight);
            }

            [[nodiscard]] inline bool IsTrianglePressed() const {
                return GetButtonState(Triangle);
            }

            [[nodiscard]] inline bool IsRectanglePressed() const {
                return GetButtonState(Rectangle);
            }

            [[nodiscard]] inline bool IsCrossPressed() const {
                return GetButtonState(Cross);
            }

            [[nodiscard]] inline bool IsCirclePressed() const {
                return GetButtonState(Circle);
            }

            [[nodiscard]] inline bool IsStartPressed() const {
                return GetButtonState(Start);
            }

            [[nodiscard]] inline bool IsStopPressed() const {
                return GetButtonState(Stop);
            }

            [[nodiscard]] inline bool IsLeftStickPressed() const {
                return GetButtonState(LeftStick);
            }

            [[nodiscard]] inline bool IsRightStickPressed() const {
                return GetButtonState(RightStick);
            }

            [[nodiscard]] inline bool IsLeftShoulderPressed() const {
                return GetButtonState(LeftShoulder);
            }

            [[nodiscard]] inline bool IsRightShoulderPressed() const {
                return GetButtonState(RightShoulder);
            }

            inline void ChangeDPadUpState() {
                ChangeButtonState(DPadUp);
            }

            inline void ChangeDPadDownState() {
                ChangeButtonState(DPadDown);
            }

            inline void ChangeDPadLeftState() {
                ChangeButtonState(DPadLeft);
            }

            inline void ChangeDPadRightState() {
                ChangeButtonState( DPadRight);
            }

            inline void ChangeTriangleState() {
                ChangeButtonState(Triangle);
            }

            inline void ChangeRectangleState() {
                ChangeButtonState(Rectangle);
            }

            inline void ChangeCrossState() {
                ChangeButtonState(Cross);
            }

            inline void ChangeCircleState() {
                ChangeButtonState(Circle);
            }

            inline void ChangeStartState() {
                ChangeButtonState(Start);
            }

            inline void ChangeStopState() {
                ChangeButtonState(Stop);
            }

            inline void ChangeLeftStickState() {
                ChangeButtonState(LeftStick);
            }

            inline void ChangeRightStickState() {
                ChangeButtonState(RightStick);
            }

            inline void ChangeLeftShoulderState() {
                ChangeButtonState(LeftShoulder);
            }

            inline void ChangeRightShoulderState() {
                ChangeButtonState(RightShoulder);
            }
        };
    }

    std::list<int> GetGamepadsIds();

    class Gamepad final : public IDataStream {
    public:
        explicit Gamepad(size_t id);

        [[nodiscard]] Stream GetStream() const final;

        std::ostream &Print(IDataStream::Stream &) const final;

        void SetVibration(uint16_t left, uint16_t right) const;


    private:
        size_t _id;
        ButtonsStates buttonsStates;


        [[nodiscard]] CommandsStruct *GetCommandsStruct() const;

        static inline float GasFunction(double X) {
            if (X > 0) {
                return 0.278112 * X + 0.06916 * X * X + 0.648397 * X * X * X;
            } else {
                return 0.278112 * X - 0.06916 * X * X + 0.648397 * X * X * X;
            }
        }

    };
}


#endif
