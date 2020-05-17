#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void addImage(Mat& image, Mat& logoImage, vector<Mat>channels, Mat imageChannel, String title);

int main(int argc,char **argv)
{
    Mat srcImage = imread(argv[1]);
    Mat logoImage = imread(argv[2], IMREAD_GRAYSCALE);

    //�ж��ļ��Ƿ���سɹ�
    if (srcImage.empty() || logoImage.empty())
    {
        cout << "ͼ�����ʧ��!" << endl;
        return false;
    }
    else
        cout << "ͼ����سɹ�!" << endl;

    //�Լ��ص�ԭͼ�����ͨ������
    vector<Mat>channels;
    split(srcImage, channels);//����ɫͨ���������
    Mat imageBlueChannel;
    imageBlueChannel = channels.at(0);  //��ȡ��ɫͨ��

    //�������ƣ�Ҳ������char���飬����char*��ָ����������
    String imageBlueTitle = "��ɫͨ������logo�ں�";     

    addImage(srcImage, logoImage, channels, imageBlueChannel, imageBlueTitle);

    return 0;
}

void addImage(Mat& image, Mat& logoImage, vector<Mat>channels, Mat imageChannel, String title)
{
    //����ȡ����ɫͨ���ϣ�ָ��ROI�������logoImage
    addWeighted(imageChannel(Rect(50, 50, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.7,
        0.0, imageChannel(Rect(50, 50, logoImage.cols, logoImage.rows)));

    merge(channels, image); //������logo�����ɫͨ��������������ɫͨ�������ں�
    imshow(title, image);
    waitKey(0);
}

