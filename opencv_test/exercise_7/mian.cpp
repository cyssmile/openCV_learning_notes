#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void printKernel(const Mat& kernel);
int getBordValue(int Length, int step, int kernelSize);
void ifilter(Mat& src, Mat& dst, int kernelSize, double** templateMatrix);
void autoCopyMakeBorder(Mat& images, int borderType, int step, int kernelSize);
void iMeanBlur(Mat& src, Mat& dst, int kernelSize);
void iGaussianBlur(Mat &src, Mat &dst,int kernelSize,double sigma);
void iLaplacian(Mat& src, Mat& dst);
void iRobert(Mat& src, Mat& dst_x, Mat& dst_y, Mat& dst);
void iSobel(Mat& src, Mat& dst_x, Mat& dst_y, Mat& dst);
int main(int argc, char** argv) 
{

	Mat src = imread("D:/images/dog.jpg", IMREAD_COLOR);
	if (src.empty()) 
	{
		cout << "打开图片失败" << endl;
		exit(0);
	}

	imshow("input", src);
	int kernelSize = 9;
	/*
	* 调用filter2D实现9*9 均值模糊
	*/
	/*
	Mat dst0;
	Mat mKernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);
	//调用库函数实现
	filter2D(src, dst0, CV_32F, mKernel, Point(-1, -1));
	convertScaleAbs(dst0, dst0);
	imshow("调库实现9*9 均值模糊", dst0);
	*/
	/*
	* 9*9 均值模糊, 这里自己实现的算法太慢了
	*/
	
	Mat dst;
	iMeanBlur(src, dst, 9);
	imshow("9*9均值滤波", dst);

	/*
	* 9*9 高斯模糊
	*/
	Mat dst1;
	double sigma = 1;
	iGaussianBlur(src, dst1, kernelSize, sigma);
	imshow("9*9高斯模糊", dst1);

	/*
	* 拉普拉斯模板
	*/
	Mat dst2;
	iLaplacian(src, dst2);
	imshow("拉普拉斯模板", dst2);

	/*
	* cv 拉普拉斯函数
	*/
	/*
	Mat dst2_1;
	Laplacian(src,dst2_1,CV_32F,3);
	convertScaleAbs(dst2_1, dst2_1);
	imshow("cv 拉普拉斯结果", dst2_1);
	*/

	/*
	* Robert 算子分两个方向
	*/
	Mat dst3, dst3_x, dst3_y;
	iRobert(src, dst3, dst3_x, dst3_y);
	imshow("Robert_x", dst3_x);
	imshow("Robert_y", dst3_y);
	imshow("Robert", dst3);

	/*
	 Sobel 算子分两个方向
	*/
	Mat dst4, dst4_x, dst4_y;
	iRobert(src, dst4, dst4_x, dst4_y);
	imshow("Sobel_x", dst4_x);
	imshow("Sobel_y", dst4_y);
	imshow("Sobel", dst4);

	waitKey(0);
	destroyAllWindows();
	return 0;
}

/*
* get the value of copyMakeBorder 获取需要边缘填充的大小
* cyssmile
* 2020/6/7
*/
int getBordValue(int Length, int step, int kernelSize)
{
	return (Length * (step - 1) - step + kernelSize) / 2;
}

/*
* auto fill picture， 进行边缘填充
* cyssmile
* 2020/6/7
*/
void autoCopyMakeBorder(Mat& images, int borderType, int step, int kernelSize)
{
	int row = images.rows;
	int col = images.cols;
	int hightValue = getBordValue(row, step, kernelSize);
	int widthValue = getBordValue(col, step, kernelSize);
	copyMakeBorder(images, images, hightValue, hightValue, widthValue, widthValue, borderType);
}

/*
* 打印输出模板模板
*/
void printKernel(const Mat& kernel) 
{
	int ch = kernel.channels();
	cout << "通道数为：" << ch << endl;
	for (int h = 0; h < kernel.rows; h++) 
	{
		for (int w = 0; w < kernel.cols; w++) 
		{
			int temp = kernel.at<uchar>(h, w);
			cout << temp << " ";
		}
		cout << endl;
	}
}
/*
* 自己实现的filter函数，类似系统的filter2D函数
* Point(-1,-1)默认， 填充方式BORDER_DEFAULT
*/
void ifilter(Mat& src, Mat& dst, int kernelSize,double** templateMatrix)
{
	assert(src.channels() || src.channels() == 3);
	dst = src.clone();
	//这里默认处理的N*N的filter， 如果长宽不一致，单独获取长宽
	//填充边缘大小
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, kernelSize);
	int colPadding = getBordValue(col, 1, kernelSize);
	//这里不要直接填充src,因为这里是引用，可能后面的实验会重复填充
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);


	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			double sum[3] = { 0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						sum[0] += templateMatrix[k+ rowPadding][m+colPadding] * t_src.at<uchar>(i + k, j + m);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						auto tmp = templateMatrix[k + rowPadding][m + colPadding];
						sum[0] += tmp * rgb[0];
						sum[1] += tmp * rgb[1];
						sum[2] += tmp * rgb[2];
					}
				}
			}
			//限定像素值在0-255之间
			for (int i = 0; i < channels; i++) {
				if (sum[i] < 0)
					sum[i] = 0;
				else if (sum[i] > 255)
					sum[i] = 255;
			}
			//
			if (channels == 1) {
				dst.at<uchar>(i-rowPadding, j-colPadding) = static_cast<uchar>(sum[0]);
			}
			else if (channels == 3) {
				Vec3b rgb;
				rgb[0] = static_cast<uchar>(sum[0]);
				rgb[1] = static_cast<uchar>(sum[1]);
				rgb[2] = static_cast<uchar>(sum[2]);

				dst.at<Vec3b>(i - rowPadding, j - colPadding) = rgb;
			}
		}
	}
}

/*
* 均值滤波
* 实验要求的都一样，只是模板不一样，实现方法也类似
*/
void iMeanBlur(Mat& src, Mat& dst, int kernelSize)
{

	//调用库实现的方法
	/*
	Mat mKernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);
	//调用库函数实现
	filter2D(src, dst, CV_32F, mKernel, Point(-1, -1));
	convertScaleAbs(dst, dst);
	imshow("dst", dst);
	*/

	//先根据kernelSize 创建均值模糊的模板
	double** templateMatrix = new double* [kernelSize];
	for (int i = 0; i < kernelSize; i++) {
		templateMatrix[i] = new double[kernelSize];
	}
	int tmp = kernelSize * kernelSize;
	int origin = kernelSize / 2;
	for (int i = 0; i < kernelSize; i++) {
		for (int j = 0; j < kernelSize; j++) {
			templateMatrix[i][j] = 1.0 / tmp;
		}
	}

	ifilter(src, dst, kernelSize, templateMatrix);
	//删除模板
	for (int i = 0; i < kernelSize; i++) {
		delete[] templateMatrix[i];
	}
	delete[] templateMatrix;

}
void iGaussianBlur(Mat& src, Mat& dst, int kernelSize, double sigma) 
{
	//根据高斯模糊的kernelSize创建高斯模糊的模板
	double PI = acos(-1);
	//动态申请二维数组空间
	double** kernel = new double* [kernelSize];

	for (int i = 0; i < kernelSize; i++) {
		kernel[i] = new double[kernelSize];
	}
	
	int origin =kernelSize / 2; // 以模板的中心为原点
	double x2, y2;
	double sum = 0;
	for (int i = 0; i < kernelSize; i++)
	{
		x2 = pow(i - origin, 2);
		for (int j = 0; j < kernelSize; j++)
		{
			y2 = pow(double(j - origin), 2);
			double g = exp(-(x2 + y2) / (2 * sigma * sigma));
			sum += g;
			kernel[i][j] = g;
		}
	}
	//归一化
	double k = 1 / sum;
	for (int i = 0; i < kernelSize; i++) {
		for (int j = 0; j < kernelSize; j++) {
			kernel[i][j] *= k;
		}
	}
	ifilter(src, dst, kernelSize, kernel);
	//删除动态分配的二维数组
	for (int i = 0; i < kernelSize; i++) 
	{
		delete[] kernel[i];
	}
	delete[] kernel;
}

void iLaplacian(Mat& src, Mat& dst) {
	//拉普拉斯常用的有几个模板，我只选择了其中的一个
	vector<double> list = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
	double** templateMatrix = new double* [3];
	for (int i = 0; i < 3; i++) {
		templateMatrix[i] = new double[3];
	}
	int k = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			templateMatrix[i][j] = list[k++];
		}
	}
	ifilter(src, dst, 3, templateMatrix);

	for (int i = 0; i < 3; i++) 
	{
		delete[] templateMatrix[i];
	}
	delete[] templateMatrix;
}

void iRobert(Mat& src, Mat& dst_x, Mat& dst_y,Mat& dst) 
{
	//前面的几处实现，已经代表能够自己实现这些滤波
	//这里我打算用常用的Cv库里的方法实现利用Robert滤波器处理图片,这里的
	Mat Robert_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
	Mat Robert_y = (Mat_<int>(2, 2) << 0, 1, -1, 0);

	filter2D(src, dst_x, CV_32F, Robert_x, Point(-1, -1), 0, BORDER_DEFAULT);
	convertScaleAbs(dst_x, dst_x);

	filter2D(src, dst_y, CV_32F, Robert_y, Point(-1, -1), 0, BORDER_DEFAULT);
	convertScaleAbs(dst_y, dst_y);

	add(dst_x, dst_y, dst);
	convertScaleAbs(dst, dst);

}

void iSobel(Mat& src, Mat& dst_x, Mat& dst_y, Mat& dst) 
{
	Mat Sobel_x = (Mat_<int>(3, 3) << -1, 0,1,-2, 0,2, -1,0,1);
	Mat Sobel_y = (Mat_<int>(3, 3) << -1,-2,-1,0,0,0,1,2,1);

	filter2D(src, dst_x, CV_32F, Sobel_x, Point(-1, -1), 0, BORDER_DEFAULT);
	convertScaleAbs(dst_x, dst_x);

	filter2D(src, dst_y, CV_32F, Sobel_y, Point(-1, -1), 0, BORDER_DEFAULT);
	convertScaleAbs(dst_y, dst_y);

	add(dst_x, dst_y, dst);
	convertScaleAbs(dst, dst);
}