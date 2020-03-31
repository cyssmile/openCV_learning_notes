#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
using namespace std;
using namespace cv;

/*
* 图像开操作
* 开操作 = 腐蚀 + 膨胀  目的：删除小的干扰块
*/
void morphologyOpenDemo(Mat& original, int shape, cv::Size size, cv::Point anchor);
/*
* 图像闭操作
* 闭操作 = 膨胀 + 腐蚀  目的:填充闭合区域
*/


int main(int argc, char** argv) {
	Mat src = imread("D:/images/openSubDetail.jpg", IMREAD_UNCHANGED);
	if (src.empty()) {
		cout << "can`t read this image" << endl;
	}

	imshow("source",src);
	/*
	morphologyOpenDemo(src,MORPH_RECT,Size(3,3),Point(-1,-1));
	Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3),Point(-1,-1));
	Mat dst;
	morphologyEx(src,dst,MORPH_OPEN,kernel,Point(-1,-1),2);
	imshow("open_dst", dst);

	Mat detail;
	subtract(src,dst,detail);
	imshow("open_detail", detail);
	*/
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray,binary,0,255,THRESH_BINARY_INV|THRESH_OTSU);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	imshow("binary_win", binary);
	Mat dst;
	morphologyEx(binary, dst, MORPH_OPEN, kernel, Point(-1, -1), 1);
	imshow("dst_win",dst);
	/*
	* 提取目标
	*/
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dst,contours, hierarchy,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE,Point());
	Mat canvas = Mat(src.size(),src.type());
	canvas = Scalar::all(255);
	for (size_t t =0;t<contours.size();t++) 
	{
		drawContours(canvas,contours,t,Scalar(0,0,0),1,8);
	}
	imshow("canvas",canvas);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void morphologyOpenDemo(Mat& original,int shape,cv::Size size,cv::Point anchor) 
{	
	if (original.empty()) 
	{
		cout << " can`t get this ph" << endl;
	}
	namedWindow("open_source_win",WINDOW_FREERATIO);
	imshow("open_source_win",original);
	Mat kernel = getStructuringElement(shape, size, anchor);
	Mat erode_result;
	erode(original, erode_result, kernel);
	Mat dst;
	dilate(erode_result, dst, kernel);
	namedWindow("open_dst_win", WINDOW_FREERATIO);
	imshow("open_dst_win", dst);
}