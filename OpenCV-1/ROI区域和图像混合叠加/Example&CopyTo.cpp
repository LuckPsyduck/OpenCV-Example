#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    Mat srcImage = imread(argv[1]);
    Mat addImage = imread(argv[2]);
    Mat maskImage = imread(argv[2],IMREAD_GRAYSCALE);  //������Ҷ�ͼ

    //�ж��ļ��Ƿ���سɹ�
    if(srcImage.data && addImage.data)
        cout << "ͼ����سɹ�!" << endl << endl;
    else
    {
        cout << "ͼ�����ʧ��!" << endl << endl;
        return -1;
    }

    //�Եڶ��ַ�ʽRange()����������ROI����
    Mat imageROI = srcImage(Range(50,50+maskImage.rows), Range(250,250+maskImage.cols));//begin end
  //! copies those matrix elements to "m" that are marked with non-zero mask elements.
    //void copyTo( OutputArray m, InputArray mask ) const;
    addImage.copyTo(imageROI,maskImage);
    imshow("��Ϻ�ͼ��",srcImage);

    waitKey(0);

    return 0;
}