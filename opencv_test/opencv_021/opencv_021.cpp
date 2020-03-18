#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void addGaussianNoise(Mat &images, Scalar mean, Scalar meanDev);


int main(int argc,char** argv) 
{	
	Mat src = imread("D:/images/hl.jpg", -1);
	if (src.empty()) 
	{
		cout << "can`t open this ph" << endl;
	}
	addGaussianNoise(src, Scalar(15, 15, 15), Scalar(25, 25, 25));
	Mat dst;
	bilateralFilter(src,dst,0,100,10,BORDER_DEFAULT);
	imshow("bilaterFilter_demo",dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
/*
* add GaussianNoise into source image
* cyssmile
* 2020/3/15
*/
void addGaussianNoise(Mat &images, Scalar mean, Scalar meanDev)
{
	Mat GaussianNoise = Mat::zeros(images.size(), images.type());
	randn(GaussianNoise, mean, meanDev);//randn会产生正态分布的噪声Mat
	Mat GaussianNoiseDst;
	add(images, GaussianNoise, images);
	imshow("GaussianNoiseDst_win", images);
}