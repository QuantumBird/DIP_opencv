#!/bin/bash
mkdir $1
cd $1

cat>CMakeLists.txt<<EOF
cmake_minimum_required(VERSION 2.8.4)
project($1)
find_package(OpenCV REQUIRED)
include_directories(\${OpenCV_INCLUDE_DIRS})
add_executable($1 main.cpp)
target_link_libraries($1 \${OpenCV_LIBS})
EOF

cat>main.cpp<<EOF
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main(int argv, const char * argc[]) {
  // TODO
  return 0;
}
EOF
mkdir build

