cmake_minimum_required (VERSION 3.16)

project (Input)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(Input Gamepad.cpp Gamepad.hpp)

SET( LIBS XInput DSound)
TARGET_LINK_LIBRARIES(Input ${LIBS} )