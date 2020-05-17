//-----------------------------------【程序说明】----------------------------------------------
//  程序名称:：【OpenCV入门教程之三】图像的载入，显示与输出 
//  描述： 图像的载入，显示与输出 一站式剖析   配套源码
//------------------------------------------------------------------------------------------------
 
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
 
using namespace cv;
 
int main( )
{
	Mat girl=imread("a.png"); //载入图像到Mat
	namedWindow("【1】动漫图",0); //创建一个名为 "【1】动漫图"的窗口 
	imshow("【1】动漫图",girl);//显示名为 "【1】动漫图"的窗口 
 
	Mat image= imread("b.jpg",199);//载入图片
	Mat logo= imread("c.jpg");//logo图
 
	//载入后先显示
	namedWindow("【2】原画图",0);
	imshow("【2】原画图",image);
 
	namedWindow("【3】logo图",0);
	imshow("【3】logo图",logo);
 
	Mat imageROI;	//定义一个Mat类型，用于存放，图像的ROI
	
	imageROI=image(Rect(200,200,logo.cols,logo.rows));//方法一
	////方法二
	//imageROI=image(Range(350,350+logo.rows),Range(800,800+logo.cols));
 
	addWeighted(imageROI,0.5,logo,1,0,imageROI);//将logo加到原图上
 
	namedWindow("【4】原画+logo图",0);
	imshow("【4】原画+logo图",image);
 
	imwrite("我喜欢打dota2 by浅墨.png",image);
 
	waitKey();
 
	return 0;
}