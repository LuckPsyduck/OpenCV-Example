#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    Mat srcImage;
    srcImage = imread(argv[1]);        //加载图像文件

    //判断图像是否加载成功
    if(srcImage.empty())
    {
        cout << "图像加载失败!" << endl;
        return -1;
    }
    else
        cout << "图像加载成功!" << endl << endl;

    namedWindow("原图像", WINDOW_AUTOSIZE);
    imshow("原图像", srcImage);

    Mat midImage, dstImage;
    Canny(srcImage, midImage, 50, 200, 3);        //首先对图像进行边缘检测
    cvtColor(midImage, dstImage, CV_GRAY2BGR);

    //进行霍夫变换
    vector<Vec2f> lines;            //定义一个矢量结构用于存放得到的线段矢量集合

	/*
	CV_EXPORTS_W void HoughLines( InputArray image, OutputArray lines,
                              double rho, double theta, int threshold,
                              double srn=0, double stn=0 );
	*/
    HoughLines(midImage, lines, 1, CV_PI/180,50, 0, 0);

    //在图中绘出线段
    for(size_t i = 0; i < lines.size(); i++)//记录各条直线的参数
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

    namedWindow("霍夫线变换", WINDOW_AUTOSIZE);
    imshow("霍夫线变换", dstImage);

    waitKey(0);

    return 0;
}

