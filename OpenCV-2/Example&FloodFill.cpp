//-----------------------------------��ͷ�ļ��������֡�---------------------------------------  
//      ����������������������ͷ�ļ�  
//----------------------------------------------------------------------------------------------   
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
  
using namespace cv;  

int main(int argc,char **argv)
{    
	Mat src = imread(argv[1]); 
	imshow("��ԭʼͼ��",src);
	Rect ccomp;
	floodFill(src, Point(50,30), Scalar(155, 255,55), &ccomp, Scalar(20, 20, 20),Scalar(20, 20, 20));
	imshow("��Ч��ͼ��",src);
	waitKey(0);
	return 0;    
}  