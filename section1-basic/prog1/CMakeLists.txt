cmake_minimum_required(VERSION 2.8.4)
project(test_resize)

find_package(OpenCV REQUIRED)
#link_directories(${OpenCV_LIBS_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(test_resize main.cpp)
target_link_libraries(test_resize ${OpenCV_LIBS})

