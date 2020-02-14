#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
	Mat src = imread("D:/opencv/sources/samples/data/opencv-logo.png",IMREAD_UNCHANGED); 
	/*
	* IMREAD_UNCHANGED //不改变 类似 -1
	* IMREAD_COLOR  // 加载BGR
	* IMREAD_ANYCOLOR //加载任意色彩空间
	* IMREAD_GRAYSCALE // 加载灰度
	*/
	if (src.empty()) {
		cout << "can`t read this image" << endl;
	}
	//namedWindow("001_demo", WINDOW_AUTOSIZE);
	//namedWindow("001_demo", WINDOW_FREERATIO);
	namedWindow("001_demo", WINDOW_NORMAL);
	/*
	*imshow 会展示BGR三通道的像，不支持透明通道
	*/
	imshow("001_demo", src);
	waitKey(0);
	imwrite("D:/images/test.png", src);
	destroyAllWindows();
	return 0;
}
