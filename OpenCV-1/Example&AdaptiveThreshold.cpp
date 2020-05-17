#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat srcImage, grayImage, dstImage;

const int thresholdTypeMaxValue = 1;
int thresholdTypeValue = 0;//��Ϊ1
const int CMaxValue = 50;
int CValue = 10;
const double maxValue = 255;
int blockSize = 5;

//����ص�����
void adaptiveThresholdFun(int, void*);

int main(int argc,char **argv)
{
	Mat srcImage = imread(argv[1]);

	//�ж�ͼ���Ƿ��ȡ�ɹ�
	if(srcImage.empty())
	{
		cout << "ͼ���ȡʧ��!" << endl;
		return -1;
	}
	else
		cout << "ͼ���ȡ�ɹ�!" << endl << endl;

	cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);
	namedWindow("�Ҷ�ͼ",WINDOW_AUTOSIZE);
	imshow("�Ҷ�ͼ", grayImage);

	//�켣�����Ժ�������������
	namedWindow("��ֵͼ��", WINDOW_AUTOSIZE);
	char thresholdTypeName[20];
	sprintf(thresholdTypeName, "��ֵ����\n 0: THRESH_BINARY\n 1: THRESH_BINARY_INV ", thresholdTypeMaxValue);
	createTrackbar(thresholdTypeName, "��ֵͼ��", &thresholdTypeValue, thresholdTypeMaxValue, adaptiveThresholdFun);

	adaptiveThresholdFun(thresholdTypeValue, 0);

	char CName[20];
	sprintf(CName, "��  �� %d", CMaxValue);
	createTrackbar(CName, "��ֵͼ��", &CValue, CMaxValue, adaptiveThresholdFun);
	adaptiveThresholdFun(CValue, 0);


	waitKey(0);
	return 0;
}

void adaptiveThresholdFun(int, void*)
{
	int thresholdType;
	switch(thresholdTypeValue)
	{
	case 0:
		thresholdType = THRESH_BINARY;
		break;

	case 1:
		thresholdType = THRESH_BINARY_INV;
		break;

	default:
		break;
	}
	/*
	CV_EXPORTS_W void adaptiveThreshold( InputArray src, OutputArray dst,
                                     double maxValue, int adaptiveMethod,
                                     int thresholdType, int blockSize, double C );
	*/
	adaptiveThreshold(grayImage, dstImage, maxValue, ADAPTIVE_THRESH_MEAN_C,
		thresholdType, blockSize, CValue);

	imshow("��ֵͼ��", dstImage);
}
