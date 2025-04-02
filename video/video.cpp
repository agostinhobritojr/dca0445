#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::VideoCapture cap;
  double width, height;
  cv::Mat frame;
  int counter;

  cap.open(argv[1]);
  if(!cap.isOpened())
  return -1;

  width=cap.get(cv::CAP_PROP_FRAME_WIDTH);
  height=cap.get(cv::CAP_PROP_FRAME_HEIGHT);
  std::cout << "largura=" << width << "\n";
  std::cout << "altura =" << height<< "\n";
  
  cv::Size frameSize(static_cast<int>(width), static_cast<int>(height));
  
  int type = cap.get(cv::CAP_PROP_FOURCC);
  
  cv::VideoWriter out ("output.avi", type, cap.get(cv::CAP_PROP_FPS), frameSize, true);

  for(counter=0; cap.read(frame); counter++){
    out << frame;
    cv::imshow("Frame", frame);
    if(cv::waitKey(30) >= 0) break;
  }
  std::cout << "Numero de frames: " << counter << "\n";
  return 0;
}
