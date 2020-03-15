#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void addGaussianNoise(Mat &images, Scalar mean, Scalar meanDev);
void compareMedianBlurAndGaussianDeaGaussianNoise(Mat &images_noise, int SizeOfMedianKenel,
										Size GuassianKenel);
int main(int argc, char** argv)
{
	Mat src = imread("D:/images/hl.jpg", -1);
	if (src.empty())
	{
		cout << " can`t open this ph" << endl;
	}
	imshow("src_win", src);
	Mat images_src = src.clone();
	addGaussianNoise(images_src,Scalar(10,10,10),Scalar(30,30,30));
	compareMedianBlurAndGaussianDeaGaussianNoise(images_src, 3, Size(5, 5));
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
}
/*
* compare medianBlur and GaussianBlur in process a image with Guassian noise
* cyssmile
* 2020/3/15
*/
void compareMedianBlurAndGaussianDeaGaussianNoise(Mat &images_noise, int SizeOfMedianKenel,
												Size GuassianKenel)
{
	imshow("Gaussian noise image", images_noise);
	Mat dst;
	medianBlur(images_noise, dst, SizeOfMedianKenel);
	imshow("medianBlur", dst);

	Mat dst1;
	GaussianBlur(images_noise, dst1, GuassianKenel, 0, BORDER_DEFAULT);
	imshow("gaussianBlur", dst1);
}