#include <iostream>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

const int g_nTrackBarMaxValue = 9;      //�켣�����ֵ
int g_nTrackBarValue;                   //�켣����ʼֵ
Mat g_srcImage, g_dstImage;             //����ͼ��ȫ�ֱ���
int g_nKernelTrackbarValue;             //����켣����ֵ

void on_kernelTrackbar(int, void*);

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

    namedWindow("ԭͼ��",WINDOW_AUTOSIZE);
    imshow("ԭͼ��", g_srcImage);            //��ʾԭͼ��

    g_nTrackBarValue = 1;                   //��ʼ���켣����ʼֵ
    namedWindow("�����˲�",WINDOW_AUTOSIZE);      //�켣����������
    char kernelName[20];
    sprintf(kernelName, "�˲�kernel %d",g_nTrackBarMaxValue);

    //�����켣��
    createTrackbar(kernelName, "�����˲�", &g_nTrackBarValue,g_nTrackBarMaxValue,on_kernelTrackbar);
    on_kernelTrackbar(g_nTrackBarValue, 0);

    waitKey(0);

    return 0;
}

void on_kernelTrackbar(int, void*)
{
    //��������ֵ���¼���kernel�ߴ磬���������
    g_nKernelTrackbarValue = g_nTrackBarValue * 2 + 3;

    //�����˲�����
	/*
	CV_EXPORTS_W void boxFilter( InputArray src, OutputArray dst, int ddepth,
                             Size ksize, Point anchor=Point(-1,-1),
                             bool normalize=true,
                             int borderType=BORDER_DEFAULT );
	*/
    boxFilter(g_srcImage, g_dstImage, -1, Size(g_nKernelTrackbarValue, g_nKernelTrackbarValue));
    imshow("�����˲�", g_dstImage);
}
