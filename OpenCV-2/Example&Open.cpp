#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(int argc,char **argv)
{
	//����ԭʼͼ  
	Mat image = imread(argv[1]); 
	Mat image_open,image_close;
	//��������  
	namedWindow("��ԭʼͼ��",0); 
	namedWindow("��Ч��ͼ��������",0); 
	namedWindow("��Ч��ͼ��������",0); 

	imshow("��ԭʼͼ��", image); 
	
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //�����

	morphologyEx(image,image_open, MORPH_OPEN, element);	//������̬ѧ����

	morphologyEx(image,image_close, MORPH_CLOSE, element);

	imshow("��Ч��ͼ��������", image_open); 
	imshow("��Ч��ͼ��������", image_close);

	waitKey(0); 
	return 0; 
}

