#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(int argc,char **argv)
{
	//载入原始图  
	Mat image = imread(argv[1]); 
	Mat image_open,image_close;
	//创建窗口  
	namedWindow("【原始图】",0); 
	namedWindow("【效果图】开运算",0); 
	namedWindow("【效果图】闭运算",0); 

	imshow("【原始图】", image); 
	
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //定义核

	morphologyEx(image,image_open, MORPH_OPEN, element);	//进行形态学操作

	morphologyEx(image,image_close, MORPH_CLOSE, element);

	imshow("【效果图】开运算", image_open); 
	imshow("【效果图】闭运算", image_close);

	waitKey(0); 
	return 0; 
}

