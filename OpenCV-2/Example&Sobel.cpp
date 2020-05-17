//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//            ����������������������ͷ�ļ�
//----------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char **argv)
{
	//��0������ grad_x �� grad_y ����
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y,dst;

	//��1������ԭʼͼ  
	Mat src = imread(argv[1]); 

	//��2����ʾԭʼͼ 
	namedWindow("��ԭʼͼ��sobel��Ե���", 0);
	imshow("��ԭʼͼ��sobel��Ե���", src); 

	//��3���� X�����ݶ�
	Sobel( src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
	convertScaleAbs( grad_x, abs_grad_x );//dst(i)=saturate_cast<uchar>abs(src(i)*alpha+beta)
	namedWindow("��Ч��ͼ�� X����Sobel", 0);
	imshow("��Ч��ͼ�� X����Sobel", abs_grad_x); 

	//��4����Y�����ݶ�
	Sobel( src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );//dst(i)=saturate_cast<uchar>abs(src(i)*alpha+beta)
	namedWindow("��Ч��ͼ��Y����Sobel", 0);
	imshow("��Ч��ͼ��Y����Sobel", abs_grad_y); 

	//��5���ϲ��ݶ�(����)
	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );
	namedWindow("��Ч��ͼ�����巽��Sobel", 0);
	imshow("��Ч��ͼ�����巽��Sobel", dst); 

	waitKey(0); 
	return 0; 
}