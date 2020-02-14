#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
	Mat src = Mat(256, 256,CV_8UC3);
	namedWindow("003_demo", WINDOW_FREERATIO);
	src = Scalar(255,0,0);//blue green red
	imshow("003_demo", src);

	//t1
	Mat t1 = Mat(Size(512, 512), CV_8UC3);
	namedWindow("t1_wind", WINDOW_FREERATIO);
	t1 = Scalar(255, 0, 255);
	imshow("t1_wind", t1);
	
	//t2
	Mat t2 = Mat::zeros(Size(256, 256),CV_8UC3);
	namedWindow("t2_wind", WINDOW_FREERATIO);
	imshow("t2_wind", t2);
	
	//t3 read one ph
	Mat t3 = imread("D:/images/dog.jpg", IMREAD_COLOR);
	namedWindow("t3_wind", WINDOW_FREERATIO);
	imshow("t3_wind", t3);

	//
	Mat t4 = t3; //Mat t3
	namedWindow("t4_wind", WINDOW_FREERATIO);
	imshow("t4_wind", t4);

	// t5
	Mat t5 = t3.clone();
	namedWindow("t5_wind", WINDOW_FREERATIO);
	imshow("t5_wind", t5);

	//t6
	Mat t6;
	t5.copyTo(t6);
	namedWindow("t6_wind", WINDOW_FREERATIO);
	imshow("t6_wind", t6);

	//t7 
	Mat t7 = Mat::zeros(t3.size(),t3.type());
	imshow("t7_wind",t7);

	
	waitKey(0);
	destroyAllWindows();
	return 0;
}
