project (Widgets)

add_subdirectory(RobotSettings)

add_library(Widgets Widgets.cpp)

target_link_libraries(Widgets ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(Widgets RobotSettings)
