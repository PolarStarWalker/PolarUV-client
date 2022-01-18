project (Widgets)

add_subdirectory(RobotSettings)
add_subdirectory(ClientSettings)
add_subdirectory(PythonEnvironment)

add_library(Widgets Widgets.cpp)

target_link_libraries(Widgets ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(Widgets RobotSettings)
target_link_libraries(Widgets ClientSettings)
target_link_libraries(Widgets PythonEnvironment)
