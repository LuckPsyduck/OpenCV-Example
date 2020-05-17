//-----------------------------------������˵����---------------------------------------------- &nbsp;
// &nbsp; &nbsp; &nbsp;��������:������OpenCV���Ž̳�֮ʮ�ˡ�OpenCV����任 & SURF�����������ϼ��� ��������Դ�� ֮ ����任

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include<opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace cv;
using namespace std;

static void ShowHelpText( );//�����������

int main(int argc,char **argv)
{
	//��0���ı�console������ɫ
	system("color 1A"); 

	//��0����ʾ��ӭ�Ͱ�������
	ShowHelpText( );

	//��1�������ز�ͼ
	Mat srcImage1 = imread(argv[1],1);
	Mat srcImage2 = imread(argv[2],1);
	if( !srcImage1.data || !srcImage2.data )
	{ 
		printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ����ͼƬ����~�� \n"); 
		return false; 
	}  

	//��2��ʹ��SURF���Ӽ��ؼ���
	int minHessian = 700;//SURF�㷨�е�hessian��ֵ
	SurfFeatureDetector detector( minHessian );//����һ��SurfFeatureDetector��SURF�� ������������  
	std::vector<KeyPoint> keyPoint1, keyPoints2;//vectorģ���࣬����������͵Ķ�̬����

	//��3������detect��������SURF�����ؼ��㣬������vector������
	detector.detect( srcImage1, keyPoint1 );
	detector.detect( srcImage2, keyPoints2 );

	//��4������������������������
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute( srcImage1, keyPoint1, descriptors1 );
	extractor.compute( srcImage2, keyPoints2, descriptors2 );

	//��5��ʹ��BruteForce����ƥ��
	// ʵ����һ��ƥ����
	BruteForceMatcher< L2<float> > matcher;
	std::vector< DMatch > matches;
	//ƥ������ͼ�е������ӣ�descriptors��
	matcher.match( descriptors1, descriptors2, matches );

	//��6�����ƴ�����ͼ����ƥ����Ĺؼ���
	Mat imgMatches;
	drawMatches( srcImage1, keyPoint1, srcImage2, keyPoints2, matches, imgMatches );//���л���

	//��7����ʾЧ��ͼ
	imshow("ƥ��ͼ", imgMatches );

	waitKey(0);
	return 0;
}

//-----------------------------------��ShowHelpText( )������----------------------------------  
//      ���������һЩ������Ϣ  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//���һЩ������Ϣ  
	printf(  "\n\n\n\t��ӭ������SURF����������ʾ������~\n\n");  
	printf("\t��ǰʹ�õ�OpenCV�汾Ϊ OpenCV "CV_VERSION);  
}  