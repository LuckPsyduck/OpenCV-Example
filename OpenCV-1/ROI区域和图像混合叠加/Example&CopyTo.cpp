#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    Mat srcImage = imread(argv[1]);
    Mat addImage = imread(argv[2]);
    Mat maskImage = imread(argv[2],IMREAD_GRAYSCALE);  //加载其灰度图

    //判断文件是否加载成功
    if(srcImage.data && addImage.data)
        cout << "图像加载成功!" << endl << endl;
    else
    {
        cout << "图像加载失败!" << endl << endl;
        return -1;
    }

    //以第二种方式Range()函数设置其ROI区域
    Mat imageROI = srcImage(Range(50,50+maskImage.rows), Range(250,250+maskImage.cols));//begin end
  //! copies those matrix elements to "m" that are marked with non-zero mask elements.
    //void copyTo( OutputArray m, InputArray mask ) const;
    addImage.copyTo(imageROI,maskImage);
    imshow("混合后图像",srcImage);

    waitKey(0);

    return 0;
}