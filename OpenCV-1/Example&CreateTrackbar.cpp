#include <iostream>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
const int g_nTrackbarMaxValue = 100;     //���������ֵ
int g_nTrackbarValue;                    //��������Ӧ��ֵ
double g_dAlphaValue;                   //��һ��ͼȨ��
double g_dBetaValue;                    //�ڶ���ͼȨ��
Mat g_srcImage1, g_srcImage2, g_distImage;

//�����ص�����
void on_Trackbar(int, void*);          

int main(int argc,char **argv)
{
    g_srcImage1 = imread(argv[1]);
    g_srcImage2 = imread(argv[2]);

    //�ж�ͼ���Ƿ���سɹ�
    if(g_srcImage1.data && g_srcImage2.data)
        cout << "ͼ����سɹ�!" << endl << endl;
    else
    {
        cout << "ͼ�����ʧ��!" << endl << endl;
        return -1;
    }

    namedWindow("��Ϻ�ͼ��",WINDOW_NORMAL);     //�����������Ĵ���
    g_nTrackbarValue = 20;                      //���û�������ʼֵ

    //�ڴ����Ĵ����д����������ؼ�������
    char trackBarName[100];

    sprintf(trackBarName, "͸���� %2d", g_nTrackbarMaxValue);       //Linux�汾���

    //sprintf_s(trackBarName, "͸���� %d", g_nTrackbarMaxValue);     //Windows�汾���

    createTrackbar(trackBarName, "��Ϻ�ͼ��", &g_nTrackbarValue, g_nTrackbarMaxValue, on_Trackbar);

    on_Trackbar(g_nTrackbarValue, 0);           //����ڻص���������ʾ

    waitKey(0);

    return 0;
}

void on_Trackbar(int, void*)
{
    //ͼ���ںϵ�Ȩ����0-1֮�䣬ת������ֵ��Ȩ��֮��ı���
    g_dAlphaValue = (double) g_nTrackbarValue / g_nTrackbarMaxValue;
    g_dBetaValue = 1.0 - g_dAlphaValue;     //�ڶ���ͼ��Ȩ��

    //ʹ��addWeighted������ͼ��������Ի��
    addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_distImage);

    imshow("��Ϻ�ͼ��", g_distImage);
}
