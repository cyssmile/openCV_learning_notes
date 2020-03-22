#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void myDrawContours(Mat &src);
int main(int argc, char** crgv)
{
	Mat src = imread("D:/images/leaf.jpg", -1);
	if (src.empty())
	{
		cout << "can`t open this ph" << endl;
	}
	GaussianBlur(src, src, Size(3, 3), 0);
	namedWindow("input",WINDOW_FREERATIO);
	imshow("input", src);
	Mat dst;
	myDrawContours(src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}


void myDrawContours(Mat &src) 
{
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Mat twoValued;
	threshold(gray, twoValued,0,255,THRESH_BINARY|THRESH_OTSU);
	namedWindow("Two_valued",WINDOW_FREERATIO);
	imshow("Two_valued", twoValued);

	bitwise_not(twoValued,twoValued);

	//ÂÖÀª·¢ÏÖ
	vector<vector<Point>> contours;
	vector<Vec4i> hirearchy;
	//findContours(twoValued,contours,hirearchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point());
	//findContours(twoValued, contours, hirearchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	findContours(twoValued, contours, hirearchy, RETR_LIST, CHAIN_APPROX_SIMPLE, Point());
	//findContours(twoValued, contours, hirearchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
	drawContours(src,contours,-1,Scalar(0,0,255),2,8);
	namedWindow("drawContours", WINDOW_FREERATIO);
	imshow("drawContours", src);
}