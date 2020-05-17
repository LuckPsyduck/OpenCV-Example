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

//����ص�����
void thresh_callback(int, void*);

int main(int argc,char **argv)
{
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

	//ͼ��Ҷ�ͼת����ƽ���˲�
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
	imshow("ԭͼ��", grayImage);

	//�����켣��
	createTrackbar("Threshold:", "ԭͼ��", &thresh, threshMaxValue, thresh_callback);
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

	//ʹ��Threshold���ͼ���Ե
	threshold(grayImage, threshold_output, thresh, 255, THRESH_BINARY);

	//Ѱ��ͼ������
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//Ѱ��ͼ��͹��
	vector<vector<Point>>hull(contours.size());//�������Ԫ�ظ���
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
	}

	//����������͹��
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());//����
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());//͹��
	}

	namedWindow("͹��", WINDOW_AUTOSIZE);
	imshow("͹��", drawing);
}

