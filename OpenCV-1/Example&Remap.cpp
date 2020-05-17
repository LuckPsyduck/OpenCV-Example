#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat srcImage, dstImage;
Mat map1_x, map2_y;
String windowName = "ͼ����ӳ��";
int ind;        //��ӳ������ѡ��

void updateMap(void);

int main(int argc,char **argv)
{
	////��ʼ������
	//ind = 0;
	srcImage = imread(argv[1]);
	dstImage.create(srcImage.size(), srcImage.type());
	map1_x.create(srcImage.size(), CV_32FC1);
	map2_y.create(srcImage.size(), CV_32FC1);

	//��������
	namedWindow(windowName, WINDOW_AUTOSIZE);

	while(true)
	{
		int c = waitKey(1000);      //�ӳ�1000ms

		if((char)c == 27)
		{
			break;      //ESC�˳�
		}

		updateMap();        //���ú�����������ӳ��ģʽ
		remap(srcImage, dstImage, map1_x, map2_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

		imshow(windowName, dstImage);
	}

	return 0;
}

void updateMap(void)
{
	ind = ind % 4;

	for(int j = 0; j < srcImage.rows; j++)
	{
		for(int i = 0; i < srcImage.cols; i++)
		{
			switch(ind)
			{
				//ͼ�񳤿���С��ԭ����һ�벢������ʾ
			case 0:
				if(i > srcImage.cols*0.25 && i < srcImage.cols*0.75 && j > srcImage.rows*0.25 && j < srcImage.rows*0.75)
				{
					map1_x.at<float>(j, i) = 2*(i - srcImage.cols*0.25) + 0.5;
					map2_y.at<float>(j, i) = 2*(j - srcImage.rows*0.25) + 0.5;
				}
				else
				{
					map1_x.at<float>(j, i) = 0;
					map2_y.at<float>(j, i) = 0;
				}
				break;

				//ͼ�����ҷ�ת
			case 1:
				map1_x.at<float>(j, i) = i;
				map2_y.at<float>(j, i) = srcImage.rows - j;
				break;

				//ͼ�����·�ת
			case 2:
				map1_x.at<float>(j, i) = srcImage.cols - i;
				map2_y.at<float>(j, i) = j;
				break;

				//ͼ���������Ҿ���ת
			case 3:
				map1_x.at<float>(j, i) = srcImage.cols - i;
				map2_y.at<float>(j, i) = srcImage.rows - j;
				break;

			default:
				break;
			}
		}
	}

	ind++;
}
