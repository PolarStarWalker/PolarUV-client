project (SensorsSettings)

add_library(SensorsSettings SensorsWidget.hpp SensorsWidget.cpp)

target_link_libraries(SensorsSettings ${REQUIRED_LIBS_QUALIFIED})