#include <iostream>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat g_srcImage;         //����ͼ��
Mat g_dstImage;         //���ͼ��

//����켣�����ֵ����
const int g_nKwidthTrackBarMaxValue = 9;
const int g_nKheightTrackBarMaxValue = 9;
const int g_nsigmaXTrackBarMaxValue = 5;
const int g_nsigmaYTrackBarMaxvalue = 5;

//����ÿ���켣���ĳ�ʼֵ
int g_nKwidthTrackBarValue = 1;
int g_nKheightTrackBarValue = 1;
int g_nsigmaXTrackBarValue = 1;
int g_nsigmaYTrackBarValue = 1;

int g_kernelWidthValue;
int g_kernelHeightValue;

void on_GaussianBlurTrackbar(int, void*);       //����ص�����

int main(int argc,char **argv)
{
    g_srcImage = imread(argv[1]);

    //�ж�ͼ���Ƿ���سɹ�
    if(!g_srcImage.data)
    {
        cout << "ͼ�����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼ����سɹ�!" << endl << endl;

    namedWindow("ԭͼ��", WINDOW_NORMAL);         //���崰����ʾ����
    imshow("ԭͼ��", g_srcImage);

    namedWindow("��˹�˲�ͼ��", WINDOW_NORMAL);

    //����ÿ���켣������
    char widthTrackBarName[20];
    sprintf(widthTrackBarName, "�˺���width %d", g_nKwidthTrackBarMaxValue);

    char heightTrackBarName[20];
    sprintf(heightTrackBarName,"�˺���height %d", g_nKheightTrackBarMaxValue);

    char sigmaXTrackBarName[20];
    sprintf(sigmaXTrackBarName, "�˺���sigmaX %d", g_nsigmaXTrackBarMaxValue);

    char sigmaYTrackBarName[20];
    sprintf(sigmaYTrackBarName, "�˺���sigmaY %d", g_nsigmaYTrackBarMaxvalue);

    //�����켣��
    createTrackbar(widthTrackBarName, "��˹�˲�ͼ��", &g_nKwidthTrackBarValue, 
                    g_nKwidthTrackBarMaxValue, on_GaussianBlurTrackbar);
    on_GaussianBlurTrackbar(g_nKwidthTrackBarValue, 0);

    createTrackbar(heightTrackBarName, "��˹�˲�ͼ��", &g_nKheightTrackBarValue,
                    g_nKheightTrackBarMaxValue, on_GaussianBlurTrackbar);
    on_GaussianBlurTrackbar(g_nKheightTrackBarValue, 0);

    createTrackbar(sigmaXTrackBarName, "��˹�˲�ͼ��", &g_nsigmaXTrackBarValue,
                    g_nsigmaXTrackBarMaxValue, on_GaussianBlurTrackbar);
    on_GaussianBlurTrackbar(g_nsigmaXTrackBarValue, 0);

    createTrackbar(sigmaYTrackBarName, "��˹�˲�ͼ��", &g_nsigmaYTrackBarValue,
                    g_nsigmaYTrackBarMaxvalue, on_GaussianBlurTrackbar);
    on_GaussianBlurTrackbar(g_nsigmaYTrackBarValue, 0);

    waitKey(0);

    return 0;
}

void on_GaussianBlurTrackbar(int, void*)
{
    //���������width��height���¼���ksize.width��ksize.height
    g_kernelWidthValue = g_nKwidthTrackBarValue * 2 + 1;
    g_kernelHeightValue = g_nKheightTrackBarValue * 2 + 1;

    //��˹�˲�
    GaussianBlur(g_srcImage, g_dstImage, Size(g_kernelWidthValue, g_kernelHeightValue),
                g_nsigmaXTrackBarValue, g_nsigmaYTrackBarValue);

    imshow("��˹�˲�ͼ��", g_dstImage);
}
