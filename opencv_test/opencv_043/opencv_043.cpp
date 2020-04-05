#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
	Mat source = imread("D:/images/IDphoto1.jpg",-1);
	if (source.empty()) {
		cout << "can`t open this ph" << endl;
	}
	namedWindow("source_demo",WINDOW_FREERATIO);
	imshow("source_demo",source);

	Mat gray;
	cvtColor(source, gray, COLOR_BGR2GRAY);
	threshold(gray,gray,0,255,THRESH_BINARY|THRESH_OTSU);
	vector<vector<Point>> contours;
	findContours(gray,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point());
	Mat canvas = Mat::zeros(source.size(),CV_8UC3);
	canvas = Scalar::all(255);
	/*
	for (size_t t = 0; t < contours.size(); t++) 
	{
		drawContours(canvas,contours,t,Scalar(0),2,8);
	}
	*/
	drawContours(canvas, contours, 8, Scalar(0,0,0), -1, 8);

	namedWindow("draw",WINDOW_FREERATIO);
	bitwise_not(canvas, canvas);
	imshow("draw", canvas);
	bitwise_not(canvas, canvas);
	vector<Mat> split_canvas;
	split(canvas,split_canvas);
	Mat cdst;
	bitwise_and(source, source, cdst, split_canvas[0]);
	namedWindow("cdst", WINDOW_FREERATIO);
	imshow("cdst",cdst);


	Mat hsv, gaus;
	GaussianBlur(source, gaus, Size(3, 3), 0);
	cvtColor(gaus, hsv, COLOR_BGR2HSV);
	namedWindow("hsv_demo", WINDOW_FREERATIO);
	imshow("hsv_demo", hsv);
	Mat mask;
	inRange(hsv,Scalar(100,43,46),Scalar(124,255,255),mask);
	namedWindow("mask", WINDOW_FREERATIO);
	bitwise_not(mask,mask);
	imshow("mask", mask);
	Mat dst;
	bitwise_and(source,source,dst,mask);
	namedWindow("dst", WINDOW_FREERATIO);
	imshow("dst", dst);

	
	waitKey(0);
	destroyAllWindows();
	return 0;
}