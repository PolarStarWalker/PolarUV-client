project (RobotSettings)

#do some cmake-protobug magic
find_package(Protobuf REQUIRED)

#compile .proto to c++ code
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS RobotSettingsMessage.proto)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(RobotSettings ${PROTO_SRCS} ${PROTO_HDRS} RobotSettingsWidget.hpp RobotSettingsWidget.cpp RobotSettingsWidgetActions.cpp)

target_link_libraries(RobotSettings ${REQUIRED_LIBS_QUALIFIED})