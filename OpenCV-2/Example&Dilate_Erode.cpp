#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char *argv[])
{
	Mat image = imread(argv[1]),image_erode,image_dilate; 

	namedWindow("【原始图】",0); 
	namedWindow("【效果图】膨胀",0); 
	namedWindow("【效果图】腐蚀",0); 

	imshow("【原始图】", image); 
	
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //定义核

	morphologyEx(image,image_dilate, MORPH_DILATE, element);	//进行形态学操作
	morphologyEx(image,image_erode, MORPH_ERODE, element);

	imshow("【效果图】膨胀", image_dilate); 
	imshow("【效果图】腐蚀", image_erode); 
	waitKey(0); 

	return 0; 
}

//
//OpenCV中调用morphologyEx函数进行腐蚀操作的示例程序如下：
//
//
//
//	//-----------------------------------【头文件包含部分】---------------------------------------
//	//            描述：包含程序所依赖的头文件
//	//----------------------------------------------------------------------------------------------
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//
//	//-----------------------------------【命名空间声明部分】---------------------------------------
//	//            描述：包含程序所使用的命名空间
//	//-----------------------------------------------------------------------------------------------
//	using namespace cv;
////-----------------------------------【main( )函数】--------------------------------------------
////            描述：控制台应用程序的入口函数，我们的程序从这里开始
////-----------------------------------------------------------------------------------------------
//int main( )
//{
//	//载入原始图  
//	Mat image = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图
//	//创建窗口  
//	namedWindow("【原始图】腐蚀"); 
//	namedWindow("【效果图】腐蚀"); 
//	//显示原始图 
//	imshow("【原始图】腐蚀", image); 
//	//定义核
//	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); 
//	//进行形态学操作
//	morphologyEx(image,image, MORPH_ERODE, element);
//	//显示效果图 
//	imshow("【效果图】腐蚀", image); 
//
//	waitKey(0); 
//
//	return 0; 
//}
