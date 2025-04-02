cmake_minimum_required(VERSION 3.0.0)
project(video VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(video video.cpp)
target_link_libraries(video ${OpenCV_LIBS})
