#include <iostream>//�Աȶȱ����ɢ��Χ������
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    Mat srcImage, dstImage;
    srcImage = imread(argv[1]);

    //�ж�ͼ���Ƿ���سɹ�
    if(!srcImage.data)
    {
        cout << "ͼ�����ʧ��!" << endl;
        return -1;
    }
    else
        cout << "ͼ����سɹ�!" << endl << endl;

    cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);       //��ԭͼ��ת��Ϊ�Ҷ�ͼ

    equalizeHist(srcImage, dstImage);           //ֱ��ͼ���⻯

    //��������
    String windowNameSrc = "ԭͼ��";
    String windowNameHist = "ֱ��ͼ���⻯��ͼ��";
    namedWindow(windowNameSrc, WINDOW_AUTOSIZE);
    namedWindow(windowNameHist, WINDOW_AUTOSIZE);

    //��ʾͼ��
    imshow(windowNameSrc, srcImage);
    imshow(windowNameHist, dstImage);

    waitKey(0);

    return 0;
}
