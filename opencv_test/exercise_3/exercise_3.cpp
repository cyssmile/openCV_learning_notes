#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
Mat src;
int c_ = 1;
void Logarithmic_transformation(int, void*)
{
	Mat logSrc;
	src.convertTo(logSrc, CV_32FC1, 1.0);
	logSrc += Scalar::all(1);
	log(logSrc, logSrc);
	logSrc = logSrc * c_;
	normalize(logSrc,logSrc, 0, 255,NORM_MINMAX);
	Mat dst;
	logSrc.convertTo(dst, CV_8UC1, 1.0);
	convertScaleAbs(dst,dst);
	namedWindow("对数变换结果", WINDOW_FREERATIO);
	imshow("对数变换结果", dst);

}

int main(int argc, char* argv)
{
	src = imread("D:/images/nightwalk.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		exit(0);
	}
	namedWindow("input", WINDOW_FREERATIO);
	imshow("input", src);
	
	createTrackbar("c值", "input", &c_, 5, Logarithmic_transformation);
	Logarithmic_transformation(1,0);
	waitKey(0);
	destroyAllWindows();
	return 0;
}