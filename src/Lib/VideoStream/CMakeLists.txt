project(VideoStream)

#do some cmake-protobug magic
find_package(Protobuf REQUIRED)

#compile .proto to c++ code
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS VideoStreamMessage.proto)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(VideoStream ${PROTO_SRCS} ${PROTO_HDRS} VideoStream.hpp VideoStream.cpp)

target_link_libraries(VideoStream ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(VideoStream ${OpenCV_LIBS} )