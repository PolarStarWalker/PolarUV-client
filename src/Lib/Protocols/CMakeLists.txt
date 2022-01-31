cmake_minimum_required (VERSION 3.16)

project ("Protocols")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(Protocols ./CommandsProtocol/CommandsProtocol.hpp CommandsProtocol.cpp  Socket.cpp Protocols.hpp VideoProtocol.cpp)


target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
