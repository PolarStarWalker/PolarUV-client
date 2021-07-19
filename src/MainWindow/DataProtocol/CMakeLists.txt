cmake_minimum_required (VERSION 3.16)

project ("DataProtocol")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(DataProtocol DataProtocol.cpp DataProtocol.hpp Socket.cpp Socket.hpp)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
