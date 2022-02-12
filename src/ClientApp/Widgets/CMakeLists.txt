project (Widgets)

add_subdirectory(Authorization)
add_subdirectory(RobotSettings)
add_subdirectory(ClientSettings)
add_subdirectory(PythonEnvironment)
add_subdirectory(Display)
add_subdirectory(Commands)

add_library(Widgets Widgets.hpp Widgets.cpp )

target_link_libraries(Widgets Authorization)
target_link_libraries(Widgets RobotSettings)
target_link_libraries(Widgets ClientSettings)
target_link_libraries(Widgets PythonEnvironment)
target_link_libraries(Widgets Commands)
target_link_libraries(Widgets Display)

target_link_libraries(Widgets ${REQUIRED_LIBS_QUALIFIED})