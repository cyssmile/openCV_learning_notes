#include<opencv2/opencv.hpp>
#include<iostream>
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
	* USM Èñ»¯  
	* sharpen_image = blur - laplacian
	*/
	Mat laplacian_dst;
	Laplacian(src_0, laplacian_dst, -1, 3, 1.0, 0, BORDER_DEFAULT);
	imshow("laplacian_dst_win", laplacian_dst);

	Mat blur_dst;
	GaussianBlur(src_0,blur_dst,Size(3,3),0,0,BORDER_DEFAULT);
	imshow("blur_dst", blur_dst);

	Mat usm_dst;
	addWeighted(blur_dst,1.0,laplacian_dst,-0.1,0,usm_dst);
	imshow("usm_dst_win", usm_dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}