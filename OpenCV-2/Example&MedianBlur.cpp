//-----------------------------------������˵����----------------------------------------------
//            ˵��������ֵ�˲�medianBlur������ʹ��ʾ������

#include "opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc,char **argv)
{
	//����ԭͼ
	Mat image=imread(argv[1]);

	//��������
	namedWindow("��ֵ�˲���ԭͼ��" );
	namedWindow("��ֵ�˲���Ч��ͼ��");

	//��ʾԭͼ
	imshow("��ֵ�˲���ԭͼ��", image );

	//������ֵ�˲�����
	Mat out;
	medianBlur( image, out, 7);

	//��ʾЧ��ͼ
	imshow("��ֵ�˲���Ч��ͼ��" ,out );

	waitKey(0 );    
}