#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
const int sobel_kernel_size_maxValue = 3;   //kernel�ߴ����ֵ
int sobel_kernel_size_value;                //kernel�ߴ�

Mat srcImage, dstImage, grayImage, x_gradImage, y_gradImage;
Mat x_abs_gradImage, y_abs_gradImage;
String windowName = "Sobel���ӱ�Ե���";

int depth = 0;      //���ͼ����ԭͼ��һ��
int scale = 1;      //��ѡ��������
int delta = 0;      //��ѡ��delta

//�����켣���ص�����
void sobelFun(int, void*);

int main(int argc,char **argv)
{
    srcImage = imread(argv[1]);

    //�ж�ͼ���Ƿ���سɹ�
    if(srcImage.empty())
    {
        cout << "ͼ�����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼ����سɹ�!" << endl << endl;

    //��˹�˲�
	// If both sigmas are zeros, they are computed from ksize.width and ksize.height , respectively. 
    GaussianBlur(srcImage, srcImage, Size(3, 3), 0, 0, BORDER_DEFAULT);

    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);   //ͼ��ת���Ҷ�ͼ
    namedWindow("ԭͼ��Ҷ�ͼ", WINDOW_AUTOSIZE);
    imshow("ԭͼ��Ҷ�ͼ", grayImage);

    namedWindow(windowName, WINDOW_AUTOSIZE);       //��������

    //���ù켣������
    sobel_kernel_size_value = 1;
    char kernelSizeName [20];
    sprintf(kernelSizeName, "Sobel����kernel�ߴ�", sobel_kernel_size_maxValue);

    //�����켣��
    createTrackbar(kernelSizeName, windowName, &sobel_kernel_size_value,
                    sobel_kernel_size_maxValue, sobelFun);

    //���ûص�����
    sobelFun(sobel_kernel_size_value, 0);

    waitKey(0);

    return 0;
}

//�ص�����
void sobelFun(int, void*)
{
    //���¼���ߴ�kernel�ߴ���ֵ
    int kernelvalue;
    kernelvalue = sobel_kernel_size_value * 2 + 1;

    //����x�����ݶ�
	/*
	CV_EXPORTS_W void Sobel( InputArray src, OutputArray dst, int ddepth,
                         int dx, int dy, int ksize=3,
                         double scale=1, double delta=0,
                         int borderType=BORDER_DEFAULT );
	*/
    Sobel(grayImage, x_gradImage, depth, 1, 0, kernelvalue, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(x_gradImage, x_abs_gradImage);
    namedWindow("x�����sobel��Ե���", WINDOW_AUTOSIZE);
    imshow("x�����sobel��Ե���", x_abs_gradImage);

    //����y�����ݶ�
    Sobel(grayImage, y_gradImage, depth, 0, 1, kernelvalue, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(y_gradImage, y_abs_gradImage);
    namedWindow("y�����ϵ�sobel��Ե���", WINDOW_AUTOSIZE);
    imshow("y�����ϵ�sobel��Ե���", y_abs_gradImage);

    //��x�����y������ݶȵ���
    addWeighted(x_abs_gradImage, 0.5, y_abs_gradImage, 0.5, 0, dstImage);


    imshow(windowName, dstImage);
}
