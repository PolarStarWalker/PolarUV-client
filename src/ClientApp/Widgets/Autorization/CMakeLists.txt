project(Autorization)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(Autorization AuthorizationWidget.hpp AuthorizationWidget.cpp IPFunction.hpp)

target_link_libraries(Autorization ${REQUIRED_LIBS_QUALIFIED})

if (WIN32)
    #do something
endif (WIN32)