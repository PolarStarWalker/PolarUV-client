#include "Lib.hpp"
namespace lib {
    extern "C" {
    void Setup() {
        SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
        logger::Setup();
        InitGstreamer();
    }
    }
}