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
	Mat tmpImage,dstImage1,dstImage2;//��ʱ������Ŀ��ͼ�Ķ���
	tmpImage=srcImage;//��ԭʼͼ������ʱ����

	//��ʾԭʼͼ  
	imshow("��ԭʼͼ��", srcImage);  

	//���гߴ��������
	resize(tmpImage,dstImage1,Size( tmpImage.cols/2, tmpImage.rows/2 ),(0,0),(0,0),3);//�����ֵ��
	resize(tmpImage,dstImage2,Size( tmpImage.cols*2, tmpImage.rows*2 ),(0,0),(0,0),3);

	//��ʾЧ��ͼ  
	imshow("��Ч��ͼ��֮һ", dstImage1);  
	imshow("��Ч��ͼ��֮��", dstImage2);  

	waitKey(0);  
	return 0;  
}