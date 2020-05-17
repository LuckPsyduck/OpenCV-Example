#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat srcImage, grayImage;
int thresh = 100;
const int threshMaxValue = 255;
RNG rng(12345);

//�����ص�����
void thresh_callback(int, void*);

int main(int argc,char **argv)
{
    srcImage = imread(argv[1]);

    //�ж�ͼ���Ƿ���سɹ�
    if (srcImage.empty())
    {
        cout << "ͼ�����ʧ��!";
        return -1;
    }
    else
        cout << "ͼ����سɹ�!" << endl << endl;

    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    blur(grayImage, grayImage, Size(3, 3));

    namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
    imshow("ԭͼ��", grayImage);

    //�����켣��
    createTrackbar("Thresh:", "ԭͼ��", &thresh, threshMaxValue, thresh_callback);
    thresh_callback(thresh, 0);

    waitKey(0);

    return 0;
}

void thresh_callback(int, void*)
{
    Mat threshold_output;
    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy;

    //ͼ���ֵ������Ե
    threshold(grayImage, threshold_output, thresh, 255, THRESH_BINARY);
    //Ѱ��ͼ������
    findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //Ϊÿ������Ѱ����ת�ľ��κ���Բ
    vector<RotatedRect>minRect(contours.size());
    vector<RotatedRect>minEllipse(contours.size());

    //��������ϵĵ����5��������Բ���
    for (int i = 0; i < contours.size(); i++)
    {
        minRect[i] = minAreaRect(Mat(contours[i]));
        if (contours[i].size()>5)
        {
            minEllipse[i] = fitEllipse(Mat(contours[i]));
        }
    }

    //���Ƽ�⵽��ͼ����������ת���κ���Բ
    Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        ellipse(drawing, minEllipse[i], color, 2, 8);
        //��ת����
        Point2f rect_points[4];
        minRect[i].points(rect_points);
        for (int j = 0; j < 4; j++)
        {
            line(drawing, rect_points[j], rect_points[(j + 1) % 4], color, 1, 8);
        }
    }

    namedWindow("����ͼ", WINDOW_AUTOSIZE);
    imshow("����ͼ", drawing);
}

