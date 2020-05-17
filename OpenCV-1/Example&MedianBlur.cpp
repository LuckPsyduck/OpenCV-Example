#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat g_mSrcImage;
Mat g_mDstImage;
const int g_nMedianBlurMaxValue = 5;
int g_nMedianBlurValue;
int g_nkernelSize;

//����ص�����
void on_medianBlurTrackBar(int, void*);

int main(int argc,char **argv)
{
	g_mSrcImage = imread(argv[1]);

	//�ж��ļ��Ƿ���سɹ�
	if(g_mSrcImage.empty())
	{
		cout << "ͼ�����ʧ��!" << endl;
		return -1;
	}
	else
		cout << "ͼ����سɹ�!" << endl;

	//�ж�ͼ���Ƿ���CV_8Uͼ��
	if(g_mSrcImage.depth()>=0&&g_mSrcImage.depth() <= 255)
		cout << "����ͼ����ϴ���Ҫ��!" << endl;
	else
	{
		cout << "ͼ����Ȳ���CV_8U�����򼴽��˳�..." << endl;
		return -1;
	}

	namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
	imshow("ԭͼ��", g_mSrcImage);

	//���ͼ�񴰿����Լ��켣������
	namedWindow("��ֵ�˲�ͼ��", WINDOW_AUTOSIZE);
	char medianBlurName[20];
	sprintf(medianBlurName, "�˺����ߴ� %d", g_nMedianBlurMaxValue);
	g_nMedianBlurValue = 1;

	//�����켣��
	createTrackbar(medianBlurName, "��ֵ�˲�ͼ��", &g_nMedianBlurValue,
		g_nMedianBlurMaxValue, on_medianBlurTrackBar);
	on_medianBlurTrackBar(g_nMedianBlurValue, 0);

	waitKey(0);


	return 0;
}

void on_medianBlurTrackBar(int, void*)
{
	//���¼���ߴ�ֵ���ߴ�ֵӦΪ����1������
	g_nkernelSize = g_nMedianBlurValue * 2 + 1;
	medianBlur(g_mSrcImage, g_mDstImage, g_nkernelSize);

	imshow("��ֵ�˲�ͼ��", g_mDstImage);
}
