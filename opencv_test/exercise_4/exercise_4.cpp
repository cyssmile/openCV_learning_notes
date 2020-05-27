#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
Mat src;
int gamma = 2;
void gammaTransformation(int, void*) 
{
	Mat gammaSrc;
	src.convertTo(gammaSrc, CV_32FC1, 1.0);
	pow(gammaSrc, gamma,gammaSrc);
	int c_ = 1;
	gammaSrc = gammaSrc * c_;
	normalize(gammaSrc, gammaSrc, 0, 255, NORM_MINMAX);
	Mat dst;
	gammaSrc.convertTo(dst, CV_8UC1, 1.0);
	convertScaleAbs(dst, dst);
	namedWindow("伽马变换结果", WINDOW_FREERATIO);
	imshow("伽马变换结果", dst);

}
int main(int argc, char** argv) 
{
	src = imread("D:/images/gamma.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		exit(0);
	}
	namedWindow("input",WINDOW_FREERATIO);
	imshow("input", src);
	createTrackbar("gamma值", "input", &gamma, 35, gammaTransformation);
	gammaTransformation(2,0);
	waitKey(0);
	destroyAllWindows();
	return 0;
}