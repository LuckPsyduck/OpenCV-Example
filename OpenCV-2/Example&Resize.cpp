//-----------------------------------【头文件包含部分】---------------------------------------
//		描述：包含程序所依赖的头文件
//---------------------------------------------------------------------------------------------- 
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char **argv)
{
	//载入原始图   
	Mat srcImage = imread(argv[1]); 
	Mat tmpImage,dstImage1,dstImage2;//临时变量和目标图的定义
	tmpImage=srcImage;//将原始图赋给临时变量

	//显示原始图  
	imshow("【原始图】", srcImage);  

	//进行尺寸调整操作
	resize(tmpImage,dstImage1,Size( tmpImage.cols/2, tmpImage.rows/2 ),(0,0),(0,0),3);//区域插值法
	resize(tmpImage,dstImage2,Size( tmpImage.cols*2, tmpImage.rows*2 ),(0,0),(0,0),3);

	//显示效果图  
	imshow("【效果图】之一", dstImage1);  
	imshow("【效果图】之二", dstImage2);  

	waitKey(0);  
	return 0;  
}