#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char **argv) 
{
	Mat src = imread("D:/images/cat.jpg",-1);
	if (src.empty()) 
	{
		cout << " can`t open this ph" << endl;
	}
	imshow("src_demo", src);

	Mat dst;
	GaussianBlur(src,dst,Size(5,5),0);
	imshow("GaussianBlur_demo",dst);
	//Size 和sigmaX 只需要给出一个就好了,Size应为奇数*奇数
	//GaussianBlur(src, dst, Size(0, 0), 15);//不设置sigmaX的情况，会根据sigmaX算出SIze
	// 默认sigmaY =0
	/*
	*
	* 盒子模糊 盒子模糊分为x 和y 方向
	*/
	Mat box_dst;
	boxFilter(src, box_dst, -1, Size(12, 3), Point(-1, -1), true, BORDER_DEFAULT);
	//通道数 -1 表示默认方向 锚定点为（-1，-1）
	imshow("box_dst_win",box_dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}