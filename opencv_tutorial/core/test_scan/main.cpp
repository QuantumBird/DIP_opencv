#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#define CNT_TIME(funcall) {\
  double __srt__  = static_cast<double>(getTickCount());\
  funcall;\
  double __end__  = static_cast<double>(getTickCount());\
  double __tot__  = (__end__ - __srt__) / getTickFrequency();\
  cout << #funcall << " used times: " << __tot__ << "s"<<endl;\
}
using namespace std;
using namespace cv;

const int SIZE = 256;
uchar table[SIZE];
void geneTable() {
  for (int i = 0; i < SIZE; i ++) {
    table[i] = 10 * (i / 10);
  }
}

void pointer_scan(Mat & m) {
  int channels  = m.channels();
  int nRows     = m.rows * channels;
  int nCols     = m.cols;
  if (m.isContinuous()) {
    nCols *= nRows;
    nRows = 1;
  }
  for (int i = 0; i < nRows; i ++) {
    uchar * p = m.ptr<uchar>(i);
    for (int j = 0; j < nCols; j ++) {
      p[j] = table[p[j]];
    }
  }
}

void iterator_scan(Mat & m) {
  const int channels = m.channels();
  switch(channels) {
    case 1: {
        MatIterator_<uchar> it, end = m.end<uchar>();
        for (it = m.begin<uchar>(); it != end; it ++) {
          (*it) = table[(*it)];
        }
        break;
      }
    case 3: {
        MatIterator_<Vec3b> it, end = m.end<Vec3b>();
        for (it = m.begin<Vec3b>(); it != end; it ++) {
          for (int t = 0; t < 3; t ++) {
            (*it)[t] = table[(*it)[t]];
          }
        }
        break;
      }
  }
}
int main(int argc, const char * argv[]) {
  string filename = "../lena.jpg";
  if (argc > 1) {
    filename = string(argv[1]);
  }
  Mat img = imread(filename);
  Mat gimg;
  cvtColor(img, gimg, COLOR_BGR2GRAY);
  geneTable();
  imshow("origional", gimg);

  Mat pimg = gimg.clone();
  CNT_TIME(pointer_scan(pimg));
  imshow("pointer scanned", pimg);

  Mat iimg = gimg.clone();
  CNT_TIME(iterator_scan(iimg));
  imshow("iterator scanned", iimg);
  waitKey(0);
  return 0;
}
// TODO:  finish .at<uchar> speed test
//        and LUT speed test
