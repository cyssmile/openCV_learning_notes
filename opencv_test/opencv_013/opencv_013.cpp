#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv) 
{
	Mat src = imread("D:/images/Mon.jpg",-1);
	namedWindow("src_demo",WINDOW_FREERATIO);
	imshow("src_demo",src);
	//颜色映射表  applyColorMap
	Mat dst;
	applyColorMap(src,dst,COLORMAP_AUTUMN);
	namedWindow("autumn", WINDOW_FREERATIO);
	imshow("autumn",dst);

	//LUT look up table

	Mat lut = Mat::zeros(256,1,CV_8UC3);
	// 利用src来构建 lut 查找表
	for (int i = 0; i < 256;i++) 
	{
		lut.at<Vec3b>(i, 0) = src.at<Vec3b>(10, i);
	}
	imshow("lut_demo", lut);

	Mat dst1;
	LUT(src, lut, dst1);
	namedWindow("lut_demo", WINDOW_FREERATIO);
	imshow("lut_demo", dst1);
	waitKey(0);
	destroyAllWindows();
	return 0;
}