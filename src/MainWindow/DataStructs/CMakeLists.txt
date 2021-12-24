project (DataStructs)

#do some cmake-protobug magic
find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(Client INTERFACE ${CMAKE_CURRENT_BINARY_DIR})

#compile .proto to c++ code
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ClientSettings/ClientSettingsMessage.proto)

set(ClientSettings ClientSettingsDto.cpp)

add_library(DataStructs ${PROTO_SRCS} ${PROTO_HDRS} ${ClientSettings} ${ClientSettingsStruct} CommandsStruct.cpp RobotSettingsStruct.cpp  MotorsStruct.cpp VideoPipelineStruct.cpp)

#file(COPY ${PROTO_HDRS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/ProtoHeaders)

target_link_libraries(DataStructs ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(DataStructs ${CONAN_LIBS})


target_precompile_headers(DataStructs PUBLIC DataStructs.hpp)