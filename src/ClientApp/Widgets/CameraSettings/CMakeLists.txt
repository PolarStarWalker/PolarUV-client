project (CameraSettings)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(CameraSettings CameraSettingsWidget.hpp CameraSettingsWidget.cpp)

target_link_libraries(CameraSettings ${REQUIRED_LIBS_QUALIFIED})