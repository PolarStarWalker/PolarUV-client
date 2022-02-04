project(Commands)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(Commands CommandsWidget.cpp CommandsWidget.hpp)

target_link_libraries(Commands ${REQUIRED_LIBS_QUALIFIED})