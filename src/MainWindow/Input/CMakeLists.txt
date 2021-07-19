cmake_minimum_required (VERSION 3.16)

project (Input)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(Input Input.cpp Input.hpp)
target_link_libraries(Input Qt::Gamepad)