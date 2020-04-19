#include <<opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace cv;

Mat geneGaussian(Size size, double mean, double stdv);

int main(int argv, const char * argc[]) {
  Mat img;
  string img_name = "../lena.jpg";
  int num = 3;
  if (argv > 1) {
    num = std::atoi(argc[1]);
    if (argv > 2)
      img_name = string(argc[1]);
  }
  img = imread(filename);
  if (img.empty()) {
    std::cout << "unable to open " << filename << std::endl;
    return 1;
  }

  return 0;
}
