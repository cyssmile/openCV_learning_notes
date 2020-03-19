#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc,char** crgv) 
{
	Mat src = imread("D:/images/zzl.jpeg",-1);
	if (src.empty()) 
	{
		cout << "can`t open this ph" << endl;
	}

	imshow("input", src);
	Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY);
	imshow("gray_demo",gray);
	Mat dst;
	threshold(gray,dst,127,255,THRESH_BINARY);
	imshow("THRESH_BINARY_demo", dst);
	threshold(gray, dst, 127, 255,THRESH_BINARY_INV);
	imshow("THRESH_BINARY_INV_deno", dst);
	threshold(gray, dst, 127, 255, THRESH_MASK);
	imshow("THRESH_MASK_demo", dst);
	threshold(gray, dst, 127, 255,THRESH_OTSU);
	imshow("THRESH_OTSU_demo", dst);
	threshold(gray, dst, 127, 255, THRESH_TRUNC);
	imshow("THRESH_TRUNC_demo", dst);
	threshold(gray, dst, 127, 255, THRESH_TOZERO);
	imshow("THRESH_TOZERO_demo", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}