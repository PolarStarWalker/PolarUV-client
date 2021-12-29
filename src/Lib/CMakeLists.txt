Project(Lib)

add_subdirectory(Protocols)
add_subdirectory(Gamepad)
add_subdirectory(Exceptions)
add_subdirectory(TcpSession)
add_subdirectory(DataStructs)

add_library(Lib Lib.hpp Lib.cpp)

target_link_libraries(Lib Protocols)
target_link_libraries(Lib Gamepad)
target_link_libraries(Lib Exceptions)
target_link_libraries(Lib TcpSession)
target_link_libraries(Lib DataStructs)
