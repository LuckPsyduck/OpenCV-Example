#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

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

	//判断图像是否加载成功
	if (srcImage.empty())
	{
		cout << "图像加载失败!";
		return -1;
	}
	else
		cout << "图像加载成功!" << endl << endl;

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	namedWindow("原图像", WINDOW_AUTOSIZE);
	imshow("原图像", grayImage);

	//创建轨迹条
	createTrackbar("Thresh:", "原图像", &thresh, threshMaxValue, thresh_callback);
	thresh_callback(thresh, 0);

	waitKey(0);

	return 0;
}

void thresh_callback(int, void*)
{
	Mat threshold_output;
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	//图像二值化检测边缘
	threshold(grayImage, threshold_output, thresh, 255, THRESH_BINARY);
	//寻找图像轮廓
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//使用多边形逼近检测到的图像轮廓来寻找包围轮廓的矩形和最小圆
	vector<vector<Point>>contours_poly(contours.size());
	vector<Rect>boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	/*
	curve:输入的二维点集，可以是vector类型或Mat类型 
	approxCurve:多边形逼近的结果，其类型与输入的点集类型一致 
	epsilon：逼近的精度，为原始曲线和逼近曲线间的最大值 
	closed:如果为true，逼近的曲线为封闭曲线，如果为false则逼近曲线不封闭
	*/
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));//函数计算并返回点集最外面的矩形边界
		minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);//利用迭代算法，对给定的二维点集寻找计算可包围点集的最小圆形
	}

	//绘制检测到的图像轮廓、矩形和最小包围圆
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		/*Rect类中tl表示top_left即左上角的点，br表示bottom_right即右下方的点*/
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}

	namedWindow("轮廓图", WINDOW_AUTOSIZE);
	imshow("轮廓图", drawing);
}

