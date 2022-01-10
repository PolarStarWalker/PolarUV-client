project (Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#do some cmake-protobug magic
find_package(Protobuf REQUIRED)

#compile .proto to c++ code
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS RobotSettings/RobotSettingsMessage.proto)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(Widgets ${PROTO_SRCS} ${PROTO_HDRS} Widgets.hpp RobotSettings RobotSettingsWidget.cpp)

target_link_libraries(Widgets ${REQUIRED_LIBS_QUALIFIED})

