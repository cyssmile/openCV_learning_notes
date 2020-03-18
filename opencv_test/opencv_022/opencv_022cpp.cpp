#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
void showCanny(int, void*);
Mat src;
int value = 50;
int main() 
{
    src = imread("D:/images/beauty.jpg",-1);
	if (src.empty()) 
	{
		cout << "can`t open this ph" << endl;
	}
	namedWindow("input", WINDOW_FREERATIO);
	imshow("input",src);
	createTrackbar("threshold_value","input",&value,100,showCanny);
	showCanny(0, 0);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
void showCanny(int , void* )
{
	Mat edges;
	Canny(src,edges,value,value*3,3,false);
	namedWindow("dst_demo",WINDOW_FREERATIO);
	imshow("dst_demo",edges);
}