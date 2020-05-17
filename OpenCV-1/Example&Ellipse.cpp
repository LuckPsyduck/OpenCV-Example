#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

//定义全局变量
Mat srcImage, grayImage;
int thresh = 100;
const int threshMaxValue = 255;
RNG rng(12345);

//声明回调函数
void thresh_callback(int, void*);

int main(int argc,char **argv)
{
    srcImage = imread(argv[1]);

    //判断图像是否加载成功
    if (srcImage.empty())
    {
        cout << "图像加载失败!";
        return -1;
    }
    else
        cout << "图像加载成功!" << endl << endl;

    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    blur(grayImage, grayImage, Size(3, 3));

    namedWindow("原图像", WINDOW_AUTOSIZE);
    imshow("原图像", grayImage);

    //创建轨迹条
    createTrackbar("Thresh:", "原图像", &thresh, threshMaxValue, thresh_callback);
    thresh_callback(thresh, 0);

    waitKey(0);

    return 0;
}

void thresh_callback(int, void*)
{
    Mat threshold_output;
    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy;

    //图像二值化检测边缘
    threshold(grayImage, threshold_output, thresh, 255, THRESH_BINARY);
    //寻找图像轮廓
    findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //为每个轮廓寻找旋转的矩形和椭圆
    vector<RotatedRect>minRect(contours.size());
    vector<RotatedRect>minEllipse(contours.size());

    //如果轮廓上的点大于5个则用椭圆填充
    for (int i = 0; i < contours.size(); i++)
    {
        minRect[i] = minAreaRect(Mat(contours[i]));
        if (contours[i].size()>5)
        {
            minEllipse[i] = fitEllipse(Mat(contours[i]));
        }
    }

    //绘制检测到的图像轮廓、旋转矩形和椭圆
    Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        ellipse(drawing, minEllipse[i], color, 2, 8);
        //旋转矩形
        Point2f rect_points[4];
        minRect[i].points(rect_points);
        for (int j = 0; j < 4; j++)
        {
            line(drawing, rect_points[j], rect_points[(j + 1) % 4], color, 1, 8);
        }
    }

    namedWindow("轮廓图", WINDOW_AUTOSIZE);
    imshow("轮廓图", drawing);
}

