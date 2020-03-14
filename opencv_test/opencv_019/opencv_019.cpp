#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc,char** argv) 
{
	Mat src = imread("D:/images/dog.jpg", -1);
	if (src.empty()) 
	{
		cout << " can`t open this ph" << endl;
	}
	imshow("src_win",src);

	Mat images_src = src.clone();
	/*
	* salt and pepper noise
	*/
	RNG rng(12345);
	int row = src.rows;
	int col = src.cols;
	int numberOfNoise = 10000;
	for (int i=0;i<numberOfNoise;i++) 
	{
		int x = rng.uniform(0, row);
		int y = rng.uniform(0, col);
		if (i % 2 == 0) 
		{
			src.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
		}
		else
		{
			src.at<Vec3b>(x, y) = Vec3b(0, 0, 0);
		}
	}
	imshow("salt and pepper noise",src);

	/*
	*
	* GaussianNoise
	*/
	Mat GaussianNoise = Mat::zeros(images_src.size(),images_src.type());
	randn(GaussianNoise,Scalar(20,20,20),Scalar(30,30,30));//randn会产生正态分布的噪声Mat
	Mat GaussianNoiseDst;
	add(images_src,GaussianNoise,GaussianNoiseDst);
	imshow("GaussianNoiseDst_win",GaussianNoiseDst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
