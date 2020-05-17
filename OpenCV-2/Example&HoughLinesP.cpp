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

	//��2�����б�Ե����ת��Ϊ�Ҷ�ͼ
	Canny(srcImage, midImage, 50, 200, 3);//����һ��canny��Ե���
	cvtColor(midImage,dstImage, CV_GRAY2BGR);//ת����Ե�����ͼΪ�Ҷ�ͼ

	//��3�����л����߱任
	vector<Vec4i> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	//! finds line segments in the black-n-white image using probabilistic Hough transform
//CV_EXPORTS_W void HoughLinesP( InputArray image, OutputArray lines,
//                               double rho, double theta, int threshold,
//                               double minLineLength=0, double maxLineGap=0 );
	HoughLinesP(midImage, lines, 1, CV_PI/180, 80, 50, 10 );

	//��4��������ͼ�л��Ƴ�ÿ���߶�
	for( size_t i = 0; i < lines.size(); i++ )
	{
		Vec4i l = lines[i];                                           //BGR
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186,88,255), 1, CV_AA);
	}

	//��5����ʾԭʼͼ  
	imshow("��ԭʼͼ��", srcImage);  

	//��6����Ե�����ͼ 
	imshow("����Ե�����ͼ��", midImage);  

	//��7����ʾЧ��ͼ  
	imshow("��Ч��ͼ��", dstImage);  

	waitKey(0);  

	return 0;  
}