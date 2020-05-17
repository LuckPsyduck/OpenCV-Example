/*
 *�������Ŀ��ּ�ڶ�ǰ����ܵ��˲�������һ���Ƚ�
 *�Ա�ÿ���˲������˲�Ч���ͺ�ʱ
 *��˫���˲��������˲���kernel����5*5��5
 *����˫���˲���ȡ��ֱ������ֵ30
 *sigmaColor��sigmaSpace��ֵ����ֱ���������
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    Mat srcImage = imread(argv[1]);

    if(srcImage.empty())
    {
        cout << "ͼƬ����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼƬ���سɹ�!" << endl << endl;

    namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
    imshow("ԭͼ��", srcImage);

    /********************�����˲�*******************/
    Mat dstImage_boxFilter;
    double time_boxFilter = static_cast<double>(getTickCount());//����ִ��ʱ��
    boxFilter(srcImage, dstImage_boxFilter, -1, Size(5, 5));
    time_boxFilter = ((double)getTickCount()-time_boxFilter)/getTickFrequency();
    cout << "�����˲���ʱ: " << time_boxFilter << " s" << endl;
    namedWindow("�����˲�ͼ��", WINDOW_AUTOSIZE);
    imshow("�����˲�ͼ��", dstImage_boxFilter);

    /********************��ֵ�˲�*****************/
    Mat dstImage_blur;
    double time_blur = static_cast<double>(getTickCount());
    blur(srcImage, dstImage_blur, Size(5, 5));
    time_blur = ((double)getTickCount()-time_blur)/getTickFrequency();
    cout << "��ֵ�˲���ʱ: " << time_blur << " s" << endl;
    namedWindow("��ֵ�˲�ͼ��", WINDOW_AUTOSIZE);
    imshow("��ֵ�˲�ͼ��", dstImage_blur);

    /********************��˹�˲�******************/
    Mat dstImage_GaussianBlur;
    double time_GaussianBlur = static_cast<double>(getTickCount());
    GaussianBlur(srcImage, dstImage_GaussianBlur, Size(5, 5), 0, 0);
    time_GaussianBlur = ((double)getTickCount()-time_GaussianBlur)/getTickFrequency();
    cout << "��˹�˲���ʱ: " << time_GaussianBlur << " s" << endl;
    namedWindow("��˹�˲�ͼ��", WINDOW_AUTOSIZE);
    imshow("��˹�˲�ͼ��", dstImage_GaussianBlur);

    /*******************��ֵ�˲�*******************/
    Mat dstImage_medianBlur;
    double time_medianBlur=static_cast<double>(getTickCount());
    medianBlur(srcImage, dstImage_medianBlur, 5);
    time_medianBlur = ((double)getTickCount()-time_medianBlur)/getTickFrequency();
    cout << "��ֵ�˲���ʱ: " << time_medianBlur << " s" << endl;
    namedWindow("��ֵ�˲�ͼ��", WINDOW_AUTOSIZE);
    imshow("��ֵ�˲�ͼ��", dstImage_medianBlur);

    /******************˫���˲�******************/
    Mat dstImage_bilateralFilter;
    double time_bilateralFilter = static_cast<double>(getTickCount());
    bilateralFilter(srcImage, dstImage_bilateralFilter, 30, 60, 15);
    time_bilateralFilter=((double)getTickCount()-time_bilateralFilter)/getTickFrequency();
    cout << "˫���˲���ʱ: " << time_bilateralFilter << " s" << endl;
    namedWindow("˫���˲�ͼ��", WINDOW_AUTOSIZE);
    imshow("˫���˲�ͼ��", dstImage_bilateralFilter);

    waitKey(0);

    return 0;
}
