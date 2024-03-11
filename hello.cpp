#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::Mat image;
  image = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
  cv::imshow("image", image);
  cv::waitKey();
  return 0;
}
