Project(TcpSession)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(TcpSession TcpSession.cpp TcpSession.hpp)

target_link_libraries(TcpSession ${CONAN_LIBS})
target_link_libraries(TcpSession ${REQUIRED_LIBS_QUALIFIED})

if(MINGW)
    target_link_libraries(TcpSession ws2_32)
endif()