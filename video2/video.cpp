#include <iostream>
#include <opencv2/opencv.hpp>

#include "camera.hpp"

int main(int, char**) {
  cv::VideoCapture cap;
  //  double width, height;
  int key, camera, resolutionId;

  camera = cameraEnumerator();

  std::vector<std::vector<int>> resolutions;
  resolutions = getResolutions(camera);

  cap.open(camera, cv::CAP_V4L2);
  if (!cap.isOpened()) return -1;

  std::cout << "Supported Resolutions: " << std::endl;
  for (size_t i = 0; i < resolutions.size(); i++) {
    std::cout << i << ": " << resolutions[i][0] << "x" << resolutions[i][1]
              << std::endl;
  }

  std::cout << "Choose resolution id: ";
  std::cin >> resolutionId;

  cap.set(cv::CAP_PROP_FRAME_WIDTH, resolutions[resolutionId][0]);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, resolutions[resolutionId][1]);
  cap.set(cv::CAP_PROP_GAIN, 15);
  cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
  std::cout << "fps = " << cap.get(cv::CAP_PROP_FPS) << std::endl;
  std::cout << "buf = " << cap.get(cv::CAP_PROP_BUFFERSIZE) << std::endl;
  cv::Mat edges, frame;
  cv::namedWindow("capture");
  for (;;) {
    if (cap.read(frame)) {
      cv::flip(frame, frame, 1);
      cv::imshow("capture", frame);
    } else {
      std::cout << "." << std::flush;
    }
    key = cv::waitKey(30);
    switch (key) {
      case 27:
        exit(0);
    }
  }

  return 0;
}
