project (ClientApp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(ClientApp MainWindow.cpp MainWindow.hpp UI/Slots.cpp UI/Rendering.cpp UI/WidgetResources.cpp UI/Indicators.cpp)
target_link_libraries(ClientApp ${REQUIRED_LIBS_QUALIFIED})

include_directories(./Widgets)

add_subdirectory(Widgets)

target_link_libraries(ClientApp Widgets)

target_link_libraries(ClientApp iphlpapi)
