#include <opencv2/opencv.hpp>
#include <vector>

typedef std::vector<std::vector<int>> ResolutionList;

std::vector<std::vector<int>> getResolutions(int camera, int verbose = 0) {
  std::vector<std::vector<int>> supportedResolutions;
  std::vector<std::vector<int>> standardResolutions = {
      {160, 120},   {192, 144},    {256, 144},   {240, 160},   {320, 240},
      {360, 240},   {384, 240},    {400, 240},   {432, 240},   {480, 320},
      {480, 360},   {640, 360},    {600, 480},   {640, 480},   {720, 480},
      {768, 480},   {800, 480},    {854, 480},   {960, 480},   {675, 540},
      {960, 540},   {720, 576},    {768, 576},   {1024, 576},  {750, 600},
      {800, 600},   {1024, 600},   {960, 640},   {1024, 640},  {1136, 640},
      {960, 720},   {1152, 720},   {1280, 720},  {1440, 720},  {960, 768},
      {1024, 768},  {1152, 768},   {1280, 768},  {1366, 768},  {1280, 800},
      {1152, 864},  {1280, 864},   {1536, 864},  {1200, 900},  {1440, 900},
      {1600, 900},  {1280, 960},   {1440, 960},  {1536, 960},  {1280, 1024},
      {1600, 1024}, {1400, 1050},  {1680, 1050}, {1440, 1080}, {1920, 1080},
      {2160, 1080}, {2280, 1080},  {2560, 1080}, {2048, 1152}, {1500, 1200},
      {1600, 1200}, {1920, 1200},  {1920, 1280}, {2048, 1280}, {1920, 1440},
      {2160, 1440}, {2304, 1440},  {2560, 1440}, {2880, 1440}, {2960, 1440},
      {3040, 1440}, {3120, 1440},  {3200, 1440}, {3440, 1440}, {5120, 1440},
      {2048, 1536}, {2400, 1600},  {2560, 1600}, {3840, 1600}, {2880, 1620},
      {2880, 1800}, {3200, 1800},  {2560, 1920}, {2880, 1920}, {3072, 1920},
      {2560, 2048}, {2732, 2048},  {3200, 2048}, {2880, 2160}, {3240, 2160},
      {3840, 2160}, {4320, 2160},  {5120, 2160}, {3200, 2400}, {3840, 2400},
      {3840, 2560}, {4096, 2560},  {5120, 2880}, {5760, 2880}, {4096, 3072},
      {7680, 4320}, {10240, 4320},
  };

  cv::VideoCapture cap;
#ifdef __linux__
  cap.open(camera, cv::CAP_V4L2);
#else
  cap.open(camera);
#endif
  supportedResolutions.clear();
  for (size_t i = 0; i < standardResolutions.size(); i++) {
    int w = standardResolutions[i][0];
    int h = standardResolutions[i][1];

    cap.set(cv::CAP_PROP_FRAME_WIDTH, w);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, h);
    int _w = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int _h = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    if (w == _w && h == _h) {
      supportedResolutions.push_back(standardResolutions[i]);
      if (verbose) {
        std::cout << "found " << w << "x" << h << std::endl;
      }
    }
  }
  cap.release();
  return supportedResolutions;
}

int cameraEnumerator() {
  int camera;
  std::vector<int> cameras;

  cv::VideoCapture cap;

  cameras.clear();
  for (int i = 0; i < 10; i++) {
#ifdef __linux__
    cap.open(i, cv::CAP_V4L2);
#else
    cap.open(i);
#endif
    if (cap.isOpened()) {
      cameras.push_back(i);
    }
    cap.release();
  }
  if (cameras.size() == 1) {
    return cameras[0];
  }
  std::cout << "--------------------\n";
  for (size_t i = 0; i < cameras.size(); i++) {
    std::cout << "camera [" << cameras[i] << "] is active" << std::endl;
  }
  std::cout << "--------------------\n";
  std::cout << "select camera to activate: ";
  std::cin >> camera;
  return camera;
}
