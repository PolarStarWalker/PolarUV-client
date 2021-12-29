Project(Lib)

add_subdirectory(TcpSession)

add_library(Lib Lib.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Lib TcpSession)