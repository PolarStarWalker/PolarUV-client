cmake_minimum_required (VERSION 3.16)

project (MainWindow)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


add_library(MainWindow MainWindow.cpp MainWindow.hpp)
target_link_libraries(MainWindow ${REQUIRED_LIBS_QUALIFIED})

add_subdirectory(Protocols)
add_subdirectory(Gamepad)
add_subdirectory(DataStructs)

target_link_libraries(MainWindow Protocols)
target_link_libraries(MainWindow Gamepad)
target_link_libraries(MainWindow DataStructs)

