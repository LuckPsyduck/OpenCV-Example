#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat g_srcImage;
Mat g_dilateImage;
Mat g_erodeImage;

//���������켣������
const int typeMaxValue = 2;         //���͸�ʴ����ͼ�ε�����
const int kernelSizeMaxVale = 21;   //����kernel�ĳߴ����ֵ

int dilateTypeValue = 0;            //Ĭ�����Ͳ���ģ��ͼ������
int dilateSizeValue = 5;            //Ĭ��ģ��ͼ��ߴ�
int erodeTypeValue = 0;
int erodeSizeValue = 5;

//���������ص�����
void dilateFun(int, void*);         //���ͻص�����
void erodeFun(int, void*);          //��ʴ�ص�����

int main(int argc,char **argv)
{
	g_srcImage = imread(argv[1]);

	//�ж�ͼ���Ƿ�򿪳ɹ�
	if(g_srcImage.empty())
	{
		cout << "ͼ�����ʧ��!" << endl;
		return -1;
	}
	else
		cout << "ͼ����سɹ�!" << endl << endl;
	namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
	imshow("ԭͼ��",g_srcImage);

	//�������Ͳ����������Լ��켣������
	namedWindow("ͼ������", WINDOW_AUTOSIZE);
	namedWindow("ͼ��ʴ", WINDOW_AUTOSIZE);

	char typeName[20];
	sprintf(typeName, "ģ������ %d", typeMaxValue);

	char sizeName[20];
	sprintf(sizeName, "ģ��ߴ� %d", kernelSizeMaxVale);

	//�������͹켣��
	createTrackbar(typeName, "ͼ������", &dilateTypeValue, typeMaxValue, dilateFun);
	createTrackbar(sizeName, "ͼ������", &dilateSizeValue, kernelSizeMaxVale, dilateFun);
	dilateFun(dilateTypeValue, 0);
	dilateFun(dilateSizeValue, 0);

	//������ʴ�켣��
	createTrackbar(typeName, "ͼ��ʴ", &erodeTypeValue, typeMaxValue, erodeFun);
	createTrackbar(sizeName, "ͼ��ʴ", &erodeSizeValue, kernelSizeMaxVale, erodeFun);
	erodeFun(erodeTypeValue, 0);
	erodeFun(erodeSizeValue, 0);

	waitKey(0);

	return 0;
}

//���ͻص�����
void dilateFun(int, void*)
{
	//ȷ��ģ��ͼ������
	int dilate_type;
	if(dilateTypeValue == 0)
		dilate_type = MORPH_RECT;
	else if (dilateTypeValue == 1)
		dilate_type = MORPH_CROSS;
	else
		dilate_type = MORPH_ELLIPSE;

	Mat element = getStructuringElement(dilate_type, Size(2*dilateSizeValue + 1, 2*dilateSizeValue + 1));
	dilate(g_srcImage, g_dilateImage, element);     //���Ͳ���
	imshow("ͼ������", g_dilateImage);

}

//��ʴ�ص�����
void erodeFun(int, void*)
{
	//ȷ��ģ��ͼ������
	int erode_type;
	if(erodeTypeValue == 0)
		erode_type = MORPH_RECT;
	else if (erodeTypeValue == 1)
		erode_type = MORPH_CROSS;
	else
		erode_type = MORPH_ELLIPSE;

	Mat element = getStructuringElement(erode_type, Size(2*erodeSizeValue + 1, 2*erodeSizeValue + 1));
	erode(g_srcImage, g_erodeImage, element);     //��ʴ����
	imshow("ͼ��ʴ", g_erodeImage);
}
