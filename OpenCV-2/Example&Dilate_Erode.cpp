#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char *argv[])
{
	Mat image = imread(argv[1]),image_erode,image_dilate; 

	namedWindow("��ԭʼͼ��",0); 
	namedWindow("��Ч��ͼ������",0); 
	namedWindow("��Ч��ͼ����ʴ",0); 

	imshow("��ԭʼͼ��", image); 
	
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //�����

	morphologyEx(image,image_dilate, MORPH_DILATE, element);	//������̬ѧ����
	morphologyEx(image,image_erode, MORPH_ERODE, element);

	imshow("��Ч��ͼ������", image_dilate); 
	imshow("��Ч��ͼ����ʴ", image_erode); 
	waitKey(0); 

	return 0; 
}

//
//OpenCV�е���morphologyEx�������и�ʴ������ʾ���������£�
//
//
//
//	//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//	//            ����������������������ͷ�ļ�
//	//----------------------------------------------------------------------------------------------
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//
//	//-----------------------------------�������ռ��������֡�---------------------------------------
//	//            ����������������ʹ�õ������ռ�
//	//-----------------------------------------------------------------------------------------------
//	using namespace cv;
////-----------------------------------��main( )������--------------------------------------------
////            ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ
////-----------------------------------------------------------------------------------------------
//int main( )
//{
//	//����ԭʼͼ  
//	Mat image = imread("1.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ
//	//��������  
//	namedWindow("��ԭʼͼ����ʴ"); 
//	namedWindow("��Ч��ͼ����ʴ"); 
//	//��ʾԭʼͼ 
//	imshow("��ԭʼͼ����ʴ", image); 
//	//�����
//	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); 
//	//������̬ѧ����
//	morphologyEx(image,image, MORPH_ERODE, element);
//	//��ʾЧ��ͼ 
//	imshow("��Ч��ͼ����ʴ", image); 
//
//	waitKey(0); 
//
//	return 0; 
//}
