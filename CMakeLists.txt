cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DDEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
else ()
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif ()


project(Client)

#путь до gst-launch-1.0.exe
set(GSTREAMER_DIR "/lib/gstreamer-dev/1.0/msvc_x86_64/bin")
link_directories(GSTREAMER_DIR)

# Подключение библиотек python
find_package(Python3 COMPONENTS Interpreter Development)
include_directories(${Python_INCLUDE_DIRS})
include_directories(${Python3_INCLUDE_DIRS})

#чтобы сработало библиотека должна быть в PATH
set(OpenCV_STATIC ON)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#Путь до Qt
set(CMAKE_PREFIX_PATH "/lib/mingw81_64/lib/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Test Gamepad Network)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Opengl32 Qt5::Widgets Qt5::Test Qt5::Network) # Для -l библиотек

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES})