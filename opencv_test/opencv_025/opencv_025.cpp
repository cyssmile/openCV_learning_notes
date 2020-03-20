#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char** crgv)
{
	Mat src = imread("D:/images/dark.jpg", -1);
	if (src.empty())
	{
		cout << "can`t open this ph" << endl;
	}

	imshow("input", src);
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("gray_demo", gray);
	Mat dst;
	//threshold(gray, dst, 127, 255, THRESH_BINARY);
	//double t1 = threshold(gray, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);
	//imshow("OTSU", dst);
	//adaptiveThreshold(gray,dst,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,3,2);
	adaptiveThreshold(gray, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 3);
	imshow("OTSU", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}