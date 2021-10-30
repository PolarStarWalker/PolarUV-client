Project(Lib)

ADD_SUBDIRECTORY(Client)

add_library(Lib Lib.hpp)

target_link_libraries(Lib STATIC SocketClient)