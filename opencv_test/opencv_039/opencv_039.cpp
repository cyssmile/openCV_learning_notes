#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/gate.jpg", IMREAD_UNCHANGED);
	if (src.empty()) {
		cout << "can`t read this image" << endl;
	}
	imshow("src", src);
	Mat erode_result,dilate_result;
	Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3),Point(-1,-1));
	erode(src, erode_result, kernel);
	dilate(src, dilate_result, kernel);
	/*
	*basic gradient
	*/
	Mat basic_gradient;
	subtract(dilate_result, erode_result, basic_gradient);
	imshow("basic_gradient_win", basic_gradient);

	/*
	* inner gradient
	*/
	Mat inner_gradient;
	subtract(src, erode_result, inner_gradient);
	imshow("inner_gradient_win", inner_gradient);

	/*
	* outside gradient
	*/
	Mat outside_gradient;
	subtract(dilate_result, src, outside_gradient);
	imshow("outside_gradient_win", outside_gradient);
	waitKey(0);
	destroyAllWindows();
	return 0;
}