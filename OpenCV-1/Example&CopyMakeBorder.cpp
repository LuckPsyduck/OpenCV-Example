/*����˵��
 *�����°�����c������ʹ��BORDER_CONSTANT,ʹ��һ������������ر�Ե 
 *RNG���ɵ��������Ϊ����ֵ�������
 *�����°�����r������ʹ��BORDER_REPLICATE
 *ͼ������ı߿���ԭͼ���Ե���ص�ֵ�������
 */
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat srcImage, dstImage;
int g_top, g_bottom, g_left, g_right;
int borderType;
Scalar value;
String windowName = "copyMakeBorder Demo";
RNG rng(12345);//�� ����һ������

int main(int argc,char **argv)
{
    int c;

    srcImage = imread(argv[1]);

    //�ж�ͼ���Ƿ���سɹ�
    if(srcImage.empty())
    {
        cout << "ͼ�����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼ����سɹ�" << endl << endl;
    imshow("ԭͼ��", srcImage);

    //����ʹ��˵��
    printf("\n \t copyMakeBorder Demo: \n");
    printf("\t --------------------\n");
    printf("**Press 'c' to set the border to a random constant value \n");
    printf("**Press 'r' to set the border to be replicated \n");
    printf("**Press 'ESC' to exit the program \n");

    //��������
    namedWindow(windowName, WINDOW_AUTOSIZE);

    //��ʼ���߿����
    g_top = (int)(0.05*srcImage.rows);
    g_bottom = (int)(0.05*srcImage.rows);
    g_left = (int)(0.05*srcImage.cols);
    g_right = (int)(0.05*srcImage.cols);

    //��ʾ��ʼͼ��
    dstImage = srcImage;    
    imshow(windowName, dstImage);

    while(true)
    {
        c = waitKey(500);

        if((char)c == 27)   //cΪESC�����˳�
			break;
        else if((char)c == 'c')
			borderType = BORDER_CONSTANT;
        else if((char)c == 'r')
			borderType = BORDER_REPLICATE;

		//��������� ���ȷֲ�
        value = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));//������ɫ
		/*
		CV_EXPORTS_W void copyMakeBorder( InputArray src, OutputArray dst,
                                int top, int bottom, int left, int right,
                                int borderType, const Scalar& value=Scalar() );
		*/
        copyMakeBorder(srcImage, dstImage, g_top, g_bottom, g_left, g_right, borderType, value);

        imshow(windowName, dstImage);
    }

    return 0;
}
