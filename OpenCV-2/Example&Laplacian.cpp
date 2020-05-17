//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//            ����������������������ͷ�ļ�
//----------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char **argv)
{
	Mat src,src_gray,dst, abs_dst;

	src = imread(argv[1]); 

	imshow("��ԭʼͼ��ͼ��Laplace�任", src); 

	//��3��ʹ�ø�˹�˲���������
	GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

	//��4��ת��Ϊ�Ҷ�ͼ
	cvtColor( src, src_gray, CV_RGB2GRAY );

	//��5��ʹ��Laplace����
	Laplacian( src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );

	//��6���������ֵ���������ת����8λ
	convertScaleAbs( dst, abs_dst );

	imshow( "��Ч��ͼ��ͼ��Laplace�任", abs_dst );

	waitKey(0); 

	return 0; 
}