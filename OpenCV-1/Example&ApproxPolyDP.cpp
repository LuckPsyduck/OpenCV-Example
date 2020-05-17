#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat srcImage, grayImage;
int thresh = 100;
const int threshMaxValue = 255;
RNG rng(12345);

//�����ص�����
void thresh_callback(int, void*);

int main(int argc,char **argv)
{
	srcImage = imread(argv[1]);

	//�ж�ͼ���Ƿ���سɹ�
	if (srcImage.empty())
	{
		cout << "ͼ�����ʧ��!";
		return -1;
	}
	else
		cout << "ͼ����سɹ�!" << endl << endl;

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
	imshow("ԭͼ��", grayImage);

	//�����켣��
	createTrackbar("Thresh:", "ԭͼ��", &thresh, threshMaxValue, thresh_callback);
	thresh_callback(thresh, 0);

	waitKey(0);

	return 0;
}

void thresh_callback(int, void*)
{
	Mat threshold_output;
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	//ͼ���ֵ������Ե
	threshold(grayImage, threshold_output, thresh, 255, THRESH_BINARY);
	//Ѱ��ͼ������
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//ʹ�ö���αƽ���⵽��ͼ��������Ѱ�Ұ�Χ�����ľ��κ���СԲ
	vector<vector<Point>>contours_poly(contours.size());
	vector<Rect>boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	/*
	curve:����Ķ�ά�㼯��������vector���ͻ�Mat���� 
	approxCurve:����αƽ��Ľ����������������ĵ㼯����һ�� 
	epsilon���ƽ��ľ��ȣ�Ϊԭʼ���ߺͱƽ����߼�����ֵ 
	closed:���Ϊtrue���ƽ�������Ϊ������ߣ����Ϊfalse��ƽ����߲����
	*/
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));//�������㲢���ص㼯������ľ��α߽�
		minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);//���õ����㷨���Ը����Ķ�ά�㼯Ѱ�Ҽ���ɰ�Χ�㼯����СԲ��
	}

	//���Ƽ�⵽��ͼ�����������κ���С��ΧԲ
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		/*Rect����tl��ʾtop_left�����Ͻǵĵ㣬br��ʾbottom_right�����·��ĵ�*/
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}

	namedWindow("����ͼ", WINDOW_AUTOSIZE);
	imshow("����ͼ", drawing);
}

