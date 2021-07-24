#include "main.hpp"
#include <QWindow>


int main(int argc, char *argv[]) {

    Gamepad gamepad(1);

    for (size_t j = 0;; j++) {
        CommandsStruct commands = gamepad.GetCommandsStruct();
        std::cout << commands << std::endl;
    }

    /*DWORD dwResult;
    for (DWORD i = 0; i < 2; i++) {
        XINPUT_STATE state{};

        std::memset(&state, 0, sizeof(state));

        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState(i, &state);

        if (dwResult == ERROR_SUCCESS) {

            XINPUT_VIBRATION vibration;
            ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
            vibration.wLeftMotorSpeed = 65535; // use any value between 0-65535 here
            vibration.wRightMotorSpeed = 65535; // use any value between 0-65535 here
            XInputSetState(i, &vibration);

            for (size_t j = 0;; j++) {
                XInputGetState(i, &state);
                std::cout << (uint64_t) state.Gamepad.bLeftTrigger << " : " << j << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        } else {
            std::cout << "bo gg\n";
        }*/

    QApplication a(argc, argv);

    MainWindow w;
    w.show();


    return QApplication::exec();
}
