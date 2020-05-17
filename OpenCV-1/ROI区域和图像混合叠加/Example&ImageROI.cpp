#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int atgc,char **argv)
{
    Mat srcImage = imread(argv[1]);
    Mat addImage = imread(argv[2]);

    //�ж��ļ��Ƿ���سɹ�
    if(srcImage.data && addImage.data)
        cout << "ͼ����سɹ�!" << endl << endl;
    else
    {
        cout << "ͼ�����ʧ��!" << endl << endl;
        return -1;
    }
    imshow("srcImage",srcImage);
    imshow("astronaut",addImage);

    //����srcImage����Ȥ����
    //��һ�ַ�ʽ��ʹ��Rect()��������ROI
    Mat imageROI = srcImage(Rect(250,50,addImage.cols,addImage.rows));
    addWeighted(imageROI,0.7,addImage,0.3,0,imageROI);
    imshow("��Ϻ�ͼ��",srcImage);

    waitKey(0);

    return 0;
}
