#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void Sharpen(const Mat& myImage, Mat& Result);

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

    Mat dstImage;
    dstImage.create(srcImage.size(), srcImage.type());
    Sharpen(srcImage, dstImage);
    namedWindow("dstImage",WINDOW_AUTOSIZE);
    imshow("dstImage",dstImage);

    waitKey(0);

    return 0;
}

void Sharpen(const Mat& myImage, Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U);        //�жϺ���CV_Assert
    const int nChannels = myImage.channels();

    for(int j = 1; j < myImage.rows - 1; ++j)
    {
        const uchar* precious = myImage.ptr<uchar>(j - 1);      //��ǰ������һ��ָ��
        const uchar* current = myImage.ptr<uchar>(j);           //��ǰ������ָ��
        const uchar* next = myImage.ptr<uchar>(j + 1);          //��ǰ������һ��ָ��

        uchar* output = Result.ptr<uchar>(j);

        //���ù�ʽ�����������ĸ����ضԵ�ǰ����ֵ���д���
        for(int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
        {
            *output++ = saturate_cast<uchar>(5 * current[i]
            -current[i-nChannels]-current[i+nChannels]-precious[i]-next[i]);
        }
    }

    Result.row(0).setTo(Scalar(0));                 //���õ�һ������Ԫ��ֵΪ0
    Result.row(Result.rows-1).setTo(Scalar(0));     //�������һ������Ԫ��ֵΪ0
    Result.col(0).setTo(Scalar(0));                 //���õ�һ������Ԫ��ֵΪ0
    Result.col(Result.cols-1).setTo(Scalar(0));     //�������һ������Ԫ��ֵΪ0
}