/*
 *�����򽫻����5��Ŀ��ͼƬ��ԭͼ����жԱ�
 *ÿ��ͼ����õ�ģ��Type��Size����ͨ���켣�����е���
 *������ȤҲ�ɳ���ʹ�ù켣���ı���̬ѧ���������Ϳɴ�����ٴ�����
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat g_srcImage;
Mat g_dstImageOpen, g_dstImageClose, g_dstImageGradient;
Mat g_dstImageTopHat, g_dstImageBlackHat;

//���������켣������
const int kernelTypeMaxValue = 2;
const int kernelSizeMaxValue = 20;
int kernelTypeValue = 1;
int kernelSizeValue = 10;

//����ģ��������������
int kernelTypeFun(int kernelTypeValue);

//���������ص�����
void openOperation(int, void*);
void closeOperation(int, void*);
void gradientOperation(int, void*);
void topHatOperation(int, void*);
void blackHatOperation(int, void*);

int main(int argc,char **argv)
{
    g_srcImage = imread(argv[1]);

    //�ж�ͼ���Ƿ���سɹ�
    if(!g_srcImage.data)
    {
        cout << "ͼ�����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼ����سɹ�!" << endl << endl;

    namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
    imshow("ԭͼ��", g_srcImage);

    //����켣������
    char kernelTypeName[20];
    char kernelSizeName[20];

    sprintf(kernelTypeName, "ģ������ %d\n 0-Rect 1-Cross 2-Ellipse", kernelTypeMaxValue);
    sprintf(kernelSizeName, "ģ��ߴ� %d", kernelSizeMaxValue);

    namedWindow("������", WINDOW_AUTOSIZE);
    namedWindow("������", WINDOW_AUTOSIZE);
    namedWindow("��̬ѧ�ݶ�", WINDOW_AUTOSIZE);
    namedWindow("��ñ", WINDOW_AUTOSIZE);
    namedWindow("��ñ", WINDOW_AUTOSIZE);

    //���������켣��
    createTrackbar(kernelTypeName, "������", &kernelTypeValue, kernelTypeMaxValue, openOperation);
    createTrackbar(kernelSizeName, "������", &kernelSizeValue, kernelSizeMaxValue, openOperation);

    openOperation(kernelTypeValue, 0);
    openOperation(kernelSizeValue, 0);

    createTrackbar(kernelTypeName, "������", &kernelTypeValue, kernelTypeMaxValue, closeOperation);
    createTrackbar(kernelSizeName, "������", &kernelSizeValue, kernelSizeMaxValue, closeOperation);
    openOperation(kernelTypeValue, 0);
    openOperation(kernelSizeValue, 0);

    createTrackbar(kernelTypeName, "��̬ѧ�ݶ�", &kernelTypeValue, kernelTypeMaxValue, gradientOperation);
    createTrackbar(kernelSizeName, "��̬ѧ�ݶ�", &kernelSizeValue, kernelSizeMaxValue, gradientOperation);
    openOperation(kernelTypeValue, 0);
    openOperation(kernelSizeValue, 0);

    createTrackbar(kernelTypeName, "��ñ", &kernelTypeValue, kernelTypeMaxValue, topHatOperation);
    createTrackbar(kernelSizeName, "��ñ", &kernelSizeValue, kernelSizeMaxValue, topHatOperation);
    openOperation(kernelTypeValue, 0);
    openOperation(kernelSizeValue, 0);

    createTrackbar(kernelTypeName, "��ñ", &kernelTypeValue, kernelTypeMaxValue, blackHatOperation);
    createTrackbar(kernelSizeName, "��ñ", &kernelSizeValue, kernelSizeMaxValue, blackHatOperation);
    openOperation(kernelTypeValue, 0);
    openOperation(kernelSizeValue, 0);

    waitKey(0);

    return 0;
}

//��̬ѧ����ģ�������ж�
int kernelTypeFun(int kernelTypeValue)
{
    int kernel_type;
    if(kernelTypeValue == 0)
        kernel_type = MORPH_RECT;
    else if(kernelTypeValue == 1)
        kernel_type = MORPH_CROSS;
    else
        kernel_type = MORPH_ELLIPSE;

    return kernel_type;
}

//������
void openOperation(int, void*)
{
    int kernel_type;
    kernel_type = kernelTypeFun(kernelTypeValue);//ȫ�ֱ���

	//CV_EXPORTS_W Mat getStructuringElement(int shape, Size ksize, Point anchor=Point(-1,-1));
    Mat element = getStructuringElement(kernel_type, Size(kernelSizeValue * 2 + 1,
                    kernelSizeValue * 2 + 1));
    morphologyEx(g_srcImage, g_dstImageOpen, MORPH_OPEN, element);
    imshow("������", g_dstImageOpen);
}

//������
void closeOperation(int, void*)
{
    int kernel_type;
    kernel_type = kernelTypeFun(kernelTypeValue);

    Mat element = getStructuringElement(kernel_type, Size(kernelSizeValue * 2 + 1,
                    kernelSizeValue * 2 + 1));
    morphologyEx(g_srcImage, g_dstImageClose, MORPH_CLOSE, element);
    imshow("������", g_dstImageClose);
}

//��̬ѧ�ݶ�
void gradientOperation(int, void*)
{
    int kernel_type;
    kernel_type = kernelTypeFun(kernelTypeValue);

    Mat element = getStructuringElement(kernel_type, Size(kernelSizeValue * 2 + 1,
                    kernelSizeValue * 2 + 1));
    morphologyEx(g_srcImage, g_dstImageGradient, MORPH_GRADIENT, element);
    imshow("��̬ѧ�ݶ�", g_dstImageGradient);
}

//��ñ
void topHatOperation(int, void*)
{
    int kernel_type;
    kernel_type = kernelTypeFun(kernelTypeValue);

    Mat element = getStructuringElement(kernel_type, Size(kernelSizeValue * 2 + 1,
                    kernelSizeValue * 2 + 1));
    morphologyEx(g_srcImage, g_dstImageTopHat, MORPH_TOPHAT, element);
    imshow("��ñ", g_dstImageTopHat);
}

//��ñ
void blackHatOperation(int, void*)
{
    int kernel_type;
    kernel_type = kernelTypeFun(kernelTypeValue);

    Mat element = getStructuringElement(kernel_type, Size(kernelSizeValue * 2 + 1,
                    kernelSizeValue * 2 + 1));
    morphologyEx(g_srcImage, g_dstImageBlackHat, MORPH_BLACKHAT, element);
    imshow("��ñ", g_dstImageBlackHat);
}