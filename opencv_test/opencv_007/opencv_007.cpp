#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv) 
{
	Mat src_cat = imread("D:/images/cat.jpg",IMREAD_GRAYSCALE);
	//在统计最大最小值得时候要以灰度图像的方式读入 调用 minMaxLoc方法
	if (src_cat.empty()) 
	{
		printf("can`t oprn this ph \n");
	}
	namedWindow("src_cat_demo",WINDOW_FREERATIO);
	imshow("src_cat_demo", src_cat);

	int h = src_cat.rows;
	int w = src_cat.cols;
	int ch = src_cat.channels();
	printf("h:%d w:%d channels:%d\n",h,w,ch);
	double min_val, max_val;
	Point minloc, maxloc;
	//minMaxLoc 只支持单通道的min max 
	minMaxLoc(src_cat,&min_val,&max_val,&minloc,&maxloc);
	printf("min:%.2f, max:%.2f, minloc:(%d,%d) maxloc:(%d,%d)\n",
			min_val, max_val, minloc.x, minloc.y, maxloc.x, maxloc.y);
	Mat mask = Mat::zeros(src_cat.size(), CV_8UC1);
	for (int h = 0; h<mask.rows;h++) 
	{	
		for (int w = 0; w < mask.cols; w++) 
		{
			mask.at<uchar>(h, w) = 255;
		}
	}
	//带ROI
	minMaxLoc(src_cat, &min_val, &max_val, &minloc, &maxloc,mask);
	printf("min:%.2f, max:%.2f, minloc:(%d,%d) maxloc:(%d,%d)\n",
		min_val, max_val, minloc.x, minloc.y, maxloc.x, maxloc.y);
	
	/**** 查找图片的均值******/
	//返回的是一个Scalar对象
	Mat src_dog = imread("D:/images/dog.jpg",-1);
	imshow("dog_demo", src_dog);
	Scalar s = mean(src_dog);
	printf("mean[0]:%.2f mean[1]:%.2f mean[2]:%.2f \n", s[0], s[1], s[2]);

	Mat mm, mstd;
	meanStdDev(src_dog, mm, mstd);
	int mstd_rows = mstd.rows;
	printf("mstd_rows: %d\n", mstd_rows);
	printf("src_stdDev%.2f %.2f %.2f\n",mstd.at<double>(0,0), 
			mstd.at<double>(1, 0),mstd.at<double>(2, 0));

	//创建一个纯红色的bgr图片
	/*
	Mat src_red = Mat::zeros(Size(512,512),CV_8UC3);
	src_red = Scalar(0, 0, 255);
	meanStdDev(src_red, mm, mstd);
	printf("src_red_stdDev%.2f %.2f %.2f\n", mstd.at<double>(0, 0),
		mstd.at<double>(1, 0), mstd.at<double>(2, 0));
	printf("src_red_mean%.2f %.2f %.2f\n", mm.at<double>(0, 0),
		mm.at<double>(1, 0), mm.at<double>(2, 0));
	*/
	// 统计图像的像素信息
	vector<int> totalPv(256);
	for (int i =0; i<256;i++) 
	{
		totalPv[i] = 0;
	}
	for (int h = 0; h < src_cat.rows; h++) 
	{
		for (int w = 0; w < src_cat.cols; w++) 
		{
			int pv = src_cat.at<uchar>(h, w);
			totalPv[pv]++;
		}
	}
	for (int i = 0; i < 256; i++) 
	{
		cout <<totalPv[i] << " ";
		if (i % 10 == 0) 
		{
			cout << endl;
		}
	}
	cout << endl; 
	waitKey(0);
	destroyAllWindows();
	return 0;
}