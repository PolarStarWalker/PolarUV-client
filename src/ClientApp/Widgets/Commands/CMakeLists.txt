project(Commands)

add_library(Commands CommandsWidget.cpp CommandsWidget.hpp)

target_link_libraries(Commands ${REQUIRED_LIBS_QUALIFIED})