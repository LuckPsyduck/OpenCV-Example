//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//		����������������������ͷ�ļ�
//---------------------------------------------------------------------------------------------- 
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc,char **argv)
{ 
	Mat srcImage = imread(argv[1]); 
	Mat midImage,dstImage;//��ʱ������Ŀ��ͼ�Ķ���

	//��2����ʾԭʼͼ
	imshow("��ԭʼͼ��", srcImage);  

	//��3��תΪ�Ҷ�ͼ������ͼ��ƽ��
	cvtColor(srcImage,midImage, CV_BGR2GRAY);//ת����Ե�����ͼΪ�Ҷ�ͼ
	GaussianBlur( midImage, midImage, Size(9, 9), 2, 2 );

	//��4�����л���Բ�任
	vector<Vec3f> circles;
	HoughCircles( midImage, circles, CV_HOUGH_GRADIENT,1.5, 10, 200, 100, 0, 0 );

	//��5��������ͼ�л��Ƴ�Բ
	for( size_t i = 0; i < circles.size(); i++ )
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//����Բ��
		circle( srcImage, center, 3, Scalar(0,255,0), -1, 8, 0 );
		//����Բ����
		circle( srcImage, center, radius, Scalar(155,50,255), 3, 8, 0 );
	}

	//��6����ʾЧ��ͼ  
	imshow("��Ч��ͼ��", srcImage);  

	waitKey(0);  

	return 0;  
}