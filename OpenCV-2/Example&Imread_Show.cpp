//-----------------------------------������˵����----------------------------------------------
//  ��������:����OpenCV���Ž̳�֮����ͼ������룬��ʾ����� 
//  ������ ͼ������룬��ʾ����� һվʽ����   ����Դ��
//------------------------------------------------------------------------------------------------
 
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
 
using namespace cv;
 
int main( )
{
	Mat girl=imread("a.png"); //����ͼ��Mat
	namedWindow("��1������ͼ",0); //����һ����Ϊ "��1������ͼ"�Ĵ��� 
	imshow("��1������ͼ",girl);//��ʾ��Ϊ "��1������ͼ"�Ĵ��� 
 
	Mat image= imread("b.jpg",199);//����ͼƬ
	Mat logo= imread("c.jpg");//logoͼ
 
	//���������ʾ
	namedWindow("��2��ԭ��ͼ",0);
	imshow("��2��ԭ��ͼ",image);
 
	namedWindow("��3��logoͼ",0);
	imshow("��3��logoͼ",logo);
 
	Mat imageROI;	//����һ��Mat���ͣ����ڴ�ţ�ͼ���ROI
	
	imageROI=image(Rect(200,200,logo.cols,logo.rows));//����һ
	////������
	//imageROI=image(Range(350,350+logo.rows),Range(800,800+logo.cols));
 
	addWeighted(imageROI,0.5,logo,1,0,imageROI);//��logo�ӵ�ԭͼ��
 
	namedWindow("��4��ԭ��+logoͼ",0);
	imshow("��4��ԭ��+logoͼ",image);
 
	imwrite("��ϲ����dota2 byǳī.png",image);
 
	waitKey();
 
	return 0;
}