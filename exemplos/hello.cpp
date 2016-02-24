#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;

int main(int argc, char** argv){
  Mat image;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  imshow("image", image);
  waitKey();
  return 0;
}
