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
    if(srcImage.data)
        cout << "ͼ����سɹ�!" << endl << endl;
    else
    {
        cout << "ͼ�����ʧ��!" << endl << endl;
        return -1;
    }
    namedWindow("srcImage", WINDOW_AUTOSIZE);
    imshow("srcImage", srcImage);

    Mat kern = (Mat_<char>(3,3) << 0, -1 ,0,
                                   -1, 5, -1,
                                   0, -1, 0);
    Mat dstImage;
    filter2D(srcImage,dstImage,srcImage.depth(),kern);
    namedWindow("dstImage",WINDOW_AUTOSIZE);
    imshow("dstImage",dstImage);


    waitKey(0);

    return 0;
}
