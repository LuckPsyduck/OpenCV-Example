//-----------------------------------【程序说明】---------------------------------------------- &nbsp;
// &nbsp; &nbsp; &nbsp;程序名称:：《【OpenCV入门教程之十八】OpenCV仿射变换 & SURF特征点描述合辑》 博文配套源码 之 仿射变换

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图窗口】"					//为窗口标题定义的宏 
#define WINDOW_NAME2 "【经过Warp后的图像】"        //为窗口标题定义的宏 
#define WINDOW_NAME3 "【经过Warp和Rotate后的图像】"        //为窗口标题定义的宏 

static void ShowHelpText( );

int main(int argc,char **argv)
{	
	system("color 1A"); //【0】改变console字体颜色

	ShowHelpText( );//【0】显示欢迎和帮助文字

	//【1】参数准备
	//定义两组点，代表两个三角形
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	//定义一些Mat变量
	Mat rotMat( 2, 3, CV_32FC1 );
	Mat warpMat( 2, 3, CV_32FC1 );
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	//【2】加载源图像并作一些初始化
	srcImage = imread(argv[1], 1 );
	if(!srcImage.data )
	{ 
		printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n");
		return false; 
	} 
	// 设置目标图像的大小和类型与源图像一致
	dstImage_warp = Mat::zeros( srcImage.rows, srcImage.cols, srcImage.type() );

	//【3】设置源图像和目标图像上的三组点以计算仿射变换
	srcTriangle[0] = Point2f( 0,0 );
	srcTriangle[1] = Point2f( static_cast<float>(srcImage.cols - 1), 0 );
	srcTriangle[2] = Point2f( 0, static_cast<float>(srcImage.rows - 1 ));

	dstTriangle[0] = Point2f( static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f( static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f( static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));

	//【4】求得仿射变换
	warpMat = getAffineTransform( srcTriangle, dstTriangle );

	//【5】对源图像应用刚刚求得的仿射变换
	warpAffine( srcImage, dstImage_warp, warpMat, dstImage_warp.size() );

	//【6】对图像进行缩放后再旋转
	// 计算绕图像中点顺时针旋转50度缩放因子为0.6的旋转矩阵
	Point center = Point( dstImage_warp.cols/2, dstImage_warp.rows/2 );
	double angle = -30.0;
	double scale = 0.8;
	// 通过上面的旋转细节信息求得旋转矩阵
	rotMat = getRotationMatrix2D( center, angle, scale );
	// 旋转已缩放后的图像
	warpAffine( dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size() );


	//【7】显示结果
	imshow( WINDOW_NAME1, srcImage );
	imshow( WINDOW_NAME2, dstImage_warp );
	imshow( WINDOW_NAME3, dstImage_warp_rotate );

	// 等待用户按任意按键退出程序
	waitKey(0);

	return 0;
}


//-----------------------------------【ShowHelpText( )函数】----------------------------------  
//      描述：输出一些帮助信息  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//输出一些帮助信息  
	printf(   "\n\n\n\t欢迎来到【仿射变换】示例程序~\n\n");  
	printf("\t当前使用的OpenCV版本为 OpenCV "CV_VERSION);     
}  