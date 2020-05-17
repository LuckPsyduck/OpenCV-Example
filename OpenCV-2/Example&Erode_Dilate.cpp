#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
	if(argc < 2)
		cout<<"error!"<<endl;

	int a=1;
	int eIter=1,dIter=1,exitFlag=1;
	IplImage *image,*image1,*image2;
	image = cvLoadImage(argv[1]);
	/*cvCreateImage( CvSize size, int depth, int channels );*/
	image1 = cvCreateImage(cvSize(image->width,image->height),8,1);
	image2 = cvCreateImage(cvSize(image->width,image->height),8,1);

	

	/*Converts input array pixels from one color space to another
	/*  cvCvtColor( const CvArr* src, CvArr* dst, int code );                                                                     */
	cvCvtColor(image,image1,CV_RGB2GRAY);
	cvCvtColor(image,image2,CV_RGB2GRAY);

	cvNamedWindow("image",0);
	cvShowImage("image",image);

	cvNamedWindow("Select",0);
	/* create trackbar and display it on top of given window, set callback */
	cvCreateTrackbar("eIterations","Select",&eIter,20,0);
	cvCreateTrackbar("dIterations","Select",&dIter,20,0);

	cvNamedWindow("Erode",0);
	cvNamedWindow("Dilate",0);
	cvShowImage("Erode",image1);
	cvShowImage("Dilate",image2);
	cvWaitKey(0);

	while(1)
	{
		//腐蚀，消除细小物质
		cvErode(image1,image1,0,2);

		cvShowImage("Erode",image1);
		cout<<"Erode"<<endl;

		a=cvWaitKey(0);
		if((char) a == 'q')
			break;
	}

	cvCopy(image1,image2);
	a=1;
	while(1)
	{
		//膨胀，填充物体内细小物质
		cvDilate(image2,image2,0,1);

		cvShowImage("Dilate",image2);
		cout<<"Dilate"<<endl;

		a=cvWaitKey(0);

		if((char) a == 'q')
			break;
	}
	return 0;
}