#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
	Mat src = imread("D:/images/dog.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cout << "can`t read this image" << endl;
	}
	int width = src.cols;
	int height = src.rows;
	int dim = src.channels();
	int src_d = src.depth();
	int src_t = src.type();

	if (src_t == CV_8UC3) {
		cout << "(width, height) =  " << "(" << width << ", " << height << ")" << " ";
		cout << "dims = " << dim << " ";
		cout << "depth = " << src_d << " ";
		cout << "typr = " << src_t << " ";
	}

	//namedWindow("001_demo", WINDOW_AUTOSIZE);
	//namedWindow("001_demo", WINDOW_FREERATIO);
	namedWindow("002_demo", WINDOW_FREERATIO);
	/*
	*imshow 会展示BGR三通道的像，不支持透明通道
	*/
	imshow("002_demo", src);
	waitKey(0);
	//imwrite("D:/images/test.png", src);
	destroyAllWindows();
	return 0;
}
