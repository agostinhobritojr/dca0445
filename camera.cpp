#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  VideoCapture cap;
  Vec3b val;

  cap.open("MyVideo.avi");
  
  if(!cap.isOpened()){
	printf("nao abriu");
	exit(0);
  }
  int width, height;
  
  width=cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height=cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  
  Size frameSize(width, height);
    
  VideoWriter out ("MyVideoOut.avi",
				   CV_FOURCC('P','I','M','1'),
				   20,
				   frameSize,
				   true);
  
  Mat image, imagegray;
  Mat imagecopia;
  
  namedWindow("image",1);

  val[0] = 0;   //B
  val[1] = 0;   //G
  val[2] = 255; //R

  char tecla;

  for(;;){
	bool ok = cap.read(image);
	
	if(!ok){
	  break;
	}

	out << image;
	
	for(int i=200;i<210;i++){
	  for(int j=10;j<200;j++){
		image.at<Vec3b>(i,j)=val;
	  }
	}
	cvtColor(image, imagegray, CV_BGR2GRAY);
	//	imagegray.copyTo(imagecopia);
	flip(imagegray, imagegray, 1);
	imagecopia = imagegray.clone();
	imshow("image", imagecopia);
	tecla = (char) waitKey(30);
	if(tecla == ' ')
	  break;	
  }
  return 0;
}
