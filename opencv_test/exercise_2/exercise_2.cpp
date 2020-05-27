#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int th = 0;
Mat src;
void my_thresholdTwoValued(int,void*) {

	int height = src.rows;
	int width = src.cols;
	Mat TwoValued = Mat::zeros(src.size(), CV_8UC1);
	for (size_t row = 0; row < height; row++) {
		for (size_t col = 0; col < width; col++) 
		{
			int pv = src.at<uchar>(row, col);
			if (pv >= th) {
				TwoValued.at<uchar>(row,col) = 255;
			}
			else {
				TwoValued.at<uchar>(row, col) = 0;
			}
		}
	}
	namedWindow("��ֵ�����ͼ��", WINDOW_FREERATIO);
	imshow("��ֵ�����ͼ��", TwoValued);
}

int main(int argc, char* argv)
{
	src = imread("D:/images/dog.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		exit(0);
	}
	namedWindow("input", WINDOW_FREERATIO);
	imshow("input", src);
	createTrackbar("��ֵ", "input", &th, 255, my_thresholdTwoValued);
	my_thresholdTwoValued(127,0);
	waitKey(0);
	destroyAllWindows();
	return 0;
}