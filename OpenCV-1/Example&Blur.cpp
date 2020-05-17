#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat g_srcImage;         //��������ͼ��
Mat g_dstImage;         //����Ŀ��ͼ��

const int g_nTrackbarMaxValue = 9;      //����켣�����ֵ
int g_nTrackbarValue;                   //����켣����ʼֵ
int g_nKernelValue;                     //����kernel�ߴ�

void on_kernelTrackbar(int, void*);     //����ص�����

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

    namedWindow("ԭͼ��",WINDOW_AUTOSIZE);     //���崰����ʾ����
    imshow("ԭͼ��",g_srcImage);

    g_nTrackbarValue = 1;
    namedWindow("��ֵ�˲�", WINDOW_AUTOSIZE);   //�����˲���ͼ����ʾ��������

    //����켣�����ƺ����ֵ
    char kernelName[20];
    sprintf(kernelName, "kernel�ߴ� %d", g_nTrackbarMaxValue);    

    //�����켣��
    createTrackbar(kernelName, "��ֵ�˲�", &g_nTrackbarValue, g_nTrackbarMaxValue, on_kernelTrackbar);
    on_kernelTrackbar(g_nTrackbarValue, 0);

    waitKey(0);

    return 0;
}

void on_kernelTrackbar(int, void*)
{
    //��������ֵ���¼���kernel�ߴ�
    g_nKernelValue = g_nTrackbarValue * 2 + 1;

    //��ֵ�˲�����
    blur(g_srcImage, g_dstImage, Size(g_nKernelValue, g_nKernelValue));

    imshow("��ֵ�˲�", g_dstImage);
}