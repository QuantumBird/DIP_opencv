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
#include <string>
#define CNT_TIME(funcall) {\\
  double __srt__ = static_cast<double>(getTickCount());\\
  funcall;\\
  double __end__ = static_cast<double>(getTickCount());\\
  double __tot__ = (__end__ - __srt__) / getTickFrequency();\\
  std::cout << #funcall << "used times: " << __tot__ << "s" << std::endl;\\
}
using namespace cv;
int main(int argv, const char * argc[]) {
  // TODO
  return 0;
}
EOF
mkdir build

