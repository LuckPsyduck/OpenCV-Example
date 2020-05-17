#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
const int g_ndMaxValue = 100;
const int g_nsigmaColorMaxValue = 200;
const int g_nsigmaSpaceMaxValue = 200;

int g_ndValue;
int g_nsigmaColorValue;
int g_nsigmaSpaceValue;

Mat g_srcImage;
Mat g_dstImage;

//����ص�����
void on_bilateralFilterTrackbar(int, void*);

int main(int argc,char **argv)
{
    g_srcImage = imread(argv[1]);

    //�ж�ͼ���Ƿ���سɹ�
    if(g_srcImage.empty())
    {
        cout << "ͼ�����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼ����سɹ�!" << endl << endl;

    namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
    imshow("ԭͼ��", g_srcImage);

    //�������ͼ�񴰿����Ժ͹켣������
    namedWindow("˫���˲�ͼ��", WINDOW_AUTOSIZE);
    g_ndValue = 10;
    g_nsigmaColorValue = 10;
    g_nsigmaSpaceValue = 10;

    char dName[20];
    sprintf(dName, "����ֱ�� %d", g_ndMaxValue);

    char sigmaColorName[20];
    sprintf(sigmaColorName, "sigmaColor %d", g_nsigmaColorMaxValue);

    char sigmaSpaceName[20];
    sprintf(sigmaSpaceName, "sigmaSpace %d", g_nsigmaSpaceMaxValue);

    //�����켣��
    createTrackbar(dName, "˫���˲�ͼ��", &g_ndValue, g_ndMaxValue, on_bilateralFilterTrackbar);
    on_bilateralFilterTrackbar(g_ndValue, 0);

    createTrackbar(sigmaColorName, "˫���˲�ͼ��", &g_nsigmaColorValue,
                     g_nsigmaColorMaxValue, on_bilateralFilterTrackbar);
    on_bilateralFilterTrackbar(g_nsigmaColorValue, 0);

    createTrackbar(sigmaSpaceName, "˫���˲�ͼ��", &g_nsigmaSpaceValue,
                    g_nsigmaSpaceMaxValue, on_bilateralFilterTrackbar);
    on_bilateralFilterTrackbar(g_nsigmaSpaceValue, 0);

    waitKey(0);

    return 0;
}

void on_bilateralFilterTrackbar(int, void*)
{
    bilateralFilter(g_srcImage, g_dstImage, g_ndValue, g_nsigmaColorValue, g_nsigmaSpaceValue);
    imshow("˫���˲�ͼ��", g_dstImage);
}