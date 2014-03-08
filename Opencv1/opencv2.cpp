#include <opencv2/highgui/highgui.hpp>
int main() {
IplImage* img = cvLoadImage( "E:/to.jpg" );
cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );
cvShowImage( "Example1", img );
cvWaitKey(0);
cvReleaseImage( &img );
cvDestroyWindow( "Example1" );
}