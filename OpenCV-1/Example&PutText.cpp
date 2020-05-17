#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
    string text = "Yang Mi";
    //int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;     //手写风格字体
    int fontFace = FONT_HERSHEY_SCRIPT_COMPLEX;
    double fontScale = 2;       //字体缩放比
    int thickness = 3;

  /*  Mat img(600,800,CV_8UC3, Scalar::all(0));*/
	Mat img = imread(argv[1]);
    int baseline = 0;

    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    baseline += thickness;

    //center the text
    Point textOrg((img.cols - textSize.width)/2,(img.rows + textSize.height)/2);

    //draw the box
    rectangle(img,textOrg + Point(0,baseline),textOrg + Point(textSize.width, -textSize.height),Scalar(0,0,255));

	//! draws the line segment (pt1, pt2) in the image
    line(img,textOrg + Point(0,thickness),textOrg + Point(textSize.width,thickness),Scalar(0,0,255));

    putText(img,text,textOrg,fontFace,fontScale,Scalar::all(255),thickness,8);
    imshow("text",img);

    waitKey(0);

    return 0;
}