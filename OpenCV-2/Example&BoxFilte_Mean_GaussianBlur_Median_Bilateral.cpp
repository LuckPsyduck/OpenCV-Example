//-----------------------------------������˵����----------------------------------------------
//            ��������:������OpenCV���Ž̳�֮�š��������˲�ר������ֵ�˲���˫���˲�  �� ��������Դ��

#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
 
using namespace std;
using namespace cv;
 
Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3,g_dstImage4,g_dstImage5;
int g_nBoxFilterValue=6;  //�����˲��ں�ֵ
int g_nMeanBlurValue=10;  //��ֵ�˲��ں�ֵ
int g_nGaussianBlurValue=6;  //��˹�˲��ں�ֵ
int g_nMedianBlurValue=10;  //��ֵ�˲�����ֵ
int g_nBilateralFilterValue=10;  //˫���˲�����ֵ
 
 
//-----------------------------------��ȫ�ֺ����������֡�--------------------------------------
//            ������ȫ�ֺ�������
//-----------------------------------------------------------------------------------------------
//�켣���ص�����
static void on_BoxFilter(int, void *);            //�����˲�
static void on_MeanBlur(int, void *);           //��ֵ���˲���
static void on_GaussianBlur(int, void *);                    //��˹�˲���
static void on_MedianBlur(int, void *);               //��ֵ�˲���
static void on_BilateralFilter(int, void*);                    //˫���˲���
 
//-----------------------------------��main( )������--------------------------------------------
//            ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ
//-----------------------------------------------------------------------------------------------
int main(int argc,char **argv)
{
       system("color 5E"); 
 
       //����ԭͼ
       g_srcImage= imread( argv[1], 1 );
       if(!g_srcImage.data )
	   {
		   cout<<"Oh��no����ȡsrcImage����~��\n"<<endl; 
		   return false; 
	   }
 
       //��¡ԭͼ���ĸ�Mat������
       g_dstImage1= g_srcImage.clone( );
       g_dstImage2= g_srcImage.clone( );
       g_dstImage3= g_srcImage.clone( );
       g_dstImage4= g_srcImage.clone( );
       g_dstImage5= g_srcImage.clone( );
 
       //��ʾԭͼ
       namedWindow("��<0>ԭͼ���ڡ�", 0);
       imshow("��<0>ԭͼ���ڡ�",g_srcImage);
 
 
       //=================��<1>�����˲���=========================
       //��������
       namedWindow("��<1>�����˲���", 0);
       //�����켣��
       createTrackbar("�ں�ֵ��", "��<1>�����˲���",&g_nBoxFilterValue, 50,on_BoxFilter );
       on_BoxFilter(g_nBoxFilterValue,0);
       imshow("��<1>�����˲���", g_dstImage1);
       //=====================================================
 
 
       //=================��<2>��ֵ�˲���==========================
       //��������
       namedWindow("��<2>��ֵ�˲���", 0);
       //�����켣��
       createTrackbar("�ں�ֵ��", "��<2>��ֵ�˲���",&g_nMeanBlurValue, 50,on_MeanBlur );
       on_MeanBlur(g_nMeanBlurValue,0);
       //======================================================
 
 
       //=================��<3>��˹�˲���===========================
       //��������
       namedWindow("��<3>��˹�˲���", 0);
       //�����켣��
       createTrackbar("�ں�ֵ��", "��<3>��˹�˲���",&g_nGaussianBlurValue, 50,on_GaussianBlur );
       on_GaussianBlur(g_nGaussianBlurValue,0);
       //=======================================================
 
 
       //=================��<4>��ֵ�˲���===========================
       //��������
       namedWindow("��<4>��ֵ�˲���", 0);
       //�����켣��
       createTrackbar("����ֵ��", "��<4>��ֵ�˲���",&g_nMedianBlurValue, 50,on_MedianBlur );
       on_MedianBlur(g_nMedianBlurValue,0);
       //=======================================================
 
 
       //=================��<5>˫���˲���===========================
       //��������
       namedWindow("��<5>˫���˲���", 0);
       //�����켣��
       createTrackbar("����ֵ��", "��<5>˫���˲���",&g_nBilateralFilterValue, 50,on_BilateralFilter);
       on_BilateralFilter(g_nBilateralFilterValue,0);
       //=======================================================
 
 
       //���һЩ������Ϣ
       cout<<endl<<"\t�š����ˣ�������������۲�ͼ��Ч��~\n\n"
              <<"\t���¡�q����ʱ�������˳�~!\n";

       while(char(waitKey(1))!= 'q') {}
 
       return 0;
}
 
//-----------------------------��on_BoxFilter( )������------------------------------------
//            �����������˲������Ļص�����
//-----------------------------------------------------------------------------------------------
static void on_BoxFilter(int, void *)
{
       //�����˲�����
       boxFilter(g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));
       //��ʾ����
       imshow("��<1>�����˲���", g_dstImage1);
}
 
//-----------------------------��on_MeanBlur( )������------------------------------------
//            ��������ֵ�˲������Ļص�����
//-----------------------------------------------------------------------------------------------
static void on_MeanBlur(int, void *)
{
       blur(g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1),Point(-1,-1));
       imshow("��<2>��ֵ�˲���", g_dstImage2);
 
}
 
//-----------------------------��on_GaussianBlur( )������------------------------------------
//            ��������˹�˲������Ļص�����
//-----------------------------------------------------------------------------------------------
static void on_GaussianBlur(int, void *)
{
       GaussianBlur(g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1 ), 0, 0);
       imshow("��<3>��˹�˲���", g_dstImage3);
}
 
 
//-----------------------------��on_MedianBlur( )������------------------------------------
//            ��������ֵ�˲������Ļص�����
//-----------------------------------------------------------------------------------------------
static void on_MedianBlur(int, void *)
{
       medianBlur( g_srcImage, g_dstImage4, g_nMedianBlurValue*2+1 );
       imshow("��<4>��ֵ�˲���", g_dstImage4);
}
 
 
//-----------------------------��on_BilateralFilter( )������------------------------------------
//            ������˫���˲������Ļص�����
//-----------------------------------------------------------------------------------------------
static void on_BilateralFilter(int, void *)
{
       bilateralFilter( g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2,g_nBilateralFilterValue/2 );
       imshow("��<5>˫���˲���", g_dstImage5);
}