#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
	Mat src = imread("D:/images/coin.jpg", IMREAD_UNCHANGED);
	if (src.empty()) {
		cout << "can`t read this image" << endl;
	}
	GaussianBlur(src,src,Size(3,3),0);
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	namedWindow("coin_demo", WINDOW_NORMAL);
	imshow("coin_demo", gray);
	vector<Vec3f> circles;
	HoughCircles(gray,circles,HOUGH_GRADIENT,2,35,100,100,5,100);
	for (size_t t =0;t<circles.size();t++) 
	{
		circle(src,Point(circles[t][0],circles[t][1]),circles[t][2],Scalar(0,0,0),2,8);
		circle(src, Point(circles[t][0], circles[t][1]), 1, Scalar(255, 0, 255), 2, 8);
	}
	namedWindow("source",WINDOW_FREERATIO);
	imshow("source",src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
