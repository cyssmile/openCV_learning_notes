#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void addSoaltAndPepperNoise(Mat &images, int numberOfNoise);
void addGaussianNoise(Mat &images,Scalar mean,Scalar meanDev);
void compareMedianBlurAndGaussianDealSAPN(Mat &images_noise,int SizeOfMedianKenel,
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
	addSoaltAndPepperNoise(images_src, 10000);
	compareMedianBlurAndGaussianDealSAPN(images_src,3,Size(5,5));
	waitKey(0);
	destroyAllWindows();
	return 0;
}

/*
* add salt and pepper noise into source images
* cyssmile 
* 2020/3/15
*/
void addSoaltAndPepperNoise(Mat &images,int numberOfNoise) 
{
	RNG rng(12345);
	int row = images.rows;
	int col = images.cols;
	for (int i = 0; i < numberOfNoise; i++)
	{
		int x = rng.uniform(0, row);
		int y = rng.uniform(0, col);
		if (i % 2 == 0)
		{
			images.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
		}
		else
		{
			images.at<Vec3b>(x, y) = Vec3b(0, 0, 0);
		}
	}
	imshow("salt and pepper noise", images);
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
	imshow("GaussianNoiseDst_win", GaussianNoiseDst);
}
/*
* compare medianBlur and GaussianBlur in process a image with salt and pepper noise
* cyssmile
* 2020/3/15
*/
void compareMedianBlurAndGaussianDealSAPN(Mat &images_noise, int SizeOfMedianKenel,
											Size GuassianKenel) 
{
	imshow("salt and pepper noise image", images_noise);
	Mat dst;
	medianBlur(images_noise,dst, SizeOfMedianKenel);
	imshow("medianBlur",dst);

	Mat dst1;
	GaussianBlur(images_noise, dst1, GuassianKenel, 0, BORDER_DEFAULT);
	imshow("gaussianBlur", dst1);
}