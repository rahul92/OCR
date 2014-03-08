#ifndef ANNMATCHING
#define ANNMATCHING

#include <math.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include<cstring>

using namespace std;
string ou[62]={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
string matching(Mat a, Mat imToWrite, int x1, int y1, int x2, int y2)
{
	//char b[33];
	//box_count++;
	//putText(imToWrite,itoa(box_count,b,10),cvPoint(x1,y1),FONT_HERSHEY_COMPLEX_SMALL,0.5,cvScalar(255,0,0),1,CV_AA);
	string s;
	//s==itoa(box_count,b,10);
	//return s;
	//if(a.rows<15 || a.cols<15) return;
	Scalar temp;
	double deno=0.0, neu=0.0,maxMatch=0.0, maxMatch2=0.0;
	int outChar=-1,countNumber=-1, outChar2=-1, countNumber2=-1;
	Mat input = Mat(MAX_SIZE, MAX_SIZE, CV_32F);
	//cout<<"yp";
	resize(a, input, input.size(), 0, 0);
	//cvtColor( input, input, CV_BGR2GRAY);
	float inp[32][32] = { 0 };
	float wt[32][32] = { 0 };
	for(int y=0;y<MAX_SIZE;y++)
	{
		for(int x=0;x<MAX_SIZE;x++)
		{
			if(input.at<float>(y,x) > thresholdValue)
				inp[y][x] = 0;
			else
				inp[y][x] = 1;
		}
	}
	ifstream file;
	file.open("dataStorage.txt");
	
	if(file.is_open())
	{
		while(!file.eof())
		{
			string line;
			getline(file, line);
			if(line.length() > 5)
			{
				countNumber++;
				stringstream ss(line);
				double i;
				int j=0,k=0;
				while (ss >> i) {
					if(j==0)
						deno = i;
					else
					{
						wt[k/MAX_SIZE][k%MAX_SIZE] = i;
					}
					ss.ignore(1);
					if(j>0) k++;
					j++;
				}
				neu=0.0;
				for(int y=0;y<MAX_SIZE;y++)
				{
					for(int x=0;x<MAX_SIZE;x++)
					{
						neu = neu + (wt[y][x]*inp[y][x]);
					}
				}
				double val = neu/deno;
				if(maxMatch < val)
				{
					maxMatch2 = maxMatch;
					outChar2 = outChar;
					maxMatch = val;
					outChar = countNumber;
				}
				else if(maxMatch2 < val)
				{
					maxMatch2 = val;
					outChar2 = countNumber;
				}
				//cout<<"max= "<<neu/deno<<" "<<output[countNumber]<<endl;
			}
		}
		file.close();
	}		
	else
		cout<<"Failed in opening file !!\n";
	//cout<<"max="<<maxMatch<<endl;
	int temp4 = (x2-x1)/2;
	if(maxMatch>=0.5)
	{
		if(outChar == 37 && maxMatch2 >=.45)
		{
			//cout<<"Image matched with : "<<ou[outChar2]<<endl;
			putText(imToWrite,ou[outChar],cvPoint(x1+temp4-(temp4/2),y1),FONT_HERSHEY_COMPLEX_SMALL,1,cvScalar(255,0,0),1,CV_AA);
		}
		else
		{
			//cout<<"Image matched with : "<<ou[outChar]<<"  "<<a.rows<<" "<<a.cols<<endl;
			putText(imToWrite,ou[outChar],cvPoint(x1+temp4-(temp4/2),y1),FONT_HERSHEY_COMPLEX_SMALL,1,cvScalar(255,0,0),1,CV_AA);
			s=ou[outChar];
		}
	}
	else cout<<"No match !!\n";
	return s;
}

#endif