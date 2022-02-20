project(CommandsSettings)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(CommandsSettings CommandsSettingsWidget.hpp CommandsSettingsWidget.cpp)

target_link_libraries(CommandsSettings ${REQUIRED_LIBS_QUALIFIED})