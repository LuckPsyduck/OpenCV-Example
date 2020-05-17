#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
	Mat srcImage;
	srcImage = imread(argv[1]);

	//判断图像是否读取成功
	if(srcImage.empty())
	{
		cout << "图像加载失败!" << endl;
		return -1;
	}
	else
		cout << "图像加载成功!" << endl << endl;

	//分割成三通道图像
	vector<Mat> channels;
	split(srcImage, channels);//单独分开，每个通道的颜色一种颜色，统计

	//设定bin数目
	int histBinNum = 255;

	//设定取值范围
	float range[] = {0, 255};
	const float* histRange = {range};

	bool uniform = true;
	bool accumulate = false;

	//声明三个通道的hist数组
	Mat red_hist, green_hist, blue_hist;

	//计算直方图
	/*
	CV_EXPORTS void calcHist( const Mat* images, int nimages,
                          const int* channels, InputArray mask,
                          OutputArray hist, int dims, const int* histSize,
                          const float** ranges, bool uniform=true, bool accumulate=false );
	*/
	calcHist(&channels[0], 1, 0, Mat(), red_hist, 1, &histBinNum, &histRange, uniform, accumulate);
	calcHist(&channels[1], 1, 0, Mat(), green_hist, 1, &histBinNum, &histRange, uniform, accumulate);
	calcHist(&channels[2], 1, 0, Mat(), blue_hist, 1, &histBinNum, &histRange, uniform, accumulate);

	//创建直方图窗口
	int hist_w = 400;
	int hist_h = 400;
	int bin_w = cvRound((double)srcImage.cols/histBinNum);

	Mat histImage(srcImage.cols, srcImage.rows, CV_8UC3, Scalar(0, 0, 0));

	//将直方图归一化到范围[0, histImage.rows]
	normalize(red_hist, red_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(green_hist, green_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(blue_hist, blue_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	//循环绘制直方图
	for(int i = 1; i < histBinNum; i++)
	{
		line(histImage, Point(bin_w*(i-1), srcImage.rows - cvRound(red_hist.at<float>(i-1))),
			Point(bin_w*(i), srcImage.rows - cvRound(red_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
		line(histImage, Point(bin_w*(i-1), srcImage.rows - cvRound(green_hist.at<float>(i-1))),
			Point(bin_w*(i), srcImage.rows - cvRound(green_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i-1), srcImage.rows - cvRound(blue_hist.at<float>(i-1))),
			Point(bin_w*(i), srcImage.rows - cvRound(blue_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}

	namedWindow("原图像", WINDOW_AUTOSIZE);
	imshow("原图像", srcImage);

	namedWindow("图像直方图", WINDOW_AUTOSIZE);
	imshow("图像直方图", histImage);

	waitKey(0);

	return 0;
}
