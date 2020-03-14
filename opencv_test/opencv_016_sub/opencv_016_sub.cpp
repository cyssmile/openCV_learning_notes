#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;
int main(int argc, char ** argv)
{
	Mat src_0 = imread("D:/images/beauty.jpg", -1);
	if (src_0.empty())
	{
		cout << "can`t open this ph" << endl;
	}
	imshow("src_win", src_0);
	/*
	*/
	Mat laplacian_dst;
	Laplacian(src_0, laplacian_dst, -1, 3, 1.0, 0, BORDER_DEFAULT);
	imshow("laplacian_dst_win", laplacian_dst);
	/*
	*拉普拉斯锐化算子定义
	*/

	Mat Rok = (Mat_<int>(3, 3) <<   0, -1, 0 , 
									-1, 5, -1,
									0, -1, 0);
	Mat dst;
	filter2D(src_0, dst, CV_32F, Rok, Point(-1, -1), 0, BORDER_DEFAULT);
	convertScaleAbs(dst, dst);
	imshow("dst_win", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}