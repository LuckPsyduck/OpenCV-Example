#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void MyEllipse(Mat img, double angle);
void MyFilledCircle(Mat img, Point center);
void MyLine(Mat img, Point start, Point end);
void MyPolygon(Mat img);

const int w = 400;

int main()
{
	char atom_window[] = "Drawing 1: Atom";
	char rook_window[] = "Drawing 2: Rook";

	//创建两个空的图像
	Mat atom_image = Mat::zeros(w, w, CV_8UC3);//int rows, int cols, int type
	Mat rook_image = Mat::zeros(w, w, CV_8UC3);

	//使用ellipse和circle函数绘制一个简单的原子结构
	MyEllipse(atom_image,90);
	MyEllipse(atom_image,0);
	MyEllipse(atom_image,45);
	MyEllipse(atom_image,-45);

	MyFilledCircle(atom_image,Point(w/2.0, w/2.0));

	namedWindow(atom_window,WINDOW_AUTOSIZE);
	imshow(atom_window,atom_image);

	//使用line,rectangle,polygon(多边形)绘制一个rook
	MyPolygon(rook_image);

	//创建一个矩形
	rectangle(rook_image,Point(0, 7*w/8.0),Point(w,w),Scalar(0,255,255),-1, 8);

	//创建直线
	MyLine(rook_image,Point(0,15*w/16),Point(w, 15*w/16));
	MyLine(rook_image,Point(w/4, 7*w/8),Point(w/4,w));
	MyLine(rook_image,Point(w/2, 7*w/8),Point(w/2,w));
	MyLine(rook_image,Point(3*w/4, 7*w/8), Point(3*w/4,w));

	//显示绘制的图像
	namedWindow(rook_window,WINDOW_AUTOSIZE);
	imshow(rook_window,rook_image);

	waitKey(0);

	return 0;
}

void MyEllipse(Mat img, double angle)
{
	int thickness = 2;      //线宽
	int lineType = 8;       //线的类型
	ellipse(img,Point(w/2.0, w/2.0),Size(w/4.0, w/16.0),angle,0,360,Scalar(255,0,0),thickness,lineType);//蓝
}

void MyFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,center,w/32.0,Scalar(0,0,255),thickness,lineType);//红
}

void MyLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img, start, end, Scalar(0,0,0),thickness,lineType);
}

void MyPolygon(Mat img)
{
	int lineType = 8;

	//生成一些点
	Point rook_points[1][20];//点连成线
	rook_points[0][0] = Point(w/4.0, 7*w/8.0);
	rook_points[0][1] = Point(3*w/4.0, 7*w/8.0);
	rook_points[0][2] = Point(3*w/4.0, 13*w/16.0);
	rook_points[0][3] = Point(11*w/16.0, 13*w/16.0);
	rook_points[0][4] = Point(19*w/32.0, 3*w/8.0);
	rook_points[0][5] = Point(3*w/4.0, 3*w/8.0);
	rook_points[0][6] = Point(3*w/4.0, w/8.0);
	rook_points[0][7] = Point(26*w/40.0, w/8.0);
	rook_points[0][8] = Point(26*w/40.0, w/4.0);
	rook_points[0][9] = Point(22*w/40.0, w/4.0);
	rook_points[0][10] = Point(22*w/40.0, w/8.0);
	rook_points[0][11] = Point(18*w/40.0, w/8.0);
	rook_points[0][12] = Point(18*w/40.0, w/4.0);
	rook_points[0][13] = Point(14*w/40.0, w/4.0);
	rook_points[0][14] = Point(14*w/40.0, w/8.0);
	rook_points[0][15] = Point(w/4.0, w/8.0);
	rook_points[0][16] = Point(w/4.0, 3*w/8.0);
	rook_points[0][17] = Point(13*w/32.0, 3*w/8.0);
	rook_points[0][18] = Point(5*w/16.0, 13*w/16.0);
	rook_points[0][19] = Point(w/4.0, 13*w/16.0);

	const Point* ppt[1] = {rook_points[0]};
	int npt[] = {20};

	fillPoly(img,ppt,npt,1,Scalar(255,255,255),lineType);
}