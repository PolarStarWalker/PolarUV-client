project (VideoStream)

add_library(VideoStream VideoStreamWidget.hpp SensorsWidget.cpp)

target_link_libraries(VideoStream ${REQUIRED_LIBS_QUALIFIED})