#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/fgp1.jpg", IMREAD_UNCHANGED);
	if (src.empty()) {
		cout << "can`t read this image" << endl;
	}
	namedWindow("src",WINDOW_FREERATIO);
	imshow("src", src);

	Mat kernel = getStructuringElement(MORPH_ELLIPSE,Size(2,2));
	Mat open_dst;
	morphologyEx(src, open_dst, MORPH_OPEN, kernel,Point(-1,-1),3);
	namedWindow("open_dst", WINDOW_FREERATIO);
	imshow("open_dst", open_dst);


	Mat kernel1 = getStructuringElement(MORPH_RECT, Size(2, 2));
	Mat open_close_dst;
	morphologyEx(open_dst,open_close_dst, MORPH_CLOSE, kernel1, Point(-1, -1), 2);
	namedWindow("open_close_dst", WINDOW_FREERATIO);
	imshow("open_close_dst", open_close_dst);

	waitKey(0);
	destroyAllWindows();
	return 0;
}