cmake_minimum_required (VERSION 3.16)

project ("DataProtocol")

add_library(DataProtocol DataProtocol.cpp DataProtocol.hpp)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
