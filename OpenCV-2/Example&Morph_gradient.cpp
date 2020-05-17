//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//            ����������������������ͷ�ļ�
//----------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char *argv[])
{
	//����ԭʼͼ  
	Mat image = imread(argv[1]);  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ
	//��������  
	namedWindow("��ԭʼͼ����̬ѧ�ݶ�",0); 
	namedWindow("��Ч��ͼ����̬ѧ�ݶ�",0); 
	//��ʾԭʼͼ 
	imshow("��ԭʼͼ����̬ѧ�ݶ�", image); 
	//�����
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); 
	//������̬ѧ����
	morphologyEx(image,image, MORPH_GRADIENT, element);
	//��ʾЧ��ͼ 
	imshow("��Ч��ͼ����̬ѧ�ݶ�", image); 

	waitKey(0); 

	return 0; 
}