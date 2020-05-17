#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    Mat I = imread(argv[1], IMREAD_GRAYSCALE);       //读入图像灰度图

    //判断图像是否加载成功
    if (I.empty())
    {
        cout << "图像加载失败!" << endl;
        return -1;
    }
    else
        cout << "图像加载成功!" << endl << endl;

    Mat padded;                 //以0填充输入图像矩阵
    int m = getOptimalDFTSize(I.rows);
    int n = getOptimalDFTSize(I.cols);

    //填充输入图像I，输入矩阵为padded，上方和左方不做填充处理
	/*CV_EXPORTS_W void copyMakeBorder( InputArray src, OutputArray dst,
                                int top, int bottom, int left, int right,
                                int borderType, const Scalar& value=Scalar() );
	*/
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(),CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);     //将planes融合合并成一个多通道数组complexI

    dft(complexI, complexI);        //进行傅里叶变换

    //计算幅值，转换到对数尺度(logarithmic scale)
    //=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);        //planes[0] = Re(DFT(I),planes[1] = Im(DFT(I))
                                    //即planes[0]为实部,planes[1]为虚部
    magnitude(planes[0], planes[1], planes[0]); //实部的平方加复部的平方，然后开方    //planes[0] = magnitude
    Mat magI = planes[0];//幅度值

    magI += Scalar::all(1);
	/*
	之所以要进行对数转换是因为傅里叶变换后的结果对于在显示器显示来讲范围比较大，
	这样的话对于一些小的变化或者是高的变换值不能进行观察。因此高的变化值将会转变成白点，
	而较小的变化值则会变成黑点。为了能够获得可视化的效果，
	可以利用灰度值将我们的线性尺度(linear scale)转变为对数尺度(logarithmic scale)
	*/
    log(magI, magI);                //转换到对数尺度(logarithmic scale)

    //如果有奇数行或列，则对频谱进行裁剪
    magI = magI(Rect(0, 0, magI.cols&-2, magI.rows&-2));

    //重新排列傅里叶图像中的象限，使得原点位于图像中心
	/*
	四周的角上时高频分量，现在我们通过重新调整象限将高频分量调整到图像正中间
	*/
    int cx = magI.cols / 2;
    int cy = magI.rows / 2;

    Mat q0(magI, Rect(0, 0, cx, cy));       //左上角图像划定ROI区域
    Mat q1(magI, Rect(cx, 0, cx, cy));      //右上角图像
    Mat q2(magI, Rect(0, cy, cx, cy));      //左下角图像
    Mat q3(magI, Rect(cx, cy, cx, cy));     //右下角图像

    //变换左上角和右下角象限
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    //变换右上角和左下角象限
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    //归一化处理，用0-1之间的浮点数将矩阵变换为可视的图像格式
    normalize(magI, magI, 0, 1, CV_MINMAX);

    imshow("输入图像", I);
    imshow("频谱图", magI);
    waitKey(0);


    return 0;
}