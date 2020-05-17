#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    Mat srcImage1 = imread(argv[1]);
    Mat srcImage2 = imread(argv[2]);
    Mat dstImage;

    //检查文件是否加载成功
    if(srcImage1.empty() || srcImage2.empty())
    {
        cout << "图像加载失败!" << endl << endl;
        return -1;
    }
    else
        cout << "图像加载成功!" << endl << endl;

    double alpha = 0.5;
    double beta;
    double input;

    cout << "Please Input alpha[0-1]: ";
    cin >> input;

    //判断输入的alpha是否符合要求
    if(input >= 0.0 && input <= 1.0)
    {
        alpha = input;
    }

    namedWindow("线性混合", WINDOW_NORMAL);
    beta = (1.0 - alpha);
	//! computes weighted sum of two arrays (dst = alpha*src1 + beta*src2 + gamma)
//CV_EXPORTS_W void addWeighted(InputArray src1, double alpha, InputArray src2,
//                              double beta, double gamma, OutputArray dst, int dtype=-1);
    addWeighted(srcImage1, alpha, srcImage2, beta, 0.0, dstImage);

    imshow("线性混合", dstImage);
    namedWindow("srcImage1",WINDOW_NORMAL);
    imshow("srcImage1",srcImage1);
    namedWindow("srcImage2",WINDOW_NORMAL);
    imshow("srcImage2",srcImage2);

    waitKey(0);
    return 0;
}