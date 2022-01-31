Project(Lib)

add_subdirectory(Protocols)
add_subdirectory(Gamepad)
add_subdirectory(Exceptions)
add_subdirectory(TcpSession)
add_subdirectory(DataStructs)
add_subdirectory(Logger)
add_subdirectory(VideoStream)

add_library(Lib Lib.hpp Lib.cpp)

target_link_libraries(Lib Protocols)
target_link_libraries(Lib Gamepad)
target_link_libraries(Lib Exceptions)
target_link_libraries(Lib TcpSession)
target_link_libraries(Lib DataStructs)
target_link_libraries(Lib Logger)
target_link_libraries(Lib VideoStream)
