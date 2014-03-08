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
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <cmath>
#include <list>



using namespace cv;
using namespace std;

Mat k, temp_im;
const float PI=3.14;
int N=200;

Mat im,im2,n,gr,final;
Mat grad_x;
	Mat grad_y;
int scale = 1, result2;
  int delta = 0;
  int ddepth = CV_32F;
  RNG rng(12345);
  int thresholdValue = 250;
int totalItems = 62;
int dataSize = 20;
int MAX_SIZE = 32;

string output[62]={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "vv", "ww", "xx", "yy", "zz", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

#include "train.h"
#include "ANNMatching.h"

string detect(Mat temp_im,int x1, int y1, int x2, int y2)
{
	//training();
	//Mat image = imread("C:/Users/DELL3493/Documents/Visual Studio 2010/Projects/ocrnew/data/RR.jpg");
	//cout<<"yes\n";
	return matching(temp_im,k,x1,y1,x2,y2);
	//system("pause") ;
}


   class Point2  {
  public:
    int x;
    int y;
    float SWT;
};

   void sort(vector<Rect> h)
{
    Rect a; int i;
for(int j=0;j<h.size();j++)
    {
		a=h[j];
        i=j-1;
		while((i>=0) && (a.tl().y<h[i].tl().y) || (i>=0) && (a.tl().y==h[i].tl().y) && (a.tl().x<h[i].tl().x) )
        {
            h[i+1]=h[i];
            h[i]=a;
            i=i-1;
        }

    }
}

void invert(Mat r)
{
	for(int i=0;i<r.rows;i++)
		for(int j=0;j<r.cols;j++)
		{
			Scalar temp3=r.at<float>(i, j);
			if(temp3.val[0]==0)
				r.at<float>(i, j)=255;
			else
				r.at<float>(i, j)=0;
		}
}

void remove(Mat l)
{
	for(int i=0;i<l.rows;i++)
	{
		int c=0;
		for(int j=0;j<l.cols;j++)
		{
			Scalar temp=l.at<float>(i,j);
			if(temp.val[0]>0 && j-1>0 && j+1<l.cols && i+1<l.rows && i-1>0)
			{
				Scalar p=l.at<float>(i,j-1);
				Scalar a=l.at<float>(i,j+1);
				Scalar br=l.at<float>(i+1,j+1);
				Scalar bl=l.at<float>(i+1,j-1);
				Scalar tr=l.at<float>(i-1,j+1);
				Scalar tl=l.at<float>(i-1,j-1);
				if(p.val[0]==0 && a.val[0]==0 && bl.val[0]==0 && tr.val[0]==0)
					l.at<float>(i,j)=0;
			}
		 if(temp.val[0]>0 && j-1>0 && j+1<l.cols && i+1<l.rows && i-1>0)
			{
				Scalar p2=l.at<float>(i-1,j);
				Scalar a2=l.at<float>(i+1,j);
				Scalar br=l.at<float>(i+1,j+1);
				Scalar bl=l.at<float>(i+1,j-1);
				Scalar tr=l.at<float>(i-1,j+1);
				Scalar tl=l.at<float>(i-1,j-1);
				if(p2.val[0]==0 && a2.val[0]==0 && bl.val[0]==0 && tr.val[0]==0)
					l.at<float>(i,j)=0;
			}
		}
	}

}
				
			

void connected_component(Mat swt)
{
  vector<vector<Point> > contours2;
  vector<vector<Point> > contours;
   vector<Vec4i> hierarchy2;
   vector<Vec4i> hierarchy;
   Mat cc=Mat(swt.rows,swt.cols,CV_8U);
   swt.convertTo(cc,CV_8U,1);
  
	//imshow("cc6",cc);
   Mat cc2=cc.clone();
   findContours( cc2, contours2, hierarchy2, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
   findContours( cc, contours, hierarchy, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
   //imshow("cc0",swt);
   vector<vector<Point> > contours_poly2( contours2.size() );
  vector<Rect> boundRect2( contours2.size() );
  vector<Point2f>center2( contours2.size() );
  vector<float>radius2( contours2.size() );
  for( int i = 0; i < contours2.size(); i++ )
     { //float area=contourArea(contours2[i]);
	  // if(area>=5.0)
	   {approxPolyDP( Mat(contours[i]), contours_poly2[i], 3, true );
	   boundRect2[i] = boundingRect( Mat(contours_poly2[i]) );
	   }
       //minEnclosingCircle( (Mat)contours_poly2[i], center2[i], radius2[i]);
     }
  //cout<<boundRect2[0].tl().x<<endl;
  //imshow("cc1",swt);
   for( int j = 0; j<boundRect2.size(); j++)
     {
       Scalar color2 = Scalar( rng.uniform(0, 255), rng.uniform(0,255),rng.uniform(0,255) );
       //drawContours( k, contours_poly2, j, color2, 1, 8, vector<Vec4i>(), 0, Point() );
	   
      rectangle( k, boundRect2[j].tl(), boundRect2[j].br(), color2, 1, 8, 0 );
      // circle( im2, center2[j], (int)radius2[j], Scalar(255,0,0), 2, 8, 0 );
   }


   /* Rect a;
	for(int j=0;j<boundRect2.size();j++)
    {
		a=boundRect2[j];
        int i=j-1;
		while((i>=0) && (a.br().y < boundRect2[i].br().y) ||  (i>=0) && (a.br().y == boundRect2[i].br().y) && (a.br().x < boundRect2[i].br().x) )
        {
            boundRect2[i+1]=boundRect2[i];
            boundRect2[i]=a;
            i=i-1;
        }

    }*/

		vector< vector < Rect > > mlist;
		
		//insert
		for(int j=0;j<boundRect2.size();j++)
		{
			Rect a=boundRect2[j];
			bool flag=false;
			for(int i=0;i<mlist.size();i++)
			{
				if(mlist[i][0].tl().y > a.br().y || mlist[i][0].br().y < a.tl().y){}
				else
				{
					mlist[i].push_back(a);
					flag=true;
					break;
				}
			}
			if(!flag)
			{
				vector< Rect > newlist;
				newlist.push_back(a);
				mlist.push_back(newlist);
			}
		
		}
		//sorting
		for(int i=0;i<mlist.size();i++)
		{
			for(int j=0;j<mlist[i].size();j++)
			{
				for (int k=0;k<mlist[i].size()-1;k++)
				{
					if (mlist[i][k+1].tl().x < mlist[i][k].tl().x)// ascending order simply changes to <
					{ 
						Rect t=mlist[i][k];
						mlist[i][k]=mlist[i][k+1];
						mlist[i][k+1]=t;
					}
				}
			}

		}
		//putback
		/*int j=0;
		for(int m=0;m<mlist.size();m++)
		{
			//vector< Rect > temp = *it;
			if(mlist[m].size() > 3)
			{
				for(int n=0;n<mlist[m].size();n++)
				{
					boundRect2[j++]=mlist[m][n];
					cout<<mlist[m][n].tl().x<<" ";
				}
				cout<<endl;
			}
		}
		boundRect2.resize(j);*/

   /*for( int j = 0; j< boundRect2.size(); j++)
   {
	   temp_im = swt(boundRect2[j]).clone();
	   //imshow("mid", temp_im);
	   invert(temp_im);
	imwrite( "D:/OCR/fin.jpg", temp_im);
	  detect(temp_im,boundRect2[j].tl().x,boundRect2[j].tl().y,boundRect2[j].br().x,boundRect2[j].br().y );
   }*/
	string letter;
	int x1,x2,c1x,c2x,gx1,gx2;
	ofstream file;
	file.open("finaloutput.txt");
	file<<"";
	file.close();
	file.open("finaloutput.txt", ios::out | ios::app | ios::binary);
	if(file.is_open())
	{
		for(int m=0;m<mlist.size();m++)
		{
			if(mlist[m].size() > 3)
			{
				gx1=mlist[m][0].tl().x;
				gx2=mlist[m][0].br().x;
				for(int n=0;n<mlist[m].size();n++)
				{
					temp_im = swt(mlist[m][n]).clone();
					invert(temp_im);
					imwrite( "D:/OCR/fin.jpg", temp_im);
					letter = detect(temp_im,mlist[m][n].tl().x,mlist[m][n].tl().y,mlist[m][n].br().x,mlist[m][n].br().y );
					x1=mlist[m][n].tl().x;
					x2=mlist[m][n].br().x;
					if(n!=0)
					{
						c2x=(x1+x2)/2;
						if((c2x-c1x) > 3*((gx2-gx1)/2))
							file<<"  ";
						c1x=c2x;
					}
					else
					{
						c1x=(x1+x2)/2;
					}
					file<<letter;
				}
				file<<"                                   ";
			}
		}
		file.close();
	}
	else
		cout<<"output writing failed !!\n";
	
    //imshow("cc",k);
	
   imwrite( "D:/OCR/Final2.jpg", k);
  

}


 
  Mat calculateOrientations(Mat gradientX, Mat gradientY, int l){
    // Create container element
	  //cout<<"yes"<<endl;
    Mat orientation = Mat(gradientX.rows, gradientX.cols, CV_32F);
	Mat orientation2 = Mat(gradientX.rows, gradientX.cols, CV_32F);
	 n=Mat(im.rows,im.cols,CV_32F);
	 for(int i = 0; i < n.rows; i++)
        for(int j = 0; j <n.cols; j++)
			n.at<float>(i,j)=0;
	 //cout<<n;
	//cout<<"yo"<<gradientX.rows<<endl;
    // Calculate orientations of gradients --> in degrees
    // Loop over all matrix values and calculate the accompanied orientation
    for(int i = 0; i < gradientX.rows; i++){
		//cout<<endl;
        for(int j = 0; j < gradientX.cols; j++){
            // Retrieve a single value
			
            float valueX = gradientX.at<float>(i,j);
            float valueY = gradientY.at<float>(i,j);
			float mag = sqrt( (valueX* valueX) + (valueY * valueY) );
            // Calculate the corresponding single direction, done by applying the arctangens function
			gradientX.at<float>(i,j)=(l*valueX)/mag;
			gradientY.at<float>(i,j)=(l*valueY)/mag;
            float result = (fastAtan2(l*valueY,l*valueX));
			//cout<<result<<" ";
            // Store in orientation matrix element
			if ( ( (result <= 22 && result >=0) || (result >= 337 && result<=360) ))
			{
					result2 = -90;
			}
			else if( (result >= 157.5 && result<=180) || (result < 202.5 && result>=180) )
				result2 =90;
			else if (  (result >= 22.5) && (result < 67.5) ) 
				result2 = -135;
			else if( ( (result >= 202.5) && (result < 247.5) ) )
				result2= 135;
			else if ( (result >= 67.5) && (result < 112.5) ) 
				result2 = 999;
			else if(( (result >= 247.5) && (result < 292.5) ) )
				result2= -999;
			else if ( (result >= 112.5) && (result < 157.5) )
				result2 = 45;
			else if ( (result >= 292.5) && (result < 337.5) ) 
				 result2 = -45;

			Scalar temp=im.at<uchar>(i, j);
				if(temp.val[0]==255)
				{
					orientation2.at<float>(i,j) = result;
				}
				else
				{
					orientation2.at<float>(i,j) = 444;
				}
				/*if(temp.val[0]!=0)
				{
					cout<<i<<" "<<j<<" ";
					cout<<result2<<" "<<"val "<<temp.val[0]<<endl;
					
				}*/
		}
		//cout<<endl;
	}
	for(int i = 0; i < im.rows; i++){
		//cout<<endl;
        for(int j = 0; j < im.cols; j++){
			//Scalar temp=im.at<uchar>(i, j);
			
			int count=0;
			int t=1,g=99999;
			int f=0;
			float c=(float)j+0.5;
			float r=(float)i+0.5;
			int curx=j;
			int cury=i;
			int x2=0, y2=0;
			Scalar temp=im.at<uchar>(i, j);
			if(temp.val[0]==255)
			{
				
					//cout<<"'";
				//cout<<orientation2.at<float>(i,j)<<" ";
				int count=0;
				float gX = gradientX.at<float>(i,j);
				float gY = gradientY.at<float>(i,j);
				int dir=orientation2.at<float>(i,j);
				int min2,max2;
				min2=dir-135<0?dir-135+360:dir-135;
				max2=dir+135>360?dir+135-360:dir+135;
				list<Point2>q;
				Point2 f;
				f.x=curx;
				f.y=cury;
				q.push_back(f);
				while (true) {
                    c += gX*0.5;
                    r += gY*0.5;
                    if ((int)(floor(c)) != curx || (int)(floor(r)) != cury) {
                        curx = (int)(floor(c));
                        cury = (int)(floor(r));
					
					count++;
					Point2 m;
					m.x=curx;
					m.y=cury;
					q.push_back(m);
					//if(count>80)
						//break;
				
				if (curx < 0 || (curx >= n.cols) || cury < 0 || (cury >= n.rows)) {

                            break;
                        }

				Scalar t=im.at<uchar>(cury, curx);
					if(t.val[0]==255)
					{
						//cout<<"yo";
						//cout<<orientation2.at<float>(cury,curx)<" ";
						//cout<<"min"<<min2<<" "<<"max"<<max2<<"   ";
						int gXt=gradientX.at<float>(cury,curx) ;
						int gYt=gradientY.at<float>(cury,curx);
							//cout<<dir<<" ";
						int dir2=orientation2.at<float>(cury,curx);
						if (dir2<min2 && dir2>max2)
							{
								list<Point2>::iterator u;
								for(u=q.begin();u!=q.end();u++)
									{
										//cout<<n;
										Scalar y=n.at<float>(u->y,u->x);
										//||(y.val[0]!=0 && ))
										if(y.val[0]==0 ||255-count>y.val[0])  
										n.at<float>(u->y,u->x)=255-count ;
									}
							}
						
						break;
					}
				}

				
				}
			}
            
        }
	}
    
	imwrite( "D:/OCR/swt.jpg", n);
	remove(n);

	imwrite( "D:/OCR/swtImproved.jpg", n);
	//imshow("Image2", n);
	connected_component(n);
    return orientation;
}


int main()
{
     im2 = imread("D:/Vaskar SirPics/ew.jpg");
	 k=imread("D:/Vaskar SirPics/ew.jpg");
	 Mat grad;
     if (im2.empty()) 
    {
        cout << "Cannot load image!" << endl;
        return -1;
    }

	cvtColor( im2, im2, CV_BGR2GRAY) ;
	//imshow("original2", im2);
	
	
	GaussianBlur( im2, im2,Size(5,5),0,0,4 );
	Canny( im2, im, 0, 90, 3 );

	imwrite( "D:/OCR/canny.jpg", im);
	erode(im,im,3,Point(0,0),2);
	//GaussianBlur(im, im,Size(5,5),0,0,4 );
	//imshow("canny",im);
	imwrite( "D:/OCR/canny2.jpg", im);
	gr=Mat(im2.rows,im2.cols,CV_8UC1);

	

  // Gradient X
  //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
  Sobel( im2, grad_x, ddepth, 1, 0, 3, 1, 0, BORDER_DEFAULT );
  Sobel( im2, grad_y, ddepth, 0, 1, 3, 1, 0,BORDER_DEFAULT );

  GaussianBlur(grad_x, grad_x,Size(5,5),0,0,4 );
  GaussianBlur(grad_y, grad_y,Size(5,5),0,0,4 );

 // convertScaleAbs( grad_y, abs_grad_y );
  //cout<<"yo";
  for(int i=0;i<gr.rows;i++)
	  for(int j=0;j<gr.cols;j++)
		  gr.at<uchar>(i,j)=-1;

  std::vector<Point2> points;
  imwrite( "D:/OCR/gradx.jpg", grad_x);
  imwrite( "D:/OCR/grady.jpg", grad_y);
  calculateOrientations(grad_x, grad_y,1);
  
  /*strokeWidthTransform(grad_x, grad_y,0,gr,rays);

  imshow("g2r", gr);
  SWTMedianFilter (gr, rays);
  final=Mat(gr.rows,gr.cols,CV_32F);
  //imshow("gr", gr);
  normalizeImage(gr,final);

  //imshow("original", im);
  
  imshow("final", final);*/
    system("pause");
}