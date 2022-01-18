project (ClientSettings)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(ClientSettings ClientSettingsWidget.hpp ClientSettingsWidget.cpp)

target_link_libraries(ClientSettings ${REQUIRED_LIBS_QUALIFIED})