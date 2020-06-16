#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace cv;
using namespace std;
/*
* 图像去噪
* 算术均值滤波器 几何均值滤波器 谐波和逆谐波均值滤波器
*中值滤波器 自适应中值滤波器
*自适应局部降低噪声的滤波器
* 掌握彩色图像去噪的步骤
*/

/*
* 算术均值滤波器
* cyssmile 
* 2020/6/15
*/
void arithmeticMeanBlur(Mat& src, Mat& dst,int m,int n);
/*
* get the value of copyMakeBorder 获取需要边缘填充的大小
* cyssmile
* 2020/6/7
*/
int getBordValue(int Length, int step, int kernelSize);
/*
* auto fill picture， 进行边缘填充
* cyssmile
* 2020/6/7
*/
void autoCopyMakeBorder(Mat& images, int borderType, int step, int kernelSize);
/*
* 添加椒盐噪声, 盐噪声，椒噪声
* cyssmile
* 2020/6/15
* 通过noiseType 判断是加那种噪声，1为椒盐,2为椒噪声，3为盐噪声
*/
void addSoaltAndPepperNoise(Mat& images, int numberOfNoise,int noiseType);


/*
* add GaussianNoise into source image 设定均值和方差添加高斯噪声
* cyssmile
* 2020/6/15
*/
void addGaussianNoise(Mat& images, Scalar mean, Scalar meanDev);

/*
* 几何均值 
* 这种方式处理是由每个像素的1/mn的次幂得到，这样的可以保留细节运算量较大
* 所以所 几何均值对椒盐 椒 盐 噪声 特别敏感
*/
void geometricMean(Mat& src, Mat& dst, int m, int n);

/*
* 比较5*5 的算术均值滤波对 椒盐 椒 盐 高斯 噪声处理效果
*/
void comparedMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc);

/*
* 比较5*5 的几何均值滤波对 椒盐 椒 盐 高斯 噪声处理效果
*/
void comparedGeometricMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc);

/*
* 谐波均值
* 谐波均值 适合处理盐噪声，不适合处理胡椒噪声，也擅长处理高斯噪声
*/
void harmonicMeanBlur(Mat& src, Mat& dst, int m, int n);

/*
* 比较谐波均值对 椒盐 盐粒 胡椒 高斯 噪声的处理
* cyssmile
* 2020/6/15
*/
void comparedHarmonicMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc);

/*
*逆谐波均值滤波
*/
void inverseHarmonicMeanBlure(Mat& src, Mat& dst, int m, int n, double Q);

/*
* 比较反谐波均值对 椒盐 盐粒 胡椒 高斯 噪声的处理
* cyssmile
* 2020/6/15
*/
void comparedInverseHarmonicMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc,double Q);

/*
*中值滤波
* 中值滤波对处理椒盐噪声 胡椒 盐粒噪声的效果很好
*/
void iMidBlur(Mat& src, Mat& dst, int m, int n);

/*
* 比较中值滤波对椒盐，胡椒，盐粒，高斯噪声的处理效果
*/
void comparedMidBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc);
/*
* 自适应均值滤波器
*/
void adaptiveMeanBlur(Mat& src, Mat& dst, int n, int m);
/*
* 比较自适应均值滤波器 对椒盐 胡椒 盐粒 高斯噪声的处理效果
*/
void comparedAdaptiveMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc);
int main(int argc, char** argv) 
{
	Mat src = imread("D:/images/test.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cout << "读取图片失败" << endl;
		exit(0);
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);


	int row = src.rows;
	int col = src.cols;
	
	/*
	* 添加全图0.1比例的椒盐噪声
	*/
	Mat sapSrc = src.clone();
	addSoaltAndPepperNoise(sapSrc, row * col * 0.1,1);
	imshow("0.1比例的椒盐噪声", sapSrc);


	/*
	* 添加全图0.1 比例的椒噪声
	*/
	Mat pSrc = src.clone();
	addSoaltAndPepperNoise(pSrc, row * col * 0.1, 2);
	imshow("0.1比例的椒噪声", pSrc);
	
	/*
	* 添加全图0.1 比例的盐噪声
	*/
	Mat sSrc = src.clone();
	addSoaltAndPepperNoise(sSrc, row * col * 0.1, 3);
	imshow("0.1比例的盐噪声", sSrc);

	/*
	* 添加均值为15 方差为25 的高斯噪声
	*/
	Mat gSrc = src.clone();
	addGaussianNoise(gSrc, 15, 25);
	imshow("添加均值为15方差为25高斯噪声图片", gSrc);


	/*
	* 利用 m, n = 5, 5 的核进行算术均值滤波 
	*/
	//comparedMeanBlur(sapSrc, sSrc, pSrc,gSrc);


	/*
	* 几何均值 这种方式处理是由每个像素的1/mn的次幂得到，这样的可以保留细节运算量较大
	*/
	comparedGeometricMeanBlur(sapSrc, sSrc, pSrc, gSrc);


	/*
	*	谐波均值滤波 对椒盐 盐粒 胡椒 高斯噪声处理
	* 谐波均值 善于处理 盐粒 高斯噪声，不善于处理胡椒噪声
	*/
	//comparedHarmonicMeanBlur(sapSrc, sSrc, pSrc, gSrc);
	
	/*
	*	反谐波均值滤波
	*/
	//double Q = -1.0;
	//comparedInverseHarmonicMeanBlur(sapSrc, sSrc, pSrc, gSrc,Q);

	/*
	* 中值滤波
	*/
	//comparedMidBlur(sapSrc, sSrc, pSrc, gSrc);

	/*
	*自适应均值滤波
	*/
	//comparedAdaptiveMeanBlur(sapSrc, sSrc, pSrc, gSrc);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void arithmeticMeanBlur(Mat& src, Mat& dst, int m, int n) 
{
	double weight = 1.0 / ((double)m * (double)n);

	//根据m*n 大小的核填充处理图像
	//填充边缘大小
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	//进行算术均值滤波
	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			double sum[3] = { 0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						sum[0] += weight * t_src.at<uchar>(i + k, j + m);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						sum[0] += weight* rgb[0];
						sum[1] += weight * rgb[1];
						sum[2] += weight * rgb[2];
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
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(sum[0]);
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
* 添加椒盐噪声 椒 或者盐噪声
*/
void addSoaltAndPepperNoise(Mat& images, int numberOfNoise, int noiseType)
{
	RNG rng(12345);
	int row = images.rows;
	int col = images.cols;
	//添加椒盐噪声
	if (noiseType == 1)
	{
		for (int i = 0; i < numberOfNoise; i++)
		{
			int x = rng.uniform(0, row);
			int y = rng.uniform(0, col);
			if (i % 2 == 0) {
				images.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
			}
			else {
				images.at<Vec3b>(x, y) = Vec3b(0, 0, 0);
			}
		}
	}
	//添加椒噪声
	if (noiseType == 2)
	{
		for (int i = 0; i < numberOfNoise; i++)
		{
			int x = rng.uniform(0, row);
			int y = rng.uniform(0, col);
			images.at<Vec3b>(x, y) = Vec3b(0, 0, 0);
		}
	}

	//添加盐噪声
	if (noiseType == 3)
	{
		for (int i = 0; i < numberOfNoise; i++)
		{
			int x = rng.uniform(0, row);
			int y = rng.uniform(0, col);
			images.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
		}
	}
}


/*
* add GaussianNoise into source image
* cyssmile
* 2020/3/15
*/
void addGaussianNoise(Mat& images, Scalar mean, Scalar meanDev)
{
	Mat GaussianNoise = Mat::zeros(images.size(), images.type());
	randn(GaussianNoise, mean, meanDev);//randn会产生正态分布的噪声Mat
	//Mat GaussianNoiseDst;
	add(images, GaussianNoise, images);
	//imshow("GaussianNoiseDst_win", GaussianNoiseDst);
}

void comparedMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc)
{
	//5*5 的算术均值滤波处理椒盐噪声
	Mat dst1 = sapSrc.clone();
	arithmeticMeanBlur(sapSrc, dst1, 5, 5);
	imshow("5*5算术均值处理椒盐噪声结果", dst1);

	//5*5 的算术均值滤波处理椒噪声
	Mat dst2 = pSrc.clone();
	arithmeticMeanBlur(pSrc, dst2, 5, 5);
	imshow("5*5算术均值处理椒噪声结果", dst2);

	//5*5 的算术均值滤波处理盐噪声
	Mat dst3 = sSrc.clone();
	arithmeticMeanBlur(sSrc, dst3, 5, 5);
	imshow("5*5算术均值处理盐噪声结果", dst3);

	//5*5 的算术均值滤波处理高斯噪声
	Mat dst4 = gSrc.clone();
	arithmeticMeanBlur(gSrc, dst4, 5, 5);
	imshow("5*5算术均值处理高斯噪声结果", dst4);
}


void geometricMean(Mat& src, Mat& dst, int m, int n)
{
	double weight = 1.0 / ((double)m * (double)n);

	//根据m*n 大小的核填充处理图像
	//填充边缘大小
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	//这里不要直接填充src,因为这里是引用，可能后面的实验会重复填充
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			double sum[3] = { 1,1,1 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						sum[0] *= (double)t_src.at<uchar>(i + k, j + m);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						sum[0] *= rgb[0];
						sum[1] *= rgb[1];
						sum[2] *= rgb[2];
					}
				}
			}
			//乘以1/mn次幂

			for (int i = 0; i < channels; i++) {
				sum[i] = pow(sum[i], weight);
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
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(sum[0]);
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


void comparedGeometricMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc) 
{
	//5*5 的几何均值滤波处理椒盐噪声
	Mat dst1 = sapSrc.clone();
	geometricMean(sapSrc, dst1, 5, 5);
	imshow("5*5几何均值处理椒盐噪声结果", dst1);

	//5*5 的几何均值滤波处理椒噪声
	Mat dst2 = pSrc.clone();
	geometricMean(pSrc, dst2, 5, 5);
	imshow("5*5几何均值处理椒噪声结果", dst2);

	//5*5 的几何均值滤波处理盐噪声
	Mat dst3 = sSrc.clone();
	geometricMean(sSrc, dst3, 5, 5);
	imshow("5*5几何均值处理盐噪声结果", dst3);

	//5*5 的几何均值滤波处理高斯噪声
	Mat dst4 = gSrc.clone();
	geometricMean(gSrc, dst4, 5, 5);
	imshow("5*5几何均值处理高斯噪声结果", dst4);
}

/*
* 谐波均值
* 谐波均值 适合处理盐噪声，不适合处理胡椒噪声，也擅长处理高斯噪声
*/
void harmonicMeanBlur(Mat& src, Mat& dst, int m, int n)
{
	double weight = ((double)m * (double)n);

	//根据m*n 大小的核填充处理图像
	//填充边缘大小
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	//这里不要直接填充src,因为这里是引用，可能后面的实验会重复填充
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	//进行算术均值滤波
	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			double sum[3] = { 0,0,0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						sum[0] += 1.0/(double)t_src.at<uchar>(i + k, j + m);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						sum[0] += 1.0/rgb[0];
						sum[1] += 1.0/rgb[1];
						sum[2] += 1.0/rgb[2];
					}
				}
			}

			//mn/sum[]
			for (int i = 0; i < channels; i++) {
				sum[i] = weight/sum[i];
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
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(sum[0]);
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

void comparedHarmonicMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc) 
{
	//5*5 的谐波均值滤波处理椒盐噪声
	Mat dst1 = sapSrc.clone();
	harmonicMeanBlur(sapSrc, dst1, 5, 5);
	imshow("5*5谐波均值处理椒盐噪声结果", dst1);

	//5*5 的几何均值滤波处理椒噪声
	Mat dst2 = pSrc.clone();
	harmonicMeanBlur(pSrc, dst2, 5, 5);
	imshow("5*5谐波均值处理椒噪声结果", dst2);

	//5*5 的算术均值滤波处理盐噪声
	Mat dst3 = sSrc.clone();
	harmonicMeanBlur(sSrc, dst3, 5, 5);
	imshow("5*5谐波均值处理盐噪声结果", dst3);

	//5*5 的算术均值滤波处理高斯噪声
	Mat dst4 = gSrc.clone();
	harmonicMeanBlur(gSrc, dst4, 5, 5);
	imshow("5*5谐波均值处理高斯噪声结果", dst4);
}

/*
*
*/
void inverseHarmonicMeanBlure(Mat& src, Mat& dst, int m, int n, double Q)
{
	double weight = ((double)m * (double)n);

	//根据m*n 大小的核填充处理图像
	//填充边缘大小
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	//这里不要直接填充src,因为这里是引用，可能后面的实验会重复填充
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	//进行算术均值滤波
	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			double sum[3] = { 0,0,0 };
			double sum1[3] = { 0,0,0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						sum[0] += pow( (double)t_src.at<uchar>(i + k, j + m),Q+1);
						sum1[0] += pow((double)t_src.at<uchar>(i + k, j + m), Q);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						sum[0] += pow(rgb[0],Q+1);
						sum[1] += pow(rgb[1], Q + 1);
						sum[2] += pow(rgb[2], Q + 1);

						sum1[0] += pow(rgb[0], Q);
						sum1[1] += pow(rgb[1], Q);
						sum1[2] += pow(rgb[2], Q);
					}
				}
			}

			double result[3] = { 0,0,0 };
			//限定像素值在0-255之间
			for (int t = 0; t < channels; t++) {
				result[t] = (double)sum[t] / sum1[t];
				if (result[t] < 0)
					result[t] = 0;
				else if (result[t] > 255)
					result[t] = 255;
			}
			//
			if (channels == 1) {
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(result[0]);
			}
			else if (channels == 3) {
				Vec3b rgb;
				rgb[0] = static_cast<uchar>(result[0]);
				rgb[1] = static_cast<uchar>(result[1]);
				rgb[2] = static_cast<uchar>(result[2]);
				dst.at<Vec3b>(i - rowPadding, j - colPadding) = rgb;
			}
		}
	}
}

void comparedInverseHarmonicMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc, double Q) 
{
	//5*5 的反谐波均值滤波处理椒盐噪声
	Mat dst1 = sapSrc.clone();
	inverseHarmonicMeanBlure(sapSrc, dst1, 5, 5, Q);
	imshow("5*5反谐波均值处理椒盐噪声结果", dst1);

	//5*5 的几何均值滤波处理椒噪声
	Mat dst2 = pSrc.clone();
	inverseHarmonicMeanBlure(pSrc, dst2, 5, 5, Q);
	imshow("5*5反谐波均值处理椒噪声结果", dst2);

	//5*5 的几何均值滤波处理盐噪声
	Mat dst3 = pSrc.clone();
	inverseHarmonicMeanBlure(sSrc, dst3, 5, 5, Q);
	imshow("5*5反谐波均值处理盐粒噪声结果", dst3);

	//5*5 的反谐波滤波处理高斯噪声
	Mat dst4 = gSrc.clone();
	inverseHarmonicMeanBlure(gSrc, dst3, 5, 5, Q);
	imshow("5*5反谐波均值处理高斯噪声结果", dst4);
}


/*
*中值滤波
* 中值滤波对处理椒盐噪声 胡椒 盐粒噪声的效果很好
*/
void iMidBlur(Mat& src, Mat& dst, int m, int n)
{
	double weight = ((double)m * (double)n);

	//根据m*n 大小的核填充处理图像
	//填充边缘大小
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	//这里不要直接填充src,因为这里是引用，可能后面的实验会重复填充
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			vector<double> mid0,mid1,mid2;
			mid0.clear();
			mid1.clear();
			mid2.clear();

			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						mid0.push_back((double)t_src.at<uchar>(i + k, j + m));
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						mid0.push_back((double)rgb[0]);
						mid1.push_back((double)rgb[1]);
						mid2.push_back((double)rgb[2]);
					}
				}
			}

			sort(mid0.begin(), mid0.end());
			sort(mid1.begin(), mid1.end());
			sort(mid2.begin(), mid2.end());


			int r = m * n / 2;
			if (channels == 1) {
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(mid0[r]);
			}
			else if (channels == 3) {
				Vec3b rgb;
				rgb[0] = static_cast<uchar>(mid0[r]);
				rgb[1] = static_cast<uchar>(mid1[r]);
				rgb[2] = static_cast<uchar>(mid2[r]);
				dst.at<Vec3b>(i - rowPadding, j - colPadding) = rgb;
			}
		}
	}
}

void comparedMidBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc) 
{
	//5*5 的中值滤波处理椒盐噪声
	Mat dst1 = sapSrc.clone();
	iMidBlur(sapSrc, dst1, 5, 5);
	imshow("5*5中值滤波处理椒盐噪声结果", dst1);

	//5*5 的中值滤波处理椒噪声
	Mat dst2 = pSrc.clone();
	iMidBlur(pSrc, dst2, 5, 5);
	imshow("5*5中值滤波处理椒噪声结果", dst2);

	//5*5 的中值滤波处理盐噪声
	Mat dst3 = pSrc.clone();
	iMidBlur(sSrc, dst3, 5, 5);
	imshow("5*5中值滤波处理盐粒噪声结果", dst3);

	//5*5 的中值滤波处理高斯噪声
	Mat dst4 = gSrc.clone();
	iMidBlur(gSrc, dst3, 5, 5);
	imshow("5*5中值滤波处理高斯噪声结果", dst4);
}

/*
* 自适应均值滤波器
*/
void adaptiveMeanBlur(Mat& src, Mat& dst, int n, int m) 
{

	//根据m*n 大小的核填充处理图像
	//填充边缘大小
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	//这里不要直接填充src,因为这里是引用，可能后面的实验会重复填充
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	//计算全局的方差
	vector<Mat> splitMat;
	split(src,splitMat);
	double stdDevValue[3] = { 0,0,0 };
	int channels = src.channels();
	for (int i = 0; i < channels;i++) 
	{
		Mat mt, dt;
		meanStdDev(splitMat[i], mt, dt);
		stdDevValue[i] = pow(dt.at<double>(0, 0), 2);
	}

	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;
	int roiSize = m * n;
	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {

			//先算选择的ROI区域的均值
			double totalPiex[3] = { 0,0,0 };
			for (int k = -rowPadding; k <= rowPadding; k++) 
			{
				for (int m = -colPadding; m <= colPadding; m++) 
				{
					if (channels == 1) 
					{
						totalPiex[0] += (double)t_src.at<uchar>(i + k, j + m);
					}
					else {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						totalPiex[0] += (double)rgb[0];
						totalPiex[1] += (double)rgb[1];
						totalPiex[2] += (double)rgb[2];
					}
				}
			}
			for (int t = 0; t < channels; t++) {
				//计算得到均值
				totalPiex[t] = (double)totalPiex[t] / roiSize;
			}

			//接下来要算局部方差
			double roiDev[3] = { 0,0,0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						roiDev[0] += pow((double)t_src.at<uchar>(i + k, j + m)-totalPiex[0],2);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						roiDev[0] += pow((double)rgb[0] - totalPiex[0], 2);
						roiDev[1] += pow((double)rgb[1] - totalPiex[1], 2);
						roiDev[2] += pow((double)rgb[2] - totalPiex[0], 2);
					}
				}
			}
			for (int t = 0; t < channels; t++) {
				//计算得到方差
				roiDev[t] = roiDev[t] / roiSize;
			}

			//计算每个像素的值 自适应均值法
			double result[3] = { 0,0,0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						result[0] = t_src.at<uchar>(i + k, j + m)-(stdDevValue[0]/roiDev[0])*(t_src.at<uchar>(i + k, j + m)-totalPiex[0]);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						result[0] = rgb[0] - (stdDevValue[0] / roiDev[0]) * (rgb[0] - totalPiex[0]);
						result[1] = rgb[1] - (stdDevValue[1] / roiDev[1]) * (rgb[1] - totalPiex[1]);
						result[2] = rgb[2] - (stdDevValue[2] / roiDev[2]) * (rgb[2] - totalPiex[2]);
					}
				}
			}
			
			//限定像素值在0-255之间
			for (int t = 0; t < channels; t++) {
				if (result[t] < 0)
					result[t] = 0;
				else if (result[t] > 255)
					result[t] = 255;
			}
			//
			if (channels == 1) {
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(result[0]);
			}
			else if (channels == 3) {
				Vec3b rgb;
				rgb[0] = static_cast<uchar>(result[0]);
				rgb[1] = static_cast<uchar>(result[1]);
				rgb[2] = static_cast<uchar>(result[2]);
				dst.at<Vec3b>(i - rowPadding, j - colPadding) = rgb;
			}
		}
	}
}

void comparedAdaptiveMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc) 
{
	//3*3 的自适应均值滤波处理椒盐噪声
	Mat dst1 = sapSrc.clone();
	adaptiveMeanBlur(sapSrc, dst1, 3, 3);
	imshow("3*3自适应均值滤波处理椒盐噪声结果", dst1);

	//5*5 的自适应均值滤波处理椒噪声
	Mat dst2 = pSrc.clone();
	adaptiveMeanBlur(pSrc, dst2, 3, 3);
	imshow("3*3自适应均值滤波处理椒噪声结果", dst2);

	//3*3 的自适应均值滤波处理盐噪声
	Mat dst3 = pSrc.clone();
	adaptiveMeanBlur(sSrc, dst3, 3, 3);
	imshow("3*3自适应均值滤波处理盐粒噪声结果", dst3);

	//3*3 的自适应均值滤波处理高斯噪声
	Mat dst4 = gSrc.clone();
	adaptiveMeanBlur(gSrc, dst3, 3, 3);
	imshow("3*3自适应均值滤波处理高斯噪声结果", dst4);
}

