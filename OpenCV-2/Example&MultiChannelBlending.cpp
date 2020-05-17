//-----------------------------------������˵����----------------------------------------------
//  ��������:����OpenCV���Ž̳�֮�ġ�������ɫͨ��&��ͨ��ͼ����   ����Դ��
                                                                              
#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

bool MultiChannelBlending();


int main(  )
{
	system("color 5E");

	if(MultiChannelBlending())
	{
		cout<<endl<<"�š����ˣ��ó�������Ҫ�Ļ��ֵͼ��~";
	}

	waitKey(0);
	return 0;
}


//-----------------------------��MultiChannelBlending( )������--------------------------------
//     ��������ͨ����ϵ�ʵ�ֺ���
//-----------------------------------------------------------------------------------------------
bool MultiChannelBlending()
{
	//��0��������ر���
	Mat srcImage;
	Mat logoImage;
	vector<Mat>channels;
	Mat  imageBlueChannel;

	//=================����ɫͨ�����֡�=================
	//     ��������ͨ�����-��ɫ��������
	//============================================

	//��1������ͼƬ
	logoImage=imread("b.jpg",0);
	srcImage=imread("a.jpg");

	if(!logoImage.data ) 
	{ 
		printf("Oh��no����ȡlogoImage����~��\n");
		return false;
	}
	if(!srcImage.data ) 
	{
		printf("Oh��no����ȡsrcImage����~��\n"); 
		return false; 
	}

	//��2����һ��3ͨ��ͼ��ת����3����ͨ��ͼ��
	split(srcImage,channels);//����ɫ��ͨ��

	//��3����ԭͼ����ɫͨ�����÷��ظ�imageBlueChannel��ע�������ã��൱�����ߵȼۣ��޸�����һ����һ�����ű�
	imageBlueChannel=channels.at(0);

	//��4����ԭͼ����ɫͨ���ģ�250,250�����괦���·���һ�������logoͼ���м�Ȩ������\
	���õ��Ļ�Ͻ���浽imageBlueChannel��
	addWeighted(imageBlueChannel(Rect(250,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0,imageBlueChannel(Rect(250,250,logoImage.cols,logoImage.rows)));

	//��5����������ͨ�����ºϲ���һ����ͨ��
	merge(channels,srcImage);

	//��6����ʾЧ��ͼ
	namedWindow("<1>��Ϸԭ��+logo��ɫͨ��");
	imshow("<1>��Ϸԭ��+logo��ɫͨ��",srcImage);


	//=================����ɫͨ�����֡�=================
	//     ��������ͨ�����-��ɫ��������
	//============================================

	//��0��������ر���
	Mat  imageGreenChannel;

	//��1�����¶���ͼƬ
	logoImage=imread("b.jpg",0);
	srcImage=imread("a.jpg");

	if(!logoImage.data ) 
	{ 
		printf("Oh��no����ȡlogoImage����~��\n"); 
		return false;
	}
	if(!srcImage.data ) 
	{ 
		printf("Oh��no����ȡsrcImage����~��\n");
		return false;
	}

	//��2����һ����ͨ��ͼ��ת����������ͨ��ͼ��
	split(srcImage,channels);//����ɫ��ͨ��

	//��3����ԭͼ����ɫͨ�������÷��ظ�imageBlueChannel��ע�������ã��൱�����ߵȼۣ��޸�����һ����һ�����ű�
	imageGreenChannel=channels.at(1);
	//��4����ԭͼ����ɫͨ���ģ�250,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageGreenChannel��
	addWeighted(imageGreenChannel(Rect(250,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0,imageGreenChannel(Rect(250,250,logoImage.cols,logoImage.rows)));

	//��5�������������ĵ�ͨ�����ºϲ���һ����ͨ��
	merge(channels,srcImage);

	//��6����ʾЧ��ͼ
	namedWindow("<2>��Ϸԭ��+logo��ɫͨ��");
	imshow("<2>��Ϸԭ��+logo��ɫͨ��",srcImage);



	//=================����ɫͨ�����֡�=================
	//     ��������ͨ�����-��ɫ��������
	//============================================

	//��0��������ر���
	Mat  imageRedChannel;

	//��1�����¶���ͼƬ
	logoImage=imread("b.jpg",0);
	srcImage=imread("a.jpg");

	if(!logoImage.data )
	{ 
		printf("Oh��no����ȡlogoImage����~��\n"); 
		return false;
	}
	if(!srcImage.data ) 
	{ 
		printf("Oh��no����ȡsrcImage����~��\n"); 
		return false;
	}

	//��2����һ����ͨ��ͼ��ת����������ͨ��ͼ��
	split(srcImage,channels);//����ɫ��ͨ��

	//��3����ԭͼ�ĺ�ɫͨ�����÷��ظ�imageBlueChannel��ע�������ã��൱�����ߵȼۣ��޸�����һ����һ�����ű�
	imageRedChannel=channels.at(2);
	//��4����ԭͼ�ĺ�ɫͨ���ģ�250,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageRedChannel��
	addWeighted(imageRedChannel(Rect(250,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0,imageRedChannel(Rect(250,250,logoImage.cols,logoImage.rows)));

	//��5�������������ĵ�ͨ�����ºϲ���һ����ͨ��
	merge(channels,srcImage);

	//��6����ʾЧ��ͼ
	namedWindow("<3>��Ϸԭ��+logo��ɫͨ��");
	imshow("<3>��Ϸԭ��+logo��ɫͨ��",srcImage);

	return true;
}