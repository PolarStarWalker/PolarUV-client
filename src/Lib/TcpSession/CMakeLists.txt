Project(TcpSession)

add_library(TcpSession TcpSession.cpp TcpSession.hpp)

target_link_libraries(TcpSession ${CONAN_LIBS})

if(MINGW)
    target_link_libraries(Client ws2_32)
endif()