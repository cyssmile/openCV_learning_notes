#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
void show_photo(const Mat& origin) 
{
	namedWindow("input",WINDOW_FREERATIO);
	imshow("input", origin);
}
int main(int argc, char* argv)
{
	Mat src = imread("D:/images/dog.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cout << "can`t open this ph!" << endl;
		exit(0);
	}
	show_photo(src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}