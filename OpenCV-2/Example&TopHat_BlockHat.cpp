//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//            ����������������������ͷ�ļ�
//----------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char **argv)
{
	//����ԭʼͼ  
	Mat image = imread(argv[1]);  
	Mat image_TopHat,image_BlockHat;
	
	namedWindow("��ԭʼͼ��",0); 
	namedWindow("��Ч��ͼ����ñ����",0); 
	namedWindow("��Ч��ͼ����ñ����",0); 

	imshow("��ԭʼͼ��", image); 
	
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //�����
	
	morphologyEx(image,image_TopHat, MORPH_TOPHAT, element);//������̬ѧ����

	morphologyEx(image,image_BlockHat, MORPH_BLACKHAT, element);

	imshow("��Ч��ͼ����ñ����", image_TopHat); 
	imshow("��Ч��ͼ����ñ����", image_BlockHat); 

	waitKey(0); 

	return 0; 
}


////-----------------------------------��ͷ�ļ��������֡�---------------------------------------
////            ����������������������ͷ�ļ�
////----------------------------------------------------------------------------------------------
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//
////-----------------------------------�������ռ��������֡�---------------------------------------
////            ����������������ʹ�õ������ռ�
////-----------------------------------------------------------------------------------------------
//using namespace cv;
////-----------------------------------��main( )������--------------------------------------------
////            ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ
////-----------------------------------------------------------------------------------------------
//int main( )
//{
//	//����ԭʼͼ  
//	Mat image = imread("1.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ
//	//��������  
//	namedWindow("��ԭʼͼ����ñ����"); 
//	namedWindow("��Ч��ͼ����ñ����"); 
//	//��ʾԭʼͼ 
//	imshow("��ԭʼͼ����ñ����", image); 
//	//�����
//	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); 
//	//������̬ѧ����
//	morphologyEx(image,image, MORPH_BLACKHAT, element);
//	//��ʾЧ��ͼ 
//	imshow("��Ч��ͼ����ñ����", image); 
//
//	waitKey(0); 
//
//	return 0; 
//}

