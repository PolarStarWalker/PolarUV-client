cmake_minimum_required (VERSION 3.16)

project (ClientApp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


add_library(ClientApp MainWindow.cpp MainWindow.hpp UI/Shortcuts.cpp UI/Buttons.cpp UI/Rendering.cpp UI/Actions.cpp UI/Resources.cpp UI/Indicators.cpp UI/Animations.cpp)
target_link_libraries(ClientApp ${REQUIRED_LIBS_QUALIFIED})

add_subdirectory(Protocols)
add_subdirectory(Gamepad)
add_subdirectory(DataStructs)
add_subdirectory(ExceptionHandler)
add_subdirectory(Exceptions)


target_link_libraries(ClientApp Protocols)
target_link_libraries(ClientApp Gamepad)
target_link_libraries(ClientApp ExceptionHandler)
target_link_libraries(ClientApp Exceptions)
target_link_libraries(ClientApp DataStructs)

target_link_libraries(ClientApp iphlpapi)
