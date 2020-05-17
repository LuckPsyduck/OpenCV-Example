#include<cv.h>  
#include<highgui.h>  
#include<stdio.h>  
void main()
{
	IplImage* img_src = 0;
	IplImage* img_dst = 0;
	char* pictureImage = (char*)("smooth.jpg");
	img_src = cvLoadImage(pictureImage, 1);
	
	if (!img_src)
	{
		printf("Could not load image file:%s", pictureImage);
		exit(0);
	}
	img_dst = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_8U, 3);

	cvNamedWindow("ԭʼͼ��:", 0);
	cvMoveWindow("ԭʼͼ��:", 100, 100);
	cvShowImage("ԭʼͼ��:", img_src);

	cvNamedWindow("��ģ��:", 0);
	cvMoveWindow("��ģ��:", 200, 100);

	//(simple blur)��ģ��- -��ÿ������param1��param2������Ͳ����߶ȱ任 1/(param1��param2)��
	cvSmooth(img_src, img_dst, CV_BLUR, 3, 3, 0, 0);
	cvShowImage("��ģ��:", img_dst);

	//ע��ʹ��CV_BLUR_NO_SCALEʱ��ԭʼͼ���Ŀ��ͼ��,���ǵ����Ͳ�����һ�µġ�
	IplImage* img_dst2 = 0;
	img_dst2 = cvCreateImage(cvGetSize(img_src), IPL_DEPTH_16S, 3);
	cvNamedWindow("�򵥲����߶ȱ任��ģ��:", 0);
	cvMoveWindow("�򵥲����߶ȱ任��ģ��:", 300, 100);

	//(�򵥲����߶ȱ任��ģ��)-��ÿ�����ص� param1��param2 ������͡�\
	��������С�Ǳ仯��,�����������ú��� cvIntegral �������ͼ��
	cvSmooth(img_src, img_dst2, CV_BLUR_NO_SCALE, 3, 3, 0, 0);
	cvShowImage("�򵥲����߶ȱ任��ģ��:", img_dst2);

	cvNamedWindow("��˹���:", 0);//��ͼ����к˴�СΪ param1��param2 �ĸ�˹�����
	cvMoveWindow("��˹���:", 400, 100);
	cvSmooth(img_src, img_dst, CV_GAUSSIAN, 3, 3, 0, 0);
	cvShowImage("��˹���:", img_dst);

	cvNamedWindow("��ֵ�˲�:", 0);//��ͼ����к˴�СΪparam1��param1 ����ֵ�˲� (�����Ƿ���)��
	cvMoveWindow("��ֵ�˲�:", 500, 100);
	cvSmooth(img_src, img_dst, CV_MEDIAN, 3, 3, 0, 0);
	cvShowImage("��ֵ�˲�:", img_dst);

	//  cvSmooth(pFrameMat,pFrameMat,CV_BILATERAL,3,0,0);//˫���˲�  
	//�������ԣ��ĳ�  
	//cvSmooth(pFrameMat,pFrameMat,CV_BILATERAL,3,3,11,11);  
	//���ԣ��������������ֱ������λ���Ϻ���ɫ�ϵ�sigmaֵ��������Ϊ0��  
	cvNamedWindow("˫���˲�:", 0);
	cvMoveWindow("˫���˲�:", 600, 100);

	//(˫���˲�) - -Ӧ��˫�� 3x3 �˲�����ɫ sigma=param1���ռ� sigma=param2.��
	cvSmooth(img_src, img_dst, CV_BILATERAL, 3, 3, 11, 11);
	cvShowImage("˫���˲�:", img_dst);

	cvWaitKey(0);
	cvReleaseImage(&img_src);
	cvReleaseImage(&img_dst);
	cvDestroyWindow("ԭʼͼ��:");
	cvDestroyWindow("�򵥲����߶ȱ任��ģ��:");
	cvDestroyWindow("��˹���:");
	cvDestroyWindow("��ֵ�˲�:");
	cvDestroyWindow("˫���˲�:");
}