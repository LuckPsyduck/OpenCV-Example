//-----------------------------------【头文件包含部分】---------------------------------------
//     描述：包含程序所依赖的头文件
//----------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"

using namespace cv;
 
int main( )
{
       //载入原图
       Mat image=imread("a.jpg");
 
       //创建窗口
       namedWindow("均值滤波【原图】" );
       namedWindow("均值滤波【效果图】");
 
       //显示原图
       imshow("均值滤波【原图】", image );
 
       //进行滤波操作
       Mat out;
	   //CV_EXPORTS void boxFilter(const GpuMat& src, GpuMat& dst, int ddepth, \
	   Size ksize, Point anchor = Point(-1,-1), Stream& stream = Stream::Null());
       boxFilter(image, out, -1,Size(5, 5));//the output image depth (-1 to use src.depth()). 
 
       //显示效果图
       imshow("均值滤波【效果图】" ,out );
 
       waitKey(0 );    
}