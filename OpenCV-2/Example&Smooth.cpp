#include<cv.h>  
#include<highgui.h>  
#include<stdio.h>  
void main()
{
	IplImage* img_src = 0;
	IplImage* img_dst = 0;
	char* pictureImage = (char*)("smooth.jpg");
	img_src = cvLoadImage(pictureImage, 1);
	
	if (!img_src)
	{
		printf("Could not load image file:%s", pictureImage);
		exit(0);
	}
	img_dst = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_8U, 3);

	cvNamedWindow("原始图像:", 0);
	cvMoveWindow("原始图像:", 100, 100);
	cvShowImage("原始图像:", img_src);

	cvNamedWindow("简单模糊:", 0);
	cvMoveWindow("简单模糊:", 200, 100);

	//(simple blur)简单模糊- -对每个象素param1×param2邻域求和并做尺度变换 1/(param1×param2)。
	cvSmooth(img_src, img_dst, CV_BLUR, 3, 3, 0, 0);
	cvShowImage("简单模糊:", img_dst);

	//注意使用CV_BLUR_NO_SCALE时，原始图像和目标图像,他们的类型不能是一致的。
	IplImage* img_dst2 = 0;
	img_dst2 = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_16S, 3);
	cvNamedWindow("简单不带尺度变换的模糊:", 0);
	cvMoveWindow("简单不带尺度变换的模糊:", 300, 100);

	//(简单不带尺度变换的模糊)-对每个象素的 param1×param2 领域求和。\
	如果邻域大小是变化的,可以事先利用函数 cvIntegral 计算积分图像
	cvSmooth(img_src, img_dst2, CV_BLUR_NO_SCALE, 3, 3, 0, 0);
	cvShowImage("简单不带尺度变换的模糊:", img_dst2);

	cvNamedWindow("高斯卷积:", 0);//对图像进行核大小为 param1×param2 的高斯卷积。
	cvMoveWindow("高斯卷积:", 400, 100);
	cvSmooth(img_src, img_dst, CV_GAUSSIAN, 3, 3, 0, 0);
	cvShowImage("高斯卷积:", img_dst);

	cvNamedWindow("中值滤波:", 0);//对图像进行核大小为param1×param1 的中值滤波 (邻域是方的)。
	cvMoveWindow("中值滤波:", 500, 100);
	cvSmooth(img_src, img_dst, CV_MEDIAN, 3, 3, 0, 0);
	cvShowImage("中值滤波:", img_dst);

	//  cvSmooth(pFrameMat,pFrameMat,CV_BILATERAL,3,0,0);//双向滤波  
	//参数不对，改成  
	//cvSmooth(pFrameMat,pFrameMat,CV_BILATERAL,3,3,11,11);  
	//试试，后面两个参数分别代表了位置上和颜色上的sigma值，不能设为0的  
	cvNamedWindow("双向滤波:", 0);
	cvMoveWindow("双向滤波:", 600, 100);

	//(双向滤波) - -应用双向 3x3 滤波，彩色 sigma=param1，空间 sigma=param2.。
	cvSmooth(img_src, img_dst, CV_BILATERAL, 3, 3, 11, 11);
	cvShowImage("双向滤波:", img_dst);

	cvWaitKey(0);
	cvReleaseImage(&img_src);
	cvReleaseImage(&img_dst);
	cvDestroyWindow("原始图像:");
	cvDestroyWindow("简单不带尺度变换的模糊:");
	cvDestroyWindow("高斯卷积:");
	cvDestroyWindow("中值滤波:");
	cvDestroyWindow("双向滤波:");
}