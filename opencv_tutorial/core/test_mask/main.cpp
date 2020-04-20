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

void sharpen(const Mat & img, Mat & result) {
  CV_Assert(img.depth() == CV_8U);
  result.create(img.size(), img.type());
  const int nChannels = img.channels();
  for (int j = 1; j < img.rows; j ++) {
    const uchar * prev = img.ptr<uchar>(j - 1);
    const uchar * curr = img.ptr<uchar>(j);
    const uchar * next = img.ptr<uchar>(j + 1);

    uchar * rest = result.ptr<uchar>(j);

    for (int i = nChannels; i < nChannels * (img.cols - 1); i ++) {
      *rest++ = saturate_cast<uchar>(
          5 * curr[i] - curr[i - nChannels] - curr[i + nChannels] - prev[i] - next[i]
      );
    }
  }
  result.row(0).setTo(Scalar(0));
  result.row(result.rows - 1).setTo(Scalar(0));
  result.col(0).setTo(Scalar(0));
  result.col(result.cols - 1).setTo(Scalar(0));
}

int main(int argv, const char * argc[]) {
  Mat img, gimg, res;
  if (argv < 2) {
    std::cout << "need more param" << std::endl;
    return 1;
  }
  img = imread(argc[1]);
  cvtColor(img, gimg, COLOR_BGR2GRAY);
  CNT_TIME(sharpen(gimg, res));

  Mat kern = (Mat_<char>(3, 3) << 0, -1, 0,
                                  -1, 5, -1,
                                  0, -1, 0);

  Mat res2;
  CNT_TIME(filter2D(gimg, res2, gimg.depth(), kern));
  //imshow("filter2D", res2);

  //imshow("origional", gimg);
  //imshow("proecssed", res);
  //waitKey(0);
  return 0;
}
