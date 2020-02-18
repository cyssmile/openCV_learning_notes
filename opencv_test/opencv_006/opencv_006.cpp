#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv) 
{
	//图像的位操作
	Mat src = imread("D:/opencv/sources/samples/data/fruits.jpg", -1);
	if (src.empty()) 
	{
		cout << "打开图片失败" << endl;
	}
	namedWindow("src_demo", WINDOW_FREERATIO);
	imshow("src_demo", src);

	//图像取反
	Mat dst1;
	bitwise_not(src, dst1, Mat());
	//图像取反 第一个参数是原图像， 第二参数是输出图像， 第三个是mask
	//图像取反 相当于 255 减去原像素值
	//src.at<Vec3b>(row,col)[0] = 255 - src.at<Vec3b>(row, col);
	//Mat mask = MaT::zears(src.size(),CV_8UC1);
	imshow("bitwise_not", dst1);

	//图像取与
	//mask很重要大小和src原图片相同，单通道，如果去反是mask值为0，就为黑色
	//如果非零，全1，就是255。就正常取反
	Mat dst3;
	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	/**
	可以通过mask来实现ROI区域选定，只需要申请相同大小，单通道的全零的mask
	将ROI区域的值变为255，当进行取反操作的时候，为255的区域将会全部取反
	**/
	int hieght = mask.rows;
	int width = mask.cols;
	for (int hi = 0; hi < hieght / 2; hi++) 
	{
		for (int wi = 0; wi < width / 2; wi++) 
		{
			mask.at<uchar>(hi, wi) = 255;
		}
	}
	bitwise_not(src, dst3, mask);
	imshow("bitwise_not_mask", dst3);
	/*
	bitwise_and 有四个参数 第一原图 第二个与什么图片相与， 第三个输出Mat 第四个mask
	*/
	Mat dst2;
	//bitwise_and(src, src, dst2, Mat());//原图相与得原图
	bitwise_and(src, src, dst2, mask);
	imshow("bitwise_and", dst2);
	

	//bitwise_or 或操作 有1 就是1
	Mat dst4;
	Mat mask2 = Mat::zeros(src.size(), src.type());
	//ROI 区域
	int hieght2 = mask2.rows;
	int width2 = mask2.cols;
	for (int hi = 0; hi < hieght2 / 2; hi++)
	{
		for (int wi = 0; wi < width2 / 2; wi++)
		{
			mask.at<uchar>(hi, wi) = 127;
		}
	}

	bitwise_or(src, mask2,dst4, mask);
	imshow("bitwise_or", dst4);

	waitKey(0);
	destroyAllWindows();
	return 0;
}