#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc,char** argv) 
{
	Mat src = imread("D:/images/moon.jpg",-1);
	if (src.empty()) 
	{
		cout << "can`t open thid ph" << endl;
	}
	imshow("src_win",src);
	Mat mKernel = Mat::ones(11, 11, CV_32F) / (float)(11 * 11);
	Mat dst;
	filter2D(src,dst,-1,mKernel,Point(-1,-1),0,BORDER_DEFAULT);
	imshow("dst_win",dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}