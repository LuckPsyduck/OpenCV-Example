/*
 *������Ҫ��ʾ�˲�ͬ�Ĳ�ֵ�㷨��ͼ��������Ч����ͬ
 *����ͼ��Ŵ�ͼ��ԭͼ���õ�����С���ͼ��
 *Ҳ���Խ�g_shrinkImage��Ϊg_srcImage�۲�ֱ�Ӵ�ԭͼ��Ŵ�Ч��
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat g_srcImage;
Mat g_shrinkImage;
Mat g_enlargeImage;

//����켣������
const int resizeTypeMaxValue = 4;   //�����ֲ�ֵ��������
int resizeTypeValue = 0;

//��������ת������
int typeDef(int typeNum);

//�����ص�����
void shrinkFun(int, void*);
void enlargeFun(int, void*);

int main(int argc,char **argv)
{
    g_srcImage = imread(argv[1]);

    //�ж��ļ��Ƿ���سɹ�
    if(!g_srcImage.data)
    {
        cout << "ͼ�����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼ����سɹ�!" << endl << endl;

    namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
    imshow("ԭͼ��", g_srcImage);

    //�켣������
    char resizeTypeName[20];
    sprintf(resizeTypeName, "��ֵ�������� %d", resizeTypeMaxValue);

    namedWindow("ͼ����С", WINDOW_AUTOSIZE);
    namedWindow("ͼ��Ŵ�", WINDOW_AUTOSIZE);

    //�����켣��
    createTrackbar(resizeTypeName, "ͼ����С", &resizeTypeValue, resizeTypeMaxValue, shrinkFun);
    shrinkFun(resizeTypeValue, 0);

    createTrackbar(resizeTypeName, "ͼ��Ŵ�", &resizeTypeValue, resizeTypeMaxValue, enlargeFun);
    enlargeFun(resizeTypeValue, 0);

    waitKey(0);

    return 0;
}

int typeDef(int typeNum)
{
    int type;

    switch(typeNum)
    {
    case 0:
            type = INTER_NEAREST; break;
    case 1:
            type = INTER_LINEAR; break;
    case 2:
            type = INTER_CUBIC; break;
    case 3:
            type = INTER_AREA; break;
    case 4:
            type = INTER_LANCZOS4; break;//���ڵ���8*8
    default:
            break;
    }

    return type;

}

//ͼ����С����
void shrinkFun(int, void*)
{
    int shrinkType;
    shrinkType = typeDef(resizeTypeValue);
    resize(g_srcImage, g_shrinkImage, Size(g_srcImage.cols/2, g_srcImage.rows/2), 0, 0, shrinkType);
    imshow("ͼ����С", g_shrinkImage);
}

//ͼ��Ŵ���
void enlargeFun(int, void*)
{
    int enlargeType;
    enlargeType = typeDef(resizeTypeValue);
    resize(g_shrinkImage, g_enlargeImage, Size(g_shrinkImage.cols*2, g_shrinkImage.rows*2), 0, 0, enlargeType);
    imshow("ͼ��Ŵ�", g_enlargeImage);
}
