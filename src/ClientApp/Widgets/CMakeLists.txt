project (Widgets)

add_subdirectory(Authorization)
add_subdirectory(MoveSettings)
add_subdirectory(CommandsSettings)
add_subdirectory(PythonEnvironment)
add_subdirectory(Display)
add_subdirectory(Commands)
add_subdirectory(Sensors)
add_subdirectory(SensorsSettings)

add_library(Widgets Widgets.hpp Widgets.cpp)

target_link_libraries(Widgets Authorization)
target_link_libraries(Widgets MoveSettings)
target_link_libraries(Widgets CommandsSettings)
target_link_libraries(Widgets PythonEnvironment)
target_link_libraries(Widgets Commands)
target_link_libraries(Widgets Display)
target_link_libraries(Widgets Sensors)
target_link_libraries(Widgets SensorsSettings)


target_link_libraries(Widgets ${REQUIRED_LIBS_QUALIFIED})