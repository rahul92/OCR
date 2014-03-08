#ifndef TRAIN
#define TRAIN

#include <math.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include<cstring>

using namespace std;

void training()
{
	//Clearing the file
	
	ofstream file;
	file.open("dataStorage.txt");
	file<<"";
	file.close();
	string address = "C:/Users/Pranay/Documents/Visual Studio 2010/Projects/Opencv1/data/";
	float w[32][32];
	Scalar tempIni, temp;
	for(int i=0;i<totalItems;i++)
	{
		for(int y=0;y<MAX_SIZE;y++)
		{
			for(int x=0;x<MAX_SIZE;x++)
				w[y][x] = 0;
		}
		for(int j=1;j<=dataSize;j++)
		{
			char a[33];
			Mat inp = imread(address + output[i] +itoa(j,a,10) + ".jpg");
			//cout<<i<<" "<<j<<endl;
			//Mat inp = imread(address + a + ".jpg");
			if (inp.empty()) 
			{
				cout << "Cannot load image!" << endl;
			}
			Mat image = Mat(MAX_SIZE,MAX_SIZE, CV_32F);
			resize(inp, image, image.size(), 0, 0);
			cvtColor( image, image, CV_BGR2GRAY) ;
			for(int y=0;y<MAX_SIZE;y++)
			{
				for(int x=0;x<MAX_SIZE;x++)
				{
					if(image.at<uchar>(y,x) > thresholdValue)
						w[y][x] += -1;
					else
						w[y][x] += 1;
				}
			}
		}
		double deno=0;
		for(int y=0;y<MAX_SIZE;y++)
		{
			for(int x=0;x<MAX_SIZE;x++)
			{
				if(w[y][x] > 0)
					deno += w[y][x];
				//if(i==17) cout<<w[y][x]<<" ";
			}
			//if(i==17) cout<<endl;
		}
		//if(i==17) cout<<"deno="<<deno<<endl;
		file.open("dataStorage.txt", ios::out | ios::app | ios::binary);
		if(file.is_open())
		{
			file<<deno;
			for(int y=0;y<MAX_SIZE;y++)
			{
				for(int x=0;x<MAX_SIZE;x++)
				{
					file<<","<<w[y][x];
				}
			}
			file<<"\n   \n";
			file.close();
		}
		else
			cout<<"Data storing failed !!\n";
	}
	cout<<"Training complete !!\n\n";
	//waitKey(0);
}

#endif