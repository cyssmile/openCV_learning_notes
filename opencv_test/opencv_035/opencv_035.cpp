#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
	Mat src = imread("D:/images/erode.jpg", IMREAD_UNCHANGED);
	if (src.empty()) {
		cout << "can`t read this image" << endl;
	}
	namedWindow("source", WINDOW_FREERATIO);
	imshow("source", src);
	Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3),Point(-1,-1));
	//¸¯Ê´
	Mat erode_result;
	erode(src,erode_result,kernel);
	namedWindow("erode_source", WINDOW_FREERATIO);
	imshow("erode_source", erode_result);
	//ÅòÕÍ
	Mat dilate_result;
	dilate(src, dilate_result, kernel);
	namedWindow("dilate_source", WINDOW_FREERATIO);
	imshow("dilate_source", dilate_result);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
