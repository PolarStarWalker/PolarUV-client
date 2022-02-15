project(Commands)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(Commands CommandsWidget.cpp CommandsWidget.hpp Gamepad.hpp Gamepad.cpp)

target_link_libraries(Commands ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(Commands XInput DSound)