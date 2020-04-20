#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#define CNT_TIME(funcall) {\
  double __srt__ = static_cast<double>(getTickCount());\
  funcall;\
  double __end__ = static_cast<double>(getTickCount());\
  double __tot__ = (__end__ - __srt__) / getTickFrequency();\
  std::cout << #funcall << "used times: " << __tot__ << "s" << std::endl;\
}
using namespace cv;
int main(int argv, const char * argc[]) {
  // TODO
  return 0;
}
