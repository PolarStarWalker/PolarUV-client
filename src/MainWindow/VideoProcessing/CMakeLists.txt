cmake_minimum_required (VERSION 3.16)

project (VideoProcessing)

add_library(VideoProcessing VideoProcessing.cpp VideoProcessing.hpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})