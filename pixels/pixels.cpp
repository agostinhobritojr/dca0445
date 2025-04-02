#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**) {
  cv::Mat image;
  cv::Vec3b val;

  image = cv::imread("bolhas.png", cv::IMREAD_GRAYSCALE);
  if (!image.data) std::cout << "nao abriu bolhas.png" << std::endl;

  cv::namedWindow("janela", cv::WINDOW_NORMAL);

  for (int i = 200; i < 210; i++) {
    for (int j = 10; j < 200; j++) {
      image.at<uchar>(i, j) = 0;
    }
  }

  cv::imshow("janela", image);
  cv::waitKey();

  image = cv::imread("bolhas.png", cv::IMREAD_COLOR);

  val[0] = 0;    // B
  val[1] = 0;    // G
  val[2] = 255;  // R

  for (int i = 200; i < 210; i++) {
    for (int j = 10; j < 200; j++) {
      image.at<cv::Vec3b>(i, j) = val;
    }
  }

  cv::imshow("janela", image);
  cv::waitKey();
  return 0;
}
