#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main(int argv, const char * argc[]) {
  Mat img;
  if (argv > 1) {
    img = imread(argc[1]);
  } else {
    img = imread("../lena.jpg");
  }
  if (img.empty()) {
    std::cout << "Unable open image" << std::endl;
    return 1;
  }
  Mat grayimg;
  cvtColor(img, grayimg, COLOR_BGR2GRAY);

  auto size = grayimg.size();
  std::cout << "size of image: " << size << std::endl;
  int scale = 2;
  Size rsize(size.width * scale, size.height * scale);

  Mat dst1, dst2, dst3, dst4;

  resize(grayimg, dst1, rsize, 0, 0, INTER_NEAREST); // 最近邻内插
  resize(grayimg, dst2, rsize, 0, 0, INTER_LINEAR);  // 双线性内插
  resize(grayimg, dst3, rsize, 0, 0, INTER_CUBIC);   // 三次样条内插
  resize(grayimg, dst4, rsize, 0, 0, INTER_LANCZOS4);// Lanczos 内插

  imshow("origional", grayimg);
  imshow("INTER_NEAREST", dst1);
  imshow("INTER_LINEAR", dst2);
  imshow("INTER_CUBIC", dst3);
  imshow("INTER_LANCZOS4", dst4);

  waitKey(0);
  return 0;
}
