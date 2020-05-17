#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
	Mat srcImage, grayImage, dstImage;
	srcImage = imread(argv[1]);

	//判断图像是否加载成功
	if (srcImage.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}
	else
	{
		cout << "图像加载成功!" << endl << endl;
	}

	namedWindow("原图像", WINDOW_AUTOSIZE);
	imshow("原图像", srcImage);

	//转换为灰度图并平滑滤波
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	//定义变量
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	grayImage = grayImage > 100;
	findContours(grayImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	//绘制轮廓图
	dstImage = Mat::zeros(grayImage.size(), CV_8UC3);
	for (int i = 0; i < hierarchy.size(); i++)
	{
		Scalar color = Scalar(rand() % 255, rand() % 255, rand() % 255);
		drawContours(dstImage, contours, i, color, CV_FILLED, 8, hierarchy);
	}
	imshow("轮廓图", dstImage);
	waitKey(0);

	return 0;
}
