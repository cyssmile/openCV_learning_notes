#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv;
using namespace std;
int main(int argc, char ** argv) 
{
	Mat src = imread("D:/images/beauty.jpg", -1);
	if (src.empty()) 
	{
		printf("can`t open this ph\n");
	}
	namedWindow("src_demo", WINDOW_FREERATIO);
	imshow("src_demo", src);
	// 通道的分离
	vector<Mat> src_mat;
	split(src, src_mat);

	//展示三个通道
	namedWindow("blue_channels", WINDOW_FREERATIO);
	imshow("blue_channels", src_mat[0]);
	imwrite("D:/images/blue_channels.jpg", src_mat[0]);

	namedWindow("green_channels", WINDOW_FREERATIO);
	imshow("green_channels", src_mat[1]);
	imwrite("D:/images/green_channels.jpg", src_mat[1]);

	namedWindow("red_channels", WINDOW_FREERATIO);
	imshow("red_channels", src_mat[2]);
	imwrite("D:/images/red_channels.jpg", src_mat[2]);

	//改变某个通道，使其通道颜色缺失
	//src_mat[0] = Scalar(255);  //b通道255
	//src_mat[1] = Scalar(255); //g通道255
	//src_mat[2] = Scalar(255); //r通道255
	//src_mat[0] = Scalar(0);  //b通道0
	src_mat[1] = Scalar(0); //g通道0
	//src_mat[2] = Scalar(0); //r通道0
	merge(src_mat, src);
	namedWindow("merge_dst",WINDOW_FREERATIO);
	imshow("merge_dst", src);
	imwrite("D:/images/merge_src_green_0.jpg", src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}