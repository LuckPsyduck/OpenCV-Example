//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//		����������������������ͷ�ļ�
//---------------------------------------------------------------------------------------------- 
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char **argv)
{
	//����ԭʼͼ   
	Mat srcImage = imread(argv[1]);  
	Mat tmpImage,dstImage;//��ʱ������Ŀ��ͼ�Ķ���
	tmpImage=srcImage;//��ԭʼͼ������ʱ����

	//��ʾԭʼͼ  
	imshow("��ԭʼͼ��", srcImage);  
	//��������ȡ������
	pyrUp( tmpImage, dstImage, Size( tmpImage.cols*2, tmpImage.rows*2 ) );
	//��ʾЧ��ͼ  
	imshow("��Ч��ͼ��", dstImage);  

	waitKey(0);  

	return 0;  
}
