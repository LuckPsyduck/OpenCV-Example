//-----------------------------------【头文件包含部分】---------------------------------------
//	描述：包含程序所依赖的头文件
//---------------------------------------------------------------------------------------------- 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
  
using namespace cv;
using namespace std;

Mat img;
int threshval = 120;			//轨迹条滑块对应的值，给初值160

//-----------------------------【on_trackbar( )函数】------------------------------------
//	描述：轨迹条的回调函数
//-----------------------------------------------------------------------------------------------
static void on_trackbar(int, void*)
{
	Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);//变为二值图像

	//定义点和向量
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//查找轮廓，运行后，图片直接被修改
	/*
	CV_EXPORTS_W void findContours( InputOutputArray image, OutputArrayOfArrays contours,
                              OutputArray hierarchy, int mode,
                              int method, Point offset=Point());
	*/
	findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
	//初始化dst
	Mat dst = Mat::zeros(img.size(), CV_8UC3);
	//开始处理
	if( !contours.empty() && !hierarchy.empty() )
	{
		//遍历所有顶层轮廓，随机生成颜色值绘制给各连接组成部分
		int idx = 0;
		for( ; idx >= 0; idx = hierarchy[idx][0] )//hierarchy是双子针结构，相当于迭代器
		{
			Scalar color( (rand()&255), (rand()&255), (rand()&255) );
			//绘制填充轮廓
			//! draws contours in the image
	//CV_EXPORTS_W void drawContours( InputOutputArray image, InputArrayOfArrays contours,
	//							  int contourIdx, const Scalar& color,
	//							  int thickness=1, int lineType=8,
	//							  InputArray hierarchy=noArray(),
	//							  int maxLevel=INT_MAX, Point offset=Point() );
			drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );
		}
	}
	//显示窗口
	imshow( "Connected Components", dst );
}

int main(  )
{
	system("color 5F");  

	img = imread("a.jpg", 0);
	if( !img.data )
	{ 
		printf("Oh，no，读取img图片文件错误~！ \n"); 
		return -1; 
	}

	namedWindow( "Image", 1 );//显示原图
	imshow( "Image", img );

	namedWindow( "Connected Components", 1 );	//创建处理窗口
	
	createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );//创建轨迹条
	on_trackbar(threshval, 0);//轨迹条回调函数

	waitKey(0);
	return 0;
}
