#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;
int main(int argc, char ** argv)
{
	/*
	* 使用拉普拉斯算子锐化增强图片
	*/
	Mat src = imread("D:/images/deal.jpg", -1);
	if (src.empty())
	{
		cout << "can`t open this ph" << endl;
	}
	imshow("src_win", src);
	/*
	*Robot算子定义
	*/
	Mat Robot_x = (Mat_<int>(2, 2) << 1,0,0,-1);
	Mat dst_x;
	filter2D(src, dst_x, CV_32F, Robot_x, Point(-1, -1), 0, BORDER_DEFAULT);
	//convertScaleAbs(dst_x, dst_x);
	//imshow("Robot_x_win", dst_x);

	Mat Robot_y = (Mat_<int>(2,2)<<0,1,-1,0);
	Mat dst_y;
	filter2D(src,dst_y,CV_32F,Robot_y,Point(-1,-1),0,BORDER_DEFAULT);
	//convertScaleAbs(dst_y, dst_y);
	//imshow("Robot_y_win", dst_y);
	Mat dst;
	add(dst_x, dst_y, dst);
	convertScaleAbs(dst, dst);
	imshow("dst_win", dst);


	/*
	*
	*Sobel 算子
	*/
	Mat sobel_dst_x;
	Mat sobel_dst_y;
	Sobel(src, sobel_dst_x,CV_32F,1,0,3);
	Sobel(src, sobel_dst_y, CV_32F, 0, 1, 3);
	convertScaleAbs(sobel_dst_x, sobel_dst_x);
	convertScaleAbs(sobel_dst_y, sobel_dst_y);
	Mat sobel_dst;
	add(sobel_dst_x, sobel_dst_y, sobel_dst);

	imshow("sobel_win", sobel_dst);

	/*
	* Scharr算子
	*/

	Mat Scharr_dst_x;
	Mat Scharr_dst_y;
	
	Scharr(src, Scharr_dst_x, CV_32F, 1, 0, 3);
	Scharr(src, Scharr_dst_y, CV_32F, 0, 1, 3);
	convertScaleAbs(Scharr_dst_x, Scharr_dst_x);
	convertScaleAbs(Scharr_dst_y, Scharr_dst_y);
	Mat Scharr_dst;
	addWeighted(Scharr_dst_x,0.5, Scharr_dst_y,0.5,0, Scharr_dst);
	
	imshow("Scharr_win", Scharr_dst);

	waitKey(0);
	destroyAllWindows();
	return 0;
}