#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv;
using namespace std;
int main(int argc, char ** argv)
{
	Mat src = imread("D:/images/beauty.jpg", -1);
	if (src.empty())
	{
		printf("can`t open this ph\n");
	}
	namedWindow("src_demo", WINDOW_FREERATIO);
	imshow("src_demo", src);
	Rect rec;
	rec.x = 50;
	rec.y = 50;
	rec.width = 200;
	rec.height = 200;
	Mat sub = src(rec);  //可以截取原Mat中 一部分， 共享的Mat,
	//当使用clone才会复制相应的那一部分
	//Mat sub_clone = src(rec).clone();
	namedWindow("sub_demo", WINDOW_FREERATIO);
	imshow("sub_demo",sub);
	waitKey(0);
	destroyAllWindows();
	return 0;
}