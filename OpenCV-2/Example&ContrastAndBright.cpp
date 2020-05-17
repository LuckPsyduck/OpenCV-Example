//-----------------------------------【程序说明】----------------------------------------------
//  程序名称:：【OpenCV入门教程之四】 创建Trackbar&图像对比度、亮度值调整 配套博文源码

#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include"opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include<windows.h>

using namespace std;
using namespace cv;


static void ContrastAndBright(int, void *);

int g_nContrastValue; //对比度值
int g_nBrightValue;  //亮度值
Mat g_srcImage,g_dstImage;

//-----------------------------【ContrastAndBright( )函数】------------------------------------
//     描述：改变图像对比度和亮度值的回调函数
//-----------------------------------------------------------------------------------------------
static void ContrastAndBright(int, void *)
{
	namedWindow("【原始图窗口】", 1);//创建窗口

	//三个for循环，执行运算 g_dstImage(i,j) =a*g_srcImage(i,j) + b
	for(int y = 0; y < g_srcImage.rows; y++ )//BRG的顺序
		for(int x = 0; x < g_srcImage.cols; x++ )
			for(int c = 0; c < 3; c++ )//3通道
				g_dstImage.at<Vec3b>(y,x)[c]= saturate_cast<uchar>\
				( (g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y,x)[c] ) + g_nBrightValue );

	imshow("【原始图窗口】", g_srcImage);	//显示图像
	imshow("【效果图窗口】", g_dstImage);
}

int main(int argc,char **argv)
{
	system("color 4A"); //改变控制台前景色和背景色

	//读入用户提供的图像
	g_srcImage= imread(argv[1]);
	if(!g_srcImage.data )
	{ 
		printf("Oh，no，读取g_srcImage图片错误~！\n"); 
		return false;
	}
	g_dstImage= Mat::zeros( g_srcImage.size(), g_srcImage.type() );

	//设定对比度和亮度的初值
	g_nContrastValue=80;
	g_nBrightValue=80;

	//创建窗口
	namedWindow("【效果图窗口】", 1);

	//创建轨迹条
	createTrackbar("对比度：", "【效果图窗口】",&g_nContrastValue,300,ContrastAndBright );
	createTrackbar("亮   度：","【效果图窗口】",&g_nBrightValue,200,ContrastAndBright );

	//调用回调函数
	ContrastAndBright(g_nContrastValue,0);//显示图片
	ContrastAndBright(g_nBrightValue,0);

	//输出一些帮助信息
	cout<<endl<<"\t嗯。好了，请调整滚动条观察图像效果~\n\n"
		<<"\t按下“q”键时，程序退出~!\n";

	//按下“q”键时，程序退出
	while(char(waitKey(1)) != 'q') {}
	return 0;
}


//改变整个控制台的颜色 
//用 system("color 0A");  
//其中color后面的0是背景色代号，A是前景色代号。各颜色代码如下：  
//0=黑色  
//1=蓝色  
//2=绿色  
//3=湖蓝色  
//4=红色  
//5=紫色  
//6=黄色  
//7=白色  
//8=灰色  
//9=淡蓝色  
//A=淡绿色  
//B=淡浅绿色  
//C=淡红色  
//D=淡紫色  
//E=淡黄色  
//F=亮白色  
//这句话用在main函数的第一句，记得加入头文件#include<windows.h>

