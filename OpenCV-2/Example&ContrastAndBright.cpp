//-----------------------------------������˵����----------------------------------------------
//  ��������:����OpenCV���Ž̳�֮�ġ� ����Trackbar&ͼ��Աȶȡ�����ֵ���� ���ײ���Դ��

#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include"opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include<windows.h>

using namespace std;
using namespace cv;


static void ContrastAndBright(int, void *);

int g_nContrastValue; //�Աȶ�ֵ
int g_nBrightValue;  //����ֵ
Mat g_srcImage,g_dstImage;

//-----------------------------��ContrastAndBright( )������------------------------------------
//     �������ı�ͼ��ԱȶȺ�����ֵ�Ļص�����
//-----------------------------------------------------------------------------------------------
static void ContrastAndBright(int, void *)
{
	namedWindow("��ԭʼͼ���ڡ�", 1);//��������

	//����forѭ����ִ������ g_dstImage(i,j) =a*g_srcImage(i,j) + b
	for(int y = 0; y < g_srcImage.rows; y++ )//BRG��˳��
		for(int x = 0; x < g_srcImage.cols; x++ )
			for(int c = 0; c < 3; c++ )//3ͨ��
				g_dstImage.at<Vec3b>(y,x)[c]= saturate_cast<uchar>\
				( (g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y,x)[c] ) + g_nBrightValue );

	imshow("��ԭʼͼ���ڡ�", g_srcImage);	//��ʾͼ��
	imshow("��Ч��ͼ���ڡ�", g_dstImage);
}

int main(int argc,char **argv)
{
	system("color 4A"); //�ı����̨ǰ��ɫ�ͱ���ɫ

	//�����û��ṩ��ͼ��
	g_srcImage= imread(argv[1]);
	if(!g_srcImage.data )
	{ 
		printf("Oh��no����ȡg_srcImageͼƬ����~��\n"); 
		return false;
	}
	g_dstImage= Mat::zeros( g_srcImage.size(), g_srcImage.type() );

	//�趨�ԱȶȺ����ȵĳ�ֵ
	g_nContrastValue=80;
	g_nBrightValue=80;

	//��������
	namedWindow("��Ч��ͼ���ڡ�", 1);

	//�����켣��
	createTrackbar("�Աȶȣ�", "��Ч��ͼ���ڡ�",&g_nContrastValue,300,ContrastAndBright );
	createTrackbar("��   �ȣ�","��Ч��ͼ���ڡ�",&g_nBrightValue,200,ContrastAndBright );

	//���ûص�����
	ContrastAndBright(g_nContrastValue,0);//��ʾͼƬ
	ContrastAndBright(g_nBrightValue,0);

	//���һЩ������Ϣ
	cout<<endl<<"\t�š����ˣ�������������۲�ͼ��Ч��~\n\n"
		<<"\t���¡�q����ʱ�������˳�~!\n";

	//���¡�q����ʱ�������˳�
	while(char(waitKey(1)) != 'q') {}
	return 0;
}


//�ı���������̨����ɫ 
//�� system("color 0A");  
//����color�����0�Ǳ���ɫ���ţ�A��ǰ��ɫ���š�����ɫ�������£�  
//0=��ɫ  
//1=��ɫ  
//2=��ɫ  
//3=����ɫ  
//4=��ɫ  
//5=��ɫ  
//6=��ɫ  
//7=��ɫ  
//8=��ɫ  
//9=����ɫ  
//A=����ɫ  
//B=��ǳ��ɫ  
//C=����ɫ  
//D=����ɫ  
//E=����ɫ  
//F=����ɫ  
//��仰����main�����ĵ�һ�䣬�ǵü���ͷ�ļ�#include<windows.h>

