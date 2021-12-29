project(ExceptionHandler)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(ExceptionHandler ExceptionHandler.cpp ExceptionHandler.hpp)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})