//-----------------------------------������˵����----------------------------------------------
//            ˵������˫���˲�bilateralFilter������ʹ��ʾ������

#include "opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc,char **argv)
{
       //����ԭͼ
       Mat image=imread(argv[1]);
 
       //��������
       namedWindow("˫���˲���ԭͼ��" );
       namedWindow("˫���˲���Ч��ͼ��");
 
       //��ʾԭͼ
       imshow("˫���˲���ԭͼ��", image );
 
       //����˫���˲�����
       Mat out;
       bilateralFilter( image, out, 25, 25*2, 25/2 );
 
       //��ʾЧ��ͼ
       imshow("˫���˲���Ч��ͼ��" ,out );
 
       waitKey(0 );    
}