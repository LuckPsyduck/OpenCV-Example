#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//ȫ�ֱ���
String src_windowName = "ԭͼ��";
String warp_windowName = "����任";
String warp_rotate_windowName = "������ת�任";
String rotate_windowName = "ͼ����ת";

int main(int argc,char **argv)
{
	Point2f srcTri[3];
	Point2f dstTri[3];

	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat srcImage, warp_dstImage, warp_rotate_dstImage, rotate_dstImage;

	//����ͼ��
	srcImage = imread(argv[1]);

	//�ж��ļ��Ƿ���سɹ�
	if(srcImage.empty())
	{
		cout << "ͼ�����ʧ��!" << endl;
		return -1;
	}
	else
		cout << "ͼ����سɹ�!" << endl << endl;

	//��������任Ŀ��ͼ����ԭͼ��ߴ�������ͬ
	warp_dstImage = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

	//�������������������任
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(srcImage.cols - 1, 0);
	srcTri[2] = Point2f(0, srcImage.rows - 1);

	dstTri[0] = Point2f(srcImage.cols*0.0, srcImage.rows*0.33);
	dstTri[1] = Point2f(srcImage.cols*0.85, srcImage.rows*0.25);
	dstTri[2] = Point2f(srcImage.cols*0.15, srcImage.rows*0.7);

	//�������任����
	warp_mat = getAffineTransform(srcTri, dstTri);

	//�Լ���ͼ�ν��з���任����
	warpAffine(srcImage, warp_dstImage, warp_mat, warp_dstImage.size());

	//����ͼ���е�˳ʱ����ת50�ȣ���������Ϊ0.6����ת����
	Point center = Point(warp_dstImage.cols/2, warp_dstImage.rows/2);
	double angle = -50.0;
	double scale = 0.6;

	//������ת����
	rot_mat = getRotationMatrix2D(center, angle, scale);

	//��ת��Ť��ͼ��
	warpAffine(warp_dstImage, warp_rotate_dstImage, rot_mat, warp_dstImage.size());

	//��ԭͼ����ת
	warpAffine(srcImage, rotate_dstImage, rot_mat, srcImage.size());

	//��ʾ�任���
	namedWindow(src_windowName, WINDOW_AUTOSIZE);
	imshow(src_windowName, srcImage);

	namedWindow(warp_windowName, WINDOW_AUTOSIZE);
	imshow(warp_windowName, warp_dstImage);

	namedWindow(warp_rotate_windowName, WINDOW_AUTOSIZE);
	imshow(warp_rotate_windowName, warp_rotate_dstImage);

	namedWindow(rotate_windowName, WINDOW_AUTOSIZE);
	imshow(rotate_windowName, rotate_dstImage);

	waitKey(0);

	return 0;
}
