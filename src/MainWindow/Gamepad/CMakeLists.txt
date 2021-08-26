project(Gamepad)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(Gamepad Gamepad.cpp Gamepad.hpp)

SET(LIBS XInput DSound)
TARGET_LINK_LIBRARIES(Gamepad ${LIBS})