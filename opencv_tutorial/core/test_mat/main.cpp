#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main(int argc, const char * argv[]) {
  Mat img;
  if (argc > 1) {
    img = imread(argv[1]);
  } else {
    std::cout << "need more param: image name " << std::endl;
    return 1;
  }
  auto size = img.size();
  Mat half_img = img(
      Rect(0, 0, std::round(size.width / 2), std::round(size.height / 2)));
  imshow("origional", img);
  imshow("half", half_img);
  waitKey(0);

  Mat m(2, 2, CV_8UC3, Scalar(0, 0, 255));
  std::cout << m << std::endl;

  int sz[] = {2, 2, 2};
  Mat L(3, sz, CV_8UC(1), Scalar::all(0));
  std::cout << L.size() << std::endl;

  Mat E = Mat::eye(4, 4, CV_64F);
  std::cout << E << std::endl;
  Mat O = Mat::ones(2, 2, CV_32F);
  std::cout << O << std::endl;
  Mat Z = Mat::zeros(3, 3, CV_8UC1);
  std::cout << Z << std::endl;

  Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  std::cout << "C=" << C << std::endl;

  Mat R = Mat(3, 2, CV_8UC3);
  randu(R, Scalar::all(0), Scalar::all(255));
  std::cout << "R(default)" << std::endl << R << std::endl;
  
  std::cout << "R(python)" << std::endl 
    << format(R, Formatter::FMT_PYTHON) << std::endl;
  
  std::cout << "R(csv)" << std::endl 
    << format(R, Formatter::FMT_CSV) << std::endl;
  
  std::cout << "R(numpy)" << std::endl 
    << format(R, Formatter::FMT_NUMPY) << std::endl;

  std::cout << "R(matlab)" << std::endl 
    << format(R, Formatter::FMT_MATLAB) << std::endl;

  return 0;
}
