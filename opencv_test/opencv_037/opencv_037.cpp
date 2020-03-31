#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
using namespace std;
using namespace cv;
/*
* 图像闭操作
* 闭操作 = 膨胀 + 腐蚀  目的:填充闭合区域
*/
Mat src;
int value = 3;
void showClose(int,void *);
int main(int argc, char** argv) {
	src = imread("D:/images/closed.jpg", IMREAD_UNCHANGED);
	if (src.empty()) {
		cout << "can`t read this image" << endl;
	}
	imshow("input",src);
	createTrackbar("Close_size_value:","input",&value,60,showClose);
	showClose(3,0);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void showClose(int, void *) 
{
	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(value, value), Point(-1, -1));
	morphologyEx(src, dst, MORPH_CLOSE, kernel, Point(-1, -1), 1);
	namedWindow("dst_demo", WINDOW_FREERATIO);
	imshow("dst_demo", dst);
}