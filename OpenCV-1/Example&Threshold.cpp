/*
 *����ͨ������trackbar��������ֵ������
 *ͨ������trackbar������
 *�������ֵ���������£�
 *0: THRESH_BINARY ��������ֵ��
 *1: THRESH_BINARY_INV ����������ֵ��
 *2: THRESH_TRUNC �ض���ֵ��
 *3: THRESH_TOZERO ��ֵ��Ϊ0
 *4: THRESH_TOZERO_INV ����ֵ��Ϊ0
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat g_srcImage, g_srcGrayImage, g_dstImage;

const int typeMaxValue = 4;
int typeValue = 0;
const int binaryMaxValue = 255;

const int thresholdMaxValue = 255;      //��ֵ�����ֵ
int thresholdValue = 0;     //��ֵ�ĳ�ʼֵ

//����ص�����
void thresholdFun(int, void*);

int main(int argc,char **argv)
{
    g_srcImage = imread(argv[1]);

    //�ж�ͼ���Ƿ���سɹ�
    if(g_srcImage.empty())
    {
        cout << "ͼ�����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼ����سɹ�!" << endl << endl;

    cvtColor(g_srcImage, g_srcGrayImage, COLOR_RGB2GRAY);   //��ͼ��ת��Ϊ�Ҷ�ͼ

    //�����켣��������������
    namedWindow("ͼ����ֵ������", WINDOW_AUTOSIZE);

    char threasholdTypeName[20];
    sprintf(threasholdTypeName, "��ֵ������ %d", typeMaxValue);

    createTrackbar(threasholdTypeName, "ͼ����ֵ������", &typeValue, typeMaxValue, thresholdFun);
    thresholdFun(typeValue, 0);

    char thresholdValueName[20];
    sprintf(thresholdValueName, "��   ֵ %", thresholdMaxValue);

    createTrackbar(thresholdValueName, "ͼ����ֵ������", &thresholdValue, thresholdMaxValue, thresholdFun);
    thresholdFun(thresholdValue, 0);

    waitKey(0);

    return 0;
}

//�ص�����
void thresholdFun(int, void*)
{
    int thresholdType;
    switch(typeValue)
    {
    case 0:
        thresholdType = THRESH_BINARY;
        break;
    case 1:
        thresholdType = THRESH_BINARY_INV;
        break;
    case 2:
        thresholdType = THRESH_TRUNC;
        break;
    case 3:
        thresholdType = THRESH_TOZERO;
        break;
    case 4:
        thresholdType = THRESH_TOZERO_INV;
        break;
    default:
        break;
    }

    //ͼ����ֵ������
	/*
	CV_EXPORTS_W double threshold( InputArray src, OutputArray dst,
                               double thresh, double maxval, int type );
	*/
    threshold(g_srcGrayImage, g_dstImage, thresholdValue, binaryMaxValue, thresholdType);   

    imshow("ͼ����ֵ������", g_dstImage);
}
