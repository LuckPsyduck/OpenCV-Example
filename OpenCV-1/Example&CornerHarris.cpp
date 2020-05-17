#include <iostream>
#include <stdlib.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat srcImage, grayImage;
int thresh = 100;
const int threshMaxValue = 255;

//�����ص�����
void cornerHarris_detect(int, void*);

int main(int argc,char **argv)
{
	srcImage = imread(argv[1]);

	//�ж��ļ��Ƿ���سɹ�
	if (srcImage.empty())
	{
		cout << "ͼ�����ʧ�ܣ�";
		return -1;
	}
	else
		cout << "ͼ����سɹ�..." << endl << endl;

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	namedWindow("grayImage", WINDOW_AUTOSIZE);
	imshow("grayImage", grayImage);

	createTrackbar("Threshold:", "grayImage", &thresh, threshMaxValue, cornerHarris_detect);
	cornerHarris_detect(thresh, 0);

	waitKey(0);

	return 0;
}

void cornerHarris_detect(int, void*)
{
	Mat dstImage, dst_norm_image, dst_norm_scaled;
	dstImage = Mat::zeros(srcImage.size(), CV_32FC1);

	//�������������
	int blockSize = 2;          //����ߴ�
	int apertureSize = 3;       //Sobel���ӿ׾�
	double k = 0.04;            //Harris����

	//�ǵ���
	cornerHarris(grayImage, dstImage, blockSize, apertureSize, k, BORDER_DEFAULT);

	normalize(dstImage, dst_norm_image, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm_image, dst_norm_scaled);   //ǿ��һ�����ͼ�����Ա任Ϊ8λ�޷�������

	//���ƽǵ�
	for (int j = 0; j < dst_norm_image.rows; j++)
	{
		for (int i = 0; i < dst_norm_image.cols; i++)
		{
			if ((int)dst_norm_image.at<float>(j,i)>thresh)
			{
				circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
				circle(grayImage, Point(i, j), 5, Scalar(0, 0, 255), 2, 8, 0);
			}
		}
	}
	namedWindow("cornerHarris", WINDOW_AUTOSIZE);
	imshow("cornerHarris", dst_norm_scaled);
	namedWindow("corner_grayImage", WINDOW_AUTOSIZE);
	imshow("corner_grayImage", grayImage);
}
