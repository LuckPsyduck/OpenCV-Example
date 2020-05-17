/*
 *�������ȶԼ��ص�ͼ��ִ�����²��������γɸ�˹������
 *֮�����������²����õ���ͼ��������ϲ����γ�������˹������
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

    //�ж�ͼ���Ƿ���سɹ�
    if(srcImage.empty())
    {
        cout << "ͼ�����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼ����سɹ�!" << endl << endl;

    namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
    imshow("ԭͼ��", srcImage);

    //�������²��������ֱ����
    Mat pyrDownImage_1, pyrDownImage_2;

    pyrDown(srcImage, pyrDownImage_1);
    namedWindow("���²���-1", WINDOW_AUTOSIZE);
    imshow("���²���-1", pyrDownImage_1);

    pyrDown(pyrDownImage_1, pyrDownImage_2);
    namedWindow("���²���-2", WINDOW_AUTOSIZE);
    imshow("���²���-2", pyrDownImage_2);

    //�������²����Ľ���������ϲ�������
    Mat pyrUpImage_1, pyrUpImage_2;

    pyrUp(pyrDownImage_2, pyrUpImage_1);
    namedWindow("���ϲ���-1", WINDOW_AUTOSIZE);
    imshow("���ϲ���-1", pyrUpImage_1);

    pyrUp(pyrUpImage_1, pyrUpImage_2);
    namedWindow("���ϲ���-2", WINDOW_AUTOSIZE);
    imshow("���ϲ���-2", pyrUpImage_2);

    waitKey(0);

    return 0;
}
