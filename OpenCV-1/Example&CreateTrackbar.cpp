#include <iostream>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

//声明全局变量
const int g_nTrackbarMaxValue = 100;     //滑动条最大值
int g_nTrackbarValue;                    //滑动条对应的值
double g_dAlphaValue;                   //第一幅图权重
double g_dBetaValue;                    //第二幅图权重
Mat g_srcImage1, g_srcImage2, g_distImage;

//声明回调函数
void on_Trackbar(int, void*);          

int main(int argc,char **argv)
{
    g_srcImage1 = imread(argv[1]);
    g_srcImage2 = imread(argv[2]);

    //判断图像是否加载成功
    if(g_srcImage1.data && g_srcImage2.data)
        cout << "图像加载成功!" << endl << endl;
    else
    {
        cout << "图像加载失败!" << endl << endl;
        return -1;
    }

    namedWindow("混合后图像",WINDOW_NORMAL);     //滑动条依附的窗口
    g_nTrackbarValue = 20;                      //设置滑动条初始值

    //在创建的窗体中创建滑动条控件并命名
    char trackBarName[100];

    sprintf(trackBarName, "透明度 %2d", g_nTrackbarMaxValue);       //Linux版本语句

    //sprintf_s(trackBarName, "透明度 %d", g_nTrackbarMaxValue);     //Windows版本语句

    createTrackbar(trackBarName, "混合后图像", &g_nTrackbarValue, g_nTrackbarMaxValue, on_Trackbar);

    on_Trackbar(g_nTrackbarValue, 0);           //结果在回调函数中显示

    waitKey(0);

    return 0;
}

void on_Trackbar(int, void*)
{
    //图像融合的权重在0-1之间，转换输入值和权重之间的比例
    g_dAlphaValue = (double) g_nTrackbarValue / g_nTrackbarMaxValue;
    g_dBetaValue = 1.0 - g_dAlphaValue;     //第二幅图像权重

    //使用addWeighted函数对图像进行线性混合
    addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_distImage);

    imshow("混合后图像", g_distImage);
}
