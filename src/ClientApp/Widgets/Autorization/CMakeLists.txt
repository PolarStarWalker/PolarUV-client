project(Autorization)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(Autorization AutorizationWidget.hpp AutorizationWidget.cpp)

target_link_libraries(Autorization ${REQUIRED_LIBS_QUALIFIED})