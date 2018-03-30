#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <ctype.h>

using namespace cv;
using namespace std;

static void help(){
  // print a welcome message, and the OpenCV version
  cout << "\nThis is a demo of Lukas-Kanade optical flow lkdemo(),\n"
	"Using OpenCV version %s\n" << CV_VERSION << "\n"
	   << endl;

  cout << "\nHot keys: \n"
	"\tESC - quit the program\n"
	"\tr - auto-initialize tracking\n"
	"\tc - delete all the points\n"
	"\tn - switch the \"night\" mode on/off\n"
	"To add/remove a feature point click it\n" << endl;
}

Point2f point;
bool addRemovePt = false;

static void onMouse( int event, int x, int y, int /*flags*/, void* /*param*/ ){
  if( event == CV_EVENT_LBUTTONDOWN ) {
	point = Point2f((float)x,(float)y);
	addRemovePt = true;
  }
}

int main( int argc, char** argv ){
  VideoCapture cap;
  // criterio de parada para o algoritmo
  // maximo de 20 iteracoes na recursao
  // janela de busca move por menos de 0.03 unidades
  TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03);
  Size winSize(31,31);
  
  const int MAX_COUNT = 500;
  bool needToInit = false;
  bool nightMode = false;

  if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
	cap.open(argc == 2 ? argv[1][0] - '0' : 0);
  else if( argc == 2 )
	cap.open(argv[1]);

  if( !cap.isOpened() )
	{
	  cout << "Could not initialize capturing...\n";
	  return 0;
	}

  help();

  namedWindow( "LK Demo", 1 );
  setMouseCallback( "LK Demo", onMouse, 0 );

  Mat gray, prevGray, image;
  vector<Point2f> points[2];
  float dist, maxdist;
  int count=0;
  needToInit = true;


  float laplacian[]={0,-1,0,
					 -1,4,-1,
					 0,-1,0};
  Mat extended;
  int width, height;
  int originx, originy;

  width=cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height=cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  originx = 15;
  originy = 15;
  extended = Mat(height+2*originy, width+2*originx, CV_8UC3, Scalar(0));
  for(;;){
	Mat frame;
	  cap >> frame;
	  //	  cout << frame.size();
	  flip(frame,frame,1);
	  if( frame.empty() )
		break;

	  frame.copyTo(image);
	  Mat extendedRoi(extended, cv::Rect(originx, originy, width, height));
	  image.copyTo(extendedRoi);
	  extended.copyTo(image);
	  cvtColor(image, gray, CV_BGR2GRAY);
	  imshow("gray",gray);
	  if( nightMode )
		image = Scalar::all(0);

	  count ++;
	  if(count == 5){
		//	needToInit = true;
		count = 0;
	  }
	  if( needToInit ){
		// automatic initialization
		// imagem,,array de pontos,,quality-level (min autovalor), minima distancia entre pontos,,
		// tamanho da janela
		goodFeaturesToTrack(gray,  // imagem
							points[1], // novo array de pontos
							MAX_COUNT, // numero maximo de pontos 
							0.01, // qualidade (valor min para autovalor
							15, // distancia minima entre os pontos
							Mat(), // regiao de interesse (toda)
							3,  // tamanho da regiao para calculo dos autovalores
							0,  // usa detector de harris?
							0.01); // parametro do detector
		addRemovePt = false;
	  }
	  else if( !points[0].empty() )
		{
		  vector<uchar> status;
		  vector<float> err;
		  if(prevGray.empty()){
			gray.copyTo(prevGray);
		  }
		  // calcula o fluxo otico usando uma piramide de imagens
		  calcOpticalFlowPyrLK(prevGray,  // imagem anterior
							   gray,      // imagem atual
							   points[0], // pontos anteriores
							   points[1], // pontos atuais
							   status,    // status de cada ponto 
							   err,       // vetor de erros
							   winSize,   // tamanho da janela de busca
							   3,         // numero de niveis da piramide
							   termcrit,  // criterio de parada
							   0,         // flags nao usados
							   0.001);    // valor minimo do autovalor que pode ser usado
		  size_t i, k;
		  maxdist = 0;
		  for( i = k = 0; i < points[1].size(); i++ ){
			if( addRemovePt ){
			  if( norm(point - points[1][i]) <= 5 ){
				addRemovePt = false;
				continue;
			  }
			}
			   
			if( !status[i] )
			  continue;
			   
			points[1][k++] = points[1][i];
			dist = norm(points[0][i] - points[1][i]);
			if(maxdist < dist)
			  maxdist = dist;
			if(status[i]){
			  line( image, points[1][i], points[0][i], Scalar(0,255,0), 2, 8);
			}
		  }
		  points[1].resize(k);
		}
	  cout << "maxdist = " << maxdist << endl;
	  if( addRemovePt && points[1].size() < (size_t)MAX_COUNT ){
		vector<Point2f> tmp;
		tmp.push_back(point);
		cornerSubPix( gray, tmp, winSize, cvSize(-1,-1), termcrit);
		points[1].push_back(tmp[0]);
		addRemovePt = false;
	  }
	  
	  needToInit = false;
	  imshow("LK Demo", image);
	  
	  char c = (char)waitKey(10);
	  if( c == 27 )
		break;
	  switch( c )
		{
		case 'r':
		  needToInit = true;
		  break;
		case 'c':
		  points[1].clear();
		  break;
		case 'n':
		  nightMode = !nightMode;
		  break;
		default:
		  ;
		}

	  std::swap(points[1], points[0]);
	  swap(prevGray, gray);
	}

  return 0;
}
