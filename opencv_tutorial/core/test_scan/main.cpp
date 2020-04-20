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

void at_scan(Mat & m) {
  const int channels = m.channels();
  switch(channels) {
    case 1: {
        for (int i = 0; i < m.rows; i ++) {
          for (int j = 0; j < m.cols; j ++) {
            m.at<uchar>(i, j) = table[m.at<uchar>(i, j)];
          }
        }
        break;
      }
    case 3: {
      Mat_<Vec3b> _m = m;
      for (int i = 0; i < m.rows; i ++) {
        for (int j = 0; j < m.cols;j ++) {
          for (int k = 0; k < 3; k ++)
            _m(i, j)[k] = table[_m(i, j)[k]];
        }
      }
      break;
    }
  }
}

void lookup_scan(Mat & m) {
  Mat lookup(1, 256, CV_8U);
  uchar * p = lookup.data;
  for (int i = 0; i < SIZE; i ++) 
    p[i] = table[i];
  LUT(m, lookup, m);
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

  Mat aimg = gimg.clone();
  CNT_TIME(at_scan(aimg));
  imshow("at scanned", aimg);
  
  Mat limg = gimg.clone();
  CNT_TIME(lookup_scan(limg));
  imshow("LUT scanned", limg);

  waitKey(0);
  return 0;
}
// TODO:  finish .at<uchar> speed test
//        and LUT speed test
