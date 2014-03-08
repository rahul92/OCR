#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <iostream>
#include<sstream>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

/*#include "cnn.h"
#include "dataInput.h"
#include "dataReader.h"*/


using namespace cv;
using namespace std;

//int totalItems = 62;
//int dataSize = 10;
int thresholdValue = 250;
int totalItems = 62;
int dataSize = 6;
int MAX_SIZE = 32;
string output[62]={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "vv", "ww", "xx", "yy", "zz", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

#include "train.h"
#include "ANNMatching.h"
void detect(Mat t)
{
	training();
	//Mat image = imread("C:/Users/DELL3493/Documents/Visual Studio 2010/Projects/ocrnew/data/RR.jpg");
	//cout<<"yes\n";
	matching(t);
	system("pause") ;
}