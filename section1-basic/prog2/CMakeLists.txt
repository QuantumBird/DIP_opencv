cmake_minimum_required(VERSION 3.12)
project(test_image_add)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(test_image_add main.cpp)
target_link_libraries(test_image_add ${OpenCV_LIBS})

