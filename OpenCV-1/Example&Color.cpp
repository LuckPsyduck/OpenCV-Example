#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
	Mat srcImage = imread(argv[1]);

	//判断图像是否加载成功
	if(!srcImage.data)
	{
		cout << "图像加载失败!" << endl;
		return false;
	}
	else
		cout << "图像加载成功!" << endl << endl;

	//显示原图像
	namedWindow("原图像",WINDOW_AUTOSIZE);
	imshow("原图像",srcImage);

	//将图像转换为灰度图，采用CV_前缀
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);     //将图像转换为灰度图
	namedWindow("灰度图",WINDOW_AUTOSIZE);
	imshow("灰度图",grayImage);

	//将图像转换为HSV，采用COLOR_前缀
	Mat HSVImage;//色调，饱和度，亮度
	cvtColor(srcImage, HSVImage, COLOR_BGR2HSV);    //将图像转换为HSV图
	namedWindow("HSV",WINDOW_AUTOSIZE);
	imshow("HSV",HSVImage);

	waitKey(0);

	return 0;
}