//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//     ����������������������ͷ�ļ�
//----------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;

int main( )
{
       //����ԭͼ
       Mat image=imread("a.jpg");
 
       //��������
       namedWindow("��ֵ�˲���ԭͼ��" );
       namedWindow("��ֵ�˲���Ч��ͼ��");
 
       //��ʾԭͼ
       imshow("��ֵ�˲���ԭͼ��", image );
 
       //�����˲�����
       Mat out;
       blur(image, out, /*Size(7, 7)*/Size(5, 5));
 
       //��ʾЧ��ͼ
       imshow("��ֵ�˲���Ч��ͼ��" ,out );
 
       waitKey(0 );    
}