project (ClientApp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(ClientApp MainWindow.cpp MainWindow.hpp UI/Shortcuts.cpp UI/Buttons.cpp UI/Rendering.cpp UI/Actions.cpp UI/Resources.cpp UI/Indicators.cpp UI/Animations.cpp)
target_link_libraries(ClientApp ${REQUIRED_LIBS_QUALIFIED})

include_directories(./Widgets)

add_subdirectory(ExceptionHandler)
add_subdirectory(Widgets)

target_link_libraries(ClientApp ExceptionHandler)
target_link_libraries(ClientApp Widgets)

target_link_libraries(ClientApp iphlpapi)
