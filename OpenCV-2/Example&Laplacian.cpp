//-----------------------------------【头文件包含部分】---------------------------------------
//            描述：包含程序所依赖的头文件
//----------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char **argv)
{
	Mat src,src_gray,dst, abs_dst;

	src = imread(argv[1]); 

	imshow("【原始图】图像Laplace变换", src); 

	//【3】使用高斯滤波消除噪声
	GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

	//【4】转换为灰度图
	cvtColor( src, src_gray, CV_RGB2GRAY );

	//【5】使用Laplace函数
	Laplacian( src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );

	//【6】计算绝对值，并将结果转换成8位
	convertScaleAbs( dst, abs_dst );

	imshow( "【效果图】图像Laplace变换", abs_dst );

	waitKey(0); 

	return 0; 
}