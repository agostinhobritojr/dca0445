#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat image;
  VideoCapture cap;
  cap.open("MyVideo.mp4");
  while(1){
	cap.read(image);
	imshow("webcam", image);
	if(waitKey(30) >= 0) break;
  }
  return 0;
}
