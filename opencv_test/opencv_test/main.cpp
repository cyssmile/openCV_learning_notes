#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/dog.jpg"); // BGR
	if (src.empty()) {
		cout << " read images error" << endl;
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}