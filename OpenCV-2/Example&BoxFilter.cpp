//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//     ����������������������ͷ�ļ�
//----------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"

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
	   //CV_EXPORTS void boxFilter(const GpuMat& src, GpuMat& dst, int ddepth, \
	   Size ksize, Point anchor = Point(-1,-1), Stream& stream = Stream::Null());
       boxFilter(image, out, -1,Size(5, 5));//the output image depth (-1 to use src.depth()). 
 
       //��ʾЧ��ͼ
       imshow("��ֵ�˲���Ч��ͼ��" ,out );
 
       waitKey(0 );    
}