#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
	Mat srcImage = imread(argv[1]);

	//�ж�ͼ���Ƿ���سɹ�
	if(!srcImage.data)
	{
		cout << "ͼ�����ʧ��!" << endl;
		return false;
	}
	else
		cout << "ͼ����سɹ�!" << endl << endl;

	//��ʾԭͼ��
	namedWindow("ԭͼ��",WINDOW_AUTOSIZE);
	imshow("ԭͼ��",srcImage);

	//��ͼ��ת��Ϊ�Ҷ�ͼ������CV_ǰ׺
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);     //��ͼ��ת��Ϊ�Ҷ�ͼ
	namedWindow("�Ҷ�ͼ",WINDOW_AUTOSIZE);
	imshow("�Ҷ�ͼ",grayImage);

	//��ͼ��ת��ΪHSV������COLOR_ǰ׺
	Mat HSVImage;//ɫ�������Ͷȣ�����
	cvtColor(srcImage, HSVImage, COLOR_BGR2HSV);    //��ͼ��ת��ΪHSVͼ
	namedWindow("HSV",WINDOW_AUTOSIZE);
	imshow("HSV",HSVImage);

	waitKey(0);

	return 0;
}