cmake_minimum_required (VERSION 3.16)

project (MainWindow)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


add_library(MainWindow MainWindow.cpp MainWindow.hpp UI/Shortcuts.cpp UI/Buttons.cpp UI/Rendering.cpp UI/Actions.cpp UI/Resources.cpp UI/Indicators.cpp UI/Animations.cpp)
target_link_libraries(MainWindow ${REQUIRED_LIBS_QUALIFIED})

add_subdirectory(Protocols)
add_subdirectory(Gamepad)
add_subdirectory(DataStructs)
add_subdirectory(ExceptionHandler)
add_subdirectory(Exceptions)


target_link_libraries(MainWindow Protocols)
target_link_libraries(MainWindow Gamepad)
target_link_libraries(MainWindow ExceptionHandler)
target_link_libraries(MainWindow Exceptions)
target_link_libraries(MainWindow DataStructs)

target_link_libraries(MainWindow iphlpapi)
