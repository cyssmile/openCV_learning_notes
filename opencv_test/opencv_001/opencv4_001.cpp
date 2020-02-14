#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
	Mat src = imread("D:/opencv/sources/samples/data/opencv-logo.png",IMREAD_UNCHANGED); 
	/*
	* IMREAD_UNCHANGED //���ı� ���� -1
	* IMREAD_COLOR  // ����BGR
	* IMREAD_ANYCOLOR //��������ɫ�ʿռ�
	* IMREAD_GRAYSCALE // ���ػҶ�
	*/
	if (src.empty()) {
		cout << "can`t read this image" << endl;
	}
	//namedWindow("001_demo", WINDOW_AUTOSIZE);
	//namedWindow("001_demo", WINDOW_FREERATIO);
	namedWindow("001_demo", WINDOW_NORMAL);
	/*
	*imshow ��չʾBGR��ͨ�����񣬲�֧��͸��ͨ��
	*/
	imshow("001_demo", src);
	waitKey(0);
	imwrite("D:/images/test.png", src);
	destroyAllWindows();
	return 0;
}
