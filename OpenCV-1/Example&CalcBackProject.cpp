#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat srcImage, hsvImage,hueImage;
const int hueBinMaxValue = 180;
int hueBinValue=25;

//�����ص�����
void Hist_and_Backprojection(int, void*);

int main(int argc,char **argv)
{
	srcImage=imread(argv[1]);

	//�ж�ͼ���Ƿ���سɹ�
	if(srcImage.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}
	else
		cout << "ͼ����سɹ�..." << endl << endl;

	//��ͼ��ת��ΪHSVͼ��
	cvtColor(srcImage, hsvImage, CV_BGR2HSV);

	//ֻʹ��ͼ���H����
	hueImage.create(hsvImage.size(), hsvImage.depth());
	int ch[]={0,0};
	/*
	CV_EXPORTS void mixChannels(const Mat* src, size_t nsrcs, Mat* dst, size_t ndsts,
                            const int* fromTo, size_t npairs);
	*/
	mixChannels(&hsvImage, 1, &hueImage, 1, ch, 1);

	//�켣����������
	char trackBarName[20];
	sprintf(trackBarName,"Hue bin:%d",hueBinMaxValue);
	namedWindow("SourceImage",WINDOW_AUTOSIZE);

	//�����켣�������ûص�����
	createTrackbar(trackBarName, "SourceImage", &hueBinValue, hueBinMaxValue, Hist_and_Backprojection);
	Hist_and_Backprojection(hueBinValue, 0);

	imshow("SourceImage", srcImage);

	waitKey(0);

	return 0;
}

void Hist_and_Backprojection(int, void*)
{
	MatND hist;
	int histsize=MAX(hueBinValue, 2);
	float hue_range[]={0,180};
	const float* ranges={hue_range};

	//����ͼ��ֱ��ͼ����һ������
	calcHist(&hueImage, 1, 0, Mat(), hist, 1, &histsize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	//��ȡ����ͶӰ
	MatND backProjection;
	calcBackProject(&hueImage, 1, 0, hist, backProjection, &ranges, 1, true);

	//�������ͶӰ
	imshow("BackProjection", backProjection);

	//����ͼ��ֱ��ͼ
	int w=400;
	int h=400;
	int bin_w = cvRound((double)w/histsize);
	Mat histImage = Mat::zeros(w, h, CV_8UC3);
	for(int i=0; i < hueBinValue; i++)
	{
		rectangle(histImage, Point(i*bin_w, h), Point((i+1)*bin_w, h-cvRound(hist.at<float>(i)*h/255.0)), Scalar(0,0,255), -1);
	}
	imshow("HistImage", histImage);
}
