//-----------------------------------【头文件包含部分】---------------------------------------  
//      描述：包含程序所依赖的头文件  
//----------------------------------------------------------------------------------------------   
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
  
using namespace cv;  

int main(int argc,char **argv)
{    
	Mat src = imread(argv[1]); 
	imshow("【原始图】",src);
	Rect ccomp;
	floodFill(src, Point(50,30), Scalar(155, 255,55), &ccomp, Scalar(20, 20, 20),Scalar(20, 20, 20));
	imshow("【效果图】",src);
	waitKey(0);
	return 0;    
}  