#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    Mat srcImage;
    srcImage = imread(argv[1]);        //����ͼ���ļ�

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

    Mat midImage, dstImage;
    Canny(srcImage, midImage, 50, 200, 3);        //���ȶ�ͼ����б�Ե���
    cvtColor(midImage, dstImage, CV_GRAY2BGR);

    //���л���任
    vector<Vec2f> lines;            //����һ��ʸ���ṹ���ڴ�ŵõ����߶�ʸ������

	/*
	CV_EXPORTS_W void HoughLines( InputArray image, OutputArray lines,
                              double rho, double theta, int threshold,
                              double srn=0, double stn=0 );
	*/
    HoughLines(midImage, lines, 1, CV_PI/180,50, 0, 0);

    //��ͼ�л���߶�
    for(size_t i = 0; i < lines.size(); i++)//��¼����ֱ�ߵĲ���
    {
        float rho = lines[i][0];
        float theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line(dstImage, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
    }

    namedWindow("�����߱任", WINDOW_AUTOSIZE);
    imshow("�����߱任", dstImage);

    waitKey(0);

    return 0;
}

