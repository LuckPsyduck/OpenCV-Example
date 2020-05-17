//-----------------------------------������˵����----------------------------------------------
//		��������:������OpenCV���Ž̳�֮ʮ�ߡ�OpenCV��ӳ�� & SURF��������ϼ� �� ��������Դ�� 

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "�����򴰿ڡ�"        //Ϊ���ڱ��ⶨ��ĺ� 

Mat g_srcImage, g_dstImage;
Mat g_map_x, g_map_y;

int update_map( int key);
static void ShowHelpText( );//�����������

//-----------------------------------��main( )������--------------------------------------------
//          ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	system("color 2F"); 	//�ı�console������ɫ

	//��ʾ��������
	ShowHelpText();

	//��1������ԭʼͼ
	g_srcImage = imread( argv[1], 1 );
	if(!g_srcImage.data )
	{ 
		printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ����ͼƬ����~�� \n");
		return false; 
	}  
	imshow("ԭʼͼ",g_srcImage);

	//��2��������ԭʼͼһ����Ч��ͼ��x��ӳ��ͼ��y��ӳ��ͼ
	g_dstImage.create( g_srcImage.size(), g_srcImage.type() );
	g_map_x.create( g_srcImage.size(), CV_32FC1 );
	g_map_y.create( g_srcImage.size(), CV_32FC1 );

	//��3���������ڲ���ʾ
	namedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );
	imshow(WINDOW_NAME,g_srcImage);

	//��4����ѯ����������map_x��map_y��ֵ��������ӳ���������ʾЧ��ͼ
	while( 1 )
	{
		//��ȡ���̰���  
		int key = waitKey(0);//���񰴼�ֵ  

		//�ж�ESC�Ƿ��£������±��˳�  
		if( (key & 255) == 27 )  
		{  
			cout << "�����˳�...........\n";  
			break;  
		}  

		//���ݰ��µļ��̰��������� map_x & map_y��ֵ. Ȼ�����remap( )������ӳ��
		update_map(key);
		remap( g_srcImage, g_dstImage, g_map_x, g_map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

		//��ʾЧ��ͼ
		imshow( WINDOW_NAME, g_dstImage );
	}
	return 0;
}

//-----------------------------------��update_map( )������--------------------------------
//          ���������ݰ���������map_x��map_x��ֵ
//----------------------------------------------------------------------------------------------
int update_map( int key )
{
	//˫��ѭ��������ÿһ�����ص�
	for( int j = 0; j < g_srcImage.rows;j++)
	{ 
		for( int i = 0; i < g_srcImage.cols;i++)
		{
			switch(key)
			{
			case '1': // ���̡�1�������£����е�һ����ӳ�����
				if( i > g_srcImage.cols*0.25 && i < g_srcImage.cols*0.75 && j > g_srcImage.rows*0.25 && j < g_srcImage.rows*0.75)
				{
					g_map_x.at<float>(j,i) = static_cast<float>(2*( i - g_srcImage.cols*0.25 ) + 0.5);//��С
					g_map_y.at<float>(j,i) = static_cast<float>(2*( j - g_srcImage.rows*0.25 ) + 0.5);
				}
				else
				{ 
					g_map_x.at<float>(j,i) = 0;//���
					g_map_y.at<float>(j,i) = 0;
				}
				break;
			case '2':// ���̡�2�������£����еڶ�����ӳ�����
				g_map_x.at<float>(j,i) = static_cast<float>(i);
				g_map_y.at<float>(j,i) = static_cast<float>(g_srcImage.rows - j);//y��Գ�
				break;
			case '3':// ���̡�3�������£����е�������ӳ�����
				g_map_x.at<float>(j,i) = static_cast<float>(g_srcImage.cols - i);//x��Գ�
				g_map_y.at<float>(j,i) = static_cast<float>(j);
				break;
			case '4':// ���̡�4�������£����е�������ӳ�����
				g_map_x.at<float>(j,i) = static_cast<float>(g_srcImage.cols - i);//����ת
				g_map_y.at<float>(j,i) = static_cast<float>(g_srcImage.rows - j);
				break;
			} 
		}
	}
	return 1;
}

//-----------------------------------��ShowHelpText( )������----------------------------------  
//      ���������һЩ������Ϣ  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//���һЩ������Ϣ  
	printf("\n\n\n\t��ӭ������ӳ��ʾ������~\n\n");  
	printf("\t��ǰʹ�õ�OpenCV�汾Ϊ OpenCV "CV_VERSION);  
	printf( "\n\n\t��������˵��: \n\n"  
		"\t\t���̰�����ESC��- �˳�����\n"  
		"\t\t���̰�����1��-  ��һ��ӳ�䷽ʽ\n"  
		"\t\t���̰�����2��- �ڶ���ӳ�䷽ʽ\n"  
		"\t\t���̰�����3��- ������ӳ�䷽ʽ\n"  
		"\t\t���̰�����4��- ������ӳ�䷽ʽ\n"   
		);  
}  