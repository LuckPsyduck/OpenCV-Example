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
	imshow("��ԭʼͼ��Scharr�˲���", src); 

	//��3���� X�����ݶ�
	Scharr( src, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( grad_x, abs_grad_x );
	imshow("��Ч��ͼ�� X����Scharr", abs_grad_x); 

	//��4����Y�����ݶ�
	Scharr( src, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );
	imshow("��Ч��ͼ��Y����Scharr", abs_grad_y); 

	//��5���ϲ��ݶ�(����)
	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );

	//��6����ʾЧ��ͼ
	imshow("��Ч��ͼ���ϲ��ݶȺ�Scharr", dst); 

	waitKey(0); 
	return 0; 
}