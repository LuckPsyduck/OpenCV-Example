//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//	����������������������ͷ�ļ�
//---------------------------------------------------------------------------------------------- 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
  
using namespace cv;
using namespace std;

Mat img;
int threshval = 120;			//�켣�������Ӧ��ֵ������ֵ160

//-----------------------------��on_trackbar( )������------------------------------------
//	�������켣���Ļص�����
//-----------------------------------------------------------------------------------------------
static void on_trackbar(int, void*)
{
	Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);//��Ϊ��ֵͼ��

	//����������
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//�������������к�ͼƬֱ�ӱ��޸�
	/*
	CV_EXPORTS_W void findContours( InputOutputArray image, OutputArrayOfArrays contours,
                              OutputArray hierarchy, int mode,
                              int method, Point offset=Point());
	*/
	findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
	//��ʼ��dst
	Mat dst = Mat::zeros(img.size(), CV_8UC3);
	//��ʼ����
	if( !contours.empty() && !hierarchy.empty() )
	{
		//�������ж������������������ɫֵ���Ƹ���������ɲ���
		int idx = 0;
		for( ; idx >= 0; idx = hierarchy[idx][0] )//hierarchy��˫����ṹ���൱�ڵ�����
		{
			Scalar color( (rand()&255), (rand()&255), (rand()&255) );
			//�����������
			//! draws contours in the image
	//CV_EXPORTS_W void drawContours( InputOutputArray image, InputArrayOfArrays contours,
	//							  int contourIdx, const Scalar& color,
	//							  int thickness=1, int lineType=8,
	//							  InputArray hierarchy=noArray(),
	//							  int maxLevel=INT_MAX, Point offset=Point() );
			drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );
		}
	}
	//��ʾ����
	imshow( "Connected Components", dst );
}

int main(  )
{
	system("color 5F");  

	img = imread("a.jpg", 0);
	if( !img.data )
	{ 
		printf("Oh��no����ȡimgͼƬ�ļ�����~�� \n"); 
		return -1; 
	}

	namedWindow( "Image", 1 );//��ʾԭͼ
	imshow( "Image", img );

	namedWindow( "Connected Components", 1 );	//����������
	
	createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );//�����켣��
	on_trackbar(threshval, 0);//�켣���ص�����

	waitKey(0);
	return 0;
}
