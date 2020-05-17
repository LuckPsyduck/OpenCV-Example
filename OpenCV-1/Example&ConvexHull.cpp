#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

Mat srcImage, grayImage;
int thresh = 100;
const int threshMaxValue = 255;
RNG rng(12345);

//定义回调函数
void thresh_callback(int, void*);

int main(int argc,char **argv)
{
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

	//图像灰度图转化并平滑滤波
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	namedWindow("原图像", WINDOW_AUTOSIZE);
	imshow("原图像", grayImage);

	//创建轨迹条
	createTrackbar("Threshold:", "原图像", &thresh, threshMaxValue, thresh_callback);
	thresh_callback(thresh, 0);
	waitKey(0);

	return 0;
}

void thresh_callback(int, void*)
{
	Mat src_copy = srcImage.clone();
	Mat threshold_output;
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	//使用Threshold检测图像边缘
	threshold(grayImage, threshold_output, thresh, 255, THRESH_BINARY);

	//寻找图像轮廓
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//寻找图像凸包
	vector<vector<Point>>hull(contours.size());//容器里的元素个数
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
	}

	//绘制轮廓和凸包
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());//轮廓
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());//凸弧
	}

	namedWindow("凸包", WINDOW_AUTOSIZE);
	imshow("凸包", drawing);
}

