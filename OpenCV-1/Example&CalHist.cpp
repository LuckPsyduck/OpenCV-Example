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

	//�ж�ͼ���Ƿ��ȡ�ɹ�
	if(srcImage.empty())
	{
		cout << "ͼ�����ʧ��!" << endl;
		return -1;
	}
	else
		cout << "ͼ����سɹ�!" << endl << endl;

	//�ָ����ͨ��ͼ��
	vector<Mat> channels;
	split(srcImage, channels);//�����ֿ���ÿ��ͨ������ɫһ����ɫ��ͳ��

	//�趨bin��Ŀ
	int histBinNum = 255;

	//�趨ȡֵ��Χ
	float range[] = {0, 255};
	const float* histRange = {range};

	bool uniform = true;
	bool accumulate = false;

	//��������ͨ����hist����
	Mat red_hist, green_hist, blue_hist;

	//����ֱ��ͼ
	/*
	CV_EXPORTS void calcHist( const Mat* images, int nimages,
                          const int* channels, InputArray mask,
                          OutputArray hist, int dims, const int* histSize,
                          const float** ranges, bool uniform=true, bool accumulate=false );
	*/
	calcHist(&channels[0], 1, 0, Mat(), red_hist, 1, &histBinNum, &histRange, uniform, accumulate);
	calcHist(&channels[1], 1, 0, Mat(), green_hist, 1, &histBinNum, &histRange, uniform, accumulate);
	calcHist(&channels[2], 1, 0, Mat(), blue_hist, 1, &histBinNum, &histRange, uniform, accumulate);

	//����ֱ��ͼ����
	int hist_w = 400;
	int hist_h = 400;
	int bin_w = cvRound((double)srcImage.cols/histBinNum);

	Mat histImage(srcImage.cols, srcImage.rows, CV_8UC3, Scalar(0, 0, 0));

	//��ֱ��ͼ��һ������Χ[0, histImage.rows]
	normalize(red_hist, red_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(green_hist, green_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(blue_hist, blue_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	//ѭ������ֱ��ͼ
	for(int i = 1; i < histBinNum; i++)
	{
		line(histImage, Point(bin_w*(i-1), srcImage.rows - cvRound(red_hist.at<float>(i-1))),
			Point(bin_w*(i), srcImage.rows - cvRound(red_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
		line(histImage, Point(bin_w*(i-1), srcImage.rows - cvRound(green_hist.at<float>(i-1))),
			Point(bin_w*(i), srcImage.rows - cvRound(green_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i-1), srcImage.rows - cvRound(blue_hist.at<float>(i-1))),
			Point(bin_w*(i), srcImage.rows - cvRound(blue_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}

	namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
	imshow("ԭͼ��", srcImage);

	namedWindow("ͼ��ֱ��ͼ", WINDOW_AUTOSIZE);
	imshow("ͼ��ֱ��ͼ", histImage);

	waitKey(0);

	return 0;
}
