//-----------------------------------【程序说明】----------------------------------------------
//  程序名称:：【OpenCV入门教程之四】分离颜色通道&多通道图像混合   配套源码
                                                                              
#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

bool MultiChannelBlending();


int main(  )
{
	system("color 5E");

	if(MultiChannelBlending())
	{
		cout<<endl<<"嗯。好了，得出了你需要的混合值图像~";
	}

	waitKey(0);
	return 0;
}


//-----------------------------【MultiChannelBlending( )函数】--------------------------------
//     描述：多通道混合的实现函数
//-----------------------------------------------------------------------------------------------
bool MultiChannelBlending()
{
	//【0】定义相关变量
	Mat srcImage;
	Mat logoImage;
	vector<Mat>channels;
	Mat  imageBlueChannel;

	//=================【蓝色通道部分】=================
	//     描述：多通道混合-蓝色分量部分
	//============================================

	//【1】读入图片
	logoImage=imread("b.jpg",0);
	srcImage=imread("a.jpg");

	if(!logoImage.data ) 
	{ 
		printf("Oh，no，读取logoImage错误~！\n");
		return false;
	}
	if(!srcImage.data ) 
	{
		printf("Oh，no，读取srcImage错误~！\n"); 
		return false; 
	}

	//【2】把一个3通道图像转换成3个单通道图像
	split(srcImage,channels);//分离色彩通道

	//【3】将原图的蓝色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
	imageBlueChannel=channels.at(0);

	//【4】将原图的蓝色通道的（250,250）坐标处右下方的一块区域和logo图进行加权操作，\
	将得到的混合结果存到imageBlueChannel中
	addWeighted(imageBlueChannel(Rect(250,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0,imageBlueChannel(Rect(250,250,logoImage.cols,logoImage.rows)));

	//【5】将三个单通道重新合并成一个三通道
	merge(channels,srcImage);

	//【6】显示效果图
	namedWindow("<1>游戏原画+logo蓝色通道");
	imshow("<1>游戏原画+logo蓝色通道",srcImage);


	//=================【绿色通道部分】=================
	//     描述：多通道混合-绿色分量部分
	//============================================

	//【0】定义相关变量
	Mat  imageGreenChannel;

	//【1】重新读入图片
	logoImage=imread("b.jpg",0);
	srcImage=imread("a.jpg");

	if(!logoImage.data ) 
	{ 
		printf("Oh，no，读取logoImage错误~！\n"); 
		return false;
	}
	if(!srcImage.data ) 
	{ 
		printf("Oh，no，读取srcImage错误~！\n");
		return false;
	}

	//【2】将一个三通道图像转换成三个单通道图像
	split(srcImage,channels);//分离色彩通道

	//【3】将原图的绿色通道的引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
	imageGreenChannel=channels.at(1);
	//【4】将原图的绿色通道的（250,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageGreenChannel中
	addWeighted(imageGreenChannel(Rect(250,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0,imageGreenChannel(Rect(250,250,logoImage.cols,logoImage.rows)));

	//【5】将三个独立的单通道重新合并成一个三通道
	merge(channels,srcImage);

	//【6】显示效果图
	namedWindow("<2>游戏原画+logo绿色通道");
	imshow("<2>游戏原画+logo绿色通道",srcImage);



	//=================【红色通道部分】=================
	//     描述：多通道混合-红色分量部分
	//============================================

	//【0】定义相关变量
	Mat  imageRedChannel;

	//【1】重新读入图片
	logoImage=imread("b.jpg",0);
	srcImage=imread("a.jpg");

	if(!logoImage.data )
	{ 
		printf("Oh，no，读取logoImage错误~！\n"); 
		return false;
	}
	if(!srcImage.data ) 
	{ 
		printf("Oh，no，读取srcImage错误~！\n"); 
		return false;
	}

	//【2】将一个三通道图像转换成三个单通道图像
	split(srcImage,channels);//分离色彩通道

	//【3】将原图的红色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
	imageRedChannel=channels.at(2);
	//【4】将原图的红色通道的（250,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageRedChannel中
	addWeighted(imageRedChannel(Rect(250,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0,imageRedChannel(Rect(250,250,logoImage.cols,logoImage.rows)));

	//【5】将三个独立的单通道重新合并成一个三通道
	merge(channels,srcImage);

	//【6】显示效果图
	namedWindow("<3>游戏原画+logo红色通道");
	imshow("<3>游戏原画+logo红色通道",srcImage);

	return true;
}