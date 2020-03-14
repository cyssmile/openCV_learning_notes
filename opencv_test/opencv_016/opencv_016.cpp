#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;
int main(int argc, char ** argv) 
{
	/*
	* 使用拉普拉斯算子锐化增强图片
	*/
	Mat src_0 = imread("D:/images/moon.jpg",-1);
	if (src_0.empty()) 
	{
		cout << "can`t open this ph" << endl;
	}
	
	Mat src;
	GaussianBlur(src_0,src,Size(3,3),0,BORDER_DEFAULT);
	imshow("src_win", src);
	/*
	*拉普拉斯算子定义
	*/
	//Mat Rok = (Mat_<int>(3,3)<<0,1,0,1,-4,1,0,1,0);
	Mat Rok = (Mat_<int>(3, 3) << -1,-1,-1,-1,8,-1,-1,-1,-1);
	Mat dst;
	/*
	* 未标定拉普拉斯的图片
	*/
	filter2D(src,dst,CV_32F,Rok,Point(-1,-1),0,BORDER_DEFAULT);
	convertScaleAbs(dst, dst);//将原图转换到8bit

	/*
	* 以下注释代码是测试通过 convertScaleAbs转换后图片中像素的最大和最小值
	*/
	/*
	double min, max;
	Point minIndex, maxIndex;
	vector<Mat> split_dst(3);
	split(dst, split_dst);
	minMaxLoc(split_dst[2], &min, &max, &minIndex, &maxIndex);
	cout << min <<" "<<max<< endl;
	*/
	/*
	*在拉普拉斯图片中有正有负
	*/
	imshow("dst_win",dst);

	/*
	* 带标定后的拉普拉斯图片
	*/
	Mat calibration_dst;
	filter2D(src, calibration_dst, CV_32F, Rok, Point(-1, -1),20, BORDER_DEFAULT);
	convertScaleAbs(calibration_dst, calibration_dst);//将原图转换到8bit
	imshow("calibration_dst_win", calibration_dst);

	/*
	* 将原始图片与标定后的细节图片合成
	*/
	Mat merge_dst;
	add(src, calibration_dst,merge_dst,Mat(),-1);
	normalize(merge_dst, merge_dst,0,255,NORM_MINMAX,-1,Mat());
	imshow("merge_dst_win", merge_dst);

	waitKey(0);
	destroyAllWindows();
	return 0;
}