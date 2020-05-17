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

	//�ж�ͼ���Ƿ���سɹ�
	if (srcImage.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}
	else
	{
		cout << "ͼ����سɹ�!" << endl << endl;
	}

	namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
	imshow("ԭͼ��", srcImage);

	//ת��Ϊ�Ҷ�ͼ��ƽ���˲�
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	//�������
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	grayImage = grayImage > 100;
	findContours(grayImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	//��������ͼ
	dstImage = Mat::zeros(grayImage.size(), CV_8UC3);
	for (int i = 0; i < hierarchy.size(); i++)
	{
		Scalar color = Scalar(rand() % 255, rand() % 255, rand() % 255);
		drawContours(dstImage, contours, i, color, CV_FILLED, 8, hierarchy);
	}
	imshow("����ͼ", dstImage);
	waitKey(0);

	return 0;
}
