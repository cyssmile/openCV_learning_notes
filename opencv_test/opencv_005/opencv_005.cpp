#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{	/*
	******************这部分是两个的Mat的加减乘除操作***********************
	Mat src1= imread("D:/opencv/sources/samples/data/WindowsLogo.jpg", -1);
	Mat src2 = imread("D:/opencv/sources/samples/data/LinuxLogo.jpg", -1);
	
	if (src1.empty() || src2.empty()) {
		printf("could open this ph\n");
		return -1;
	}
	namedWindow("src1_demo", WINDOW_FREERATIO);
	imshow("src1_demo", src1);

	namedWindow("src2_demo", WINDOW_FREERATIO);
	imshow("src2_demo", src2);

	int height = src1.rows;
	int width = src1.cols;
	int ch = src1.channels();
	
	//加法操作 加法加起来大于255 变为255
	Mat dest1;
	add(src1, src2, dest1);
	imshow("dest1_demo", dest1);

	//减法操作
	Mat dest2;
	subtract(src1,src2,dest2);
	imshow("dest2_demo", dest2);

	//乘法操作
	Mat dest3;
	multiply(src1, src2, dest3);
	imshow("multiply_demo", dest3);

	//除法操作
	Mat dest4;
	divide(src1, src2, dest4);
	imshow("divide", dest4);
	*/

	/****************************************************/
	/***这部分改变图片的亮度***/
	Mat src_dog = imread("D:/images/dog.jpg", IMREAD_COLOR);
	imshow("src_dog_demo", src_dog);
	Mat black_bg = Mat::zeros(src_dog.size(), src_dog.type());
	Mat dst;
	//add(src_dog, black_bg, dst);
	//如果加上的是全零的Mat，不会对原图像产生影响
	//对加入的图片进行赋值
	black_bg = Scalar(50, 50, 50);
	add(src_dog, black_bg, dst); //加上具有初值的Mat，
	imshow("result_demo", dst);

	Mat dst4;
	addWeighted(src_dog, 1.2, black_bg, 0.0, 0.7, dst4);
	//addWeighted ->   dst = src1*x + src2*y +b
	//addWeighted(src1, x, src2, y, b, dst);
	imshow("dst_demo", dst4);
	waitKey(0);
	destroyAllWindows();
	return 0;
}