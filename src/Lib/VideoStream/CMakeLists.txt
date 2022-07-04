project(VideoStream)

set(VIDEO_LIBRARIES gstd3d11 gstd3d11-1.0 d3d11 dxguid dxgi Ole32 Oleaut32 Imm32 Winmm Version gstvideo-1.0 gstcodecs-1.0 gstcodecparsers-1.0 )

#do some cmake-protobug magic
find_package(Protobuf REQUIRED)

#compile .proto to c++ code
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS VideoStreamMessage.proto)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(VideoStream ${PROTO_SRCS} ${PROTO_HDRS} VideoStream.hpp VideoStream.cpp Gstreamer.cpp)

target_link_libraries(VideoStream ${CONAN_LIBS})
target_link_libraries(VideoStream ${GST_LIBRARIES})
target_link_libraries(VideoStream ${VIDEO_LIBRARIES})
target_link_libraries(VideoStream ${REQUIRED_LIBS_QUALIFIED})
