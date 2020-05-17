#include <iostream>//对比度变大，扩散范围更均衡
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    Mat srcImage, dstImage;
    srcImage = imread(argv[1]);

    //判断图像是否加载成功
    if(!srcImage.data)
    {
        cout << "图像加载失败!" << endl;
        return -1;
    }
    else
        cout << "图像加载成功!" << endl << endl;

    cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);       //将原图像转换为灰度图

    equalizeHist(srcImage, dstImage);           //直方图均衡化

    //创建窗口
    String windowNameSrc = "原图像";
    String windowNameHist = "直方图均衡化后图像";
    namedWindow(windowNameSrc, WINDOW_AUTOSIZE);
    namedWindow(windowNameHist, WINDOW_AUTOSIZE);

    //显示图像
    imshow(windowNameSrc, srcImage);
    imshow(windowNameHist, dstImage);

    waitKey(0);

    return 0;
}
