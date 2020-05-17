//-----------------------------------【头文件包含部分】---------------------------------------
//            描述：包含程序所依赖的头文件
//----------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char *argv[])
{
	//载入原始图  
	Mat image = imread(argv[1]);  //工程目录下应该有一张名为1.jpg的素材图
	//创建窗口  
	namedWindow("【原始图】形态学梯度",0); 
	namedWindow("【效果图】形态学梯度",0); 
	//显示原始图 
	imshow("【原始图】形态学梯度", image); 
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); 
	//进行形态学操作
	morphologyEx(image,image, MORPH_GRADIENT, element);
	//显示效果图 
	imshow("【效果图】形态学梯度", image); 

	waitKey(0); 

	return 0; 
}