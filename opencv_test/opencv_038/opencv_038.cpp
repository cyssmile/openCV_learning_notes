#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/openStruct.jpg", IMREAD_UNCHANGED);
	if (src.empty()) {
		cout << "can`t read this image" << endl;
	}
	imshow("src",src);
	Mat gray,binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Canny(gray, binary, 60, 100, 3);
	imshow("binary", binary);
	Mat dst;
	//Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 1), Point(-1, -1));
	Mat kernel = getStructuringElement(MORPH_RECT, Size(1, 15), Point(-1, -1));
	morphologyEx(binary, dst, MORPH_OPEN, kernel, Point(-1, -1), 1);
	bitwise_not(dst, dst);
	namedWindow("dst_demo", WINDOW_FREERATIO);
	imshow("dst_demo", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}