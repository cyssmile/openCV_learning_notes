#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
void Complementary_transformation(Mat& src) 
{
	Mat dst;
	src.copyTo(dst);

	int row = src.rows;
	int col = src.cols;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			int b = src.at<Vec3b>(i, j)[0];
			int g = src.at<Vec3b>(i, j)[1];
			int r = src.at<Vec3b>(i, j)[2];
			int maxrgb = max(max(r, g), b);
			int minrgb = min(min(r, g), b);
			dst.at<Vec3b>(i, j)[0] = maxrgb + minrgb - b;
			dst.at<Vec3b>(i, j)[1] = maxrgb + minrgb - g;
			dst.at<Vec3b>(i, j)[2] = maxrgb + minrgb - r;
		}
	}
	namedWindow("output", WINDOW_FREERATIO);
	imshow("output", dst);
}
int main(int argc, char** argv) 
{
	Mat src = imread("D:/images/dog.jpg", -1);
	if (src.empty()) {
		exit(0);
	}
	namedWindow("input", WINDOW_FREERATIO);
	imshow("input",src);
	Complementary_transformation(src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}