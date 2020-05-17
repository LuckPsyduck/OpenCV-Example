#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <Windows.h>

using namespace std;
using namespace cv;

//定义全局变量
Mat srcImage, grayImage;
int thresh = 100;
const int threshMaxValue = 255;
RNG rng(12345);

//声明回调函数
void thresh_callback(int, void*);

int main(int argc,char **argv)
{
	srcImage = imread(argv[1]);

	//判断文件是否加载成功
	if (!srcImage.data)
	{
		cout << "图像加载失败...";
		return -1;
	}
	else
		cout << "图像加载成功..." << endl << endl;

	namedWindow("原图像", WINDOW_AUTOSIZE);
	imshow("原图像", srcImage);

	//图像转化为灰度图并平滑
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	namedWindow("灰度图", WINDOW_AUTOSIZE);
	imshow("灰度图", grayImage);

	//创建轨迹条
	createTrackbar("Thresh:", "灰度图", &thresh, threshMaxValue, thresh_callback);
	thresh_callback(thresh, 0);
	waitKey(0);

	return 0;
}

void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	//canny边缘检测
	Canny(grayImage, canny_output, thresh, thresh * 2, 3);
	//轮廓提取
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//计算图像矩
	vector<Moments>mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	//计算图像的质心
	vector<Point2f>mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);//公式
	}

	//绘制轮廓
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}

	namedWindow("轮廓图", WINDOW_AUTOSIZE);
	imshow("轮廓图", drawing);

	//用moments矩集计算轮廓面积并与opencv函数计算结果进行比较
	printf("\t Info: Area and Contour Length \n");
	for (int i = 0; i < contours.size(); i++)
	{
		printf("* Contour[%d] - Area(M_00)=%.2f-Area OpenCV:%.2f - Length:%.2f\n", i, mu[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);//! draws the circle outline or a solid circle in the image
	}
}

