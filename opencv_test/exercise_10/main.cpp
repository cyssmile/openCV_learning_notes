#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>
using namespace std;
using namespace cv;


void paddingPQ(Mat& src, Mat& dst);
void takeDFT(Mat& source, Mat& destination);
void showDFT(Mat& source);
void changeQuadrant(Mat& source);
void make_ILPE_filter(int width, int height, double D0, Mat& dst);
void make_IHPE_filter(int width, int height, double D0, Mat& dst);
void make_BHPF_filter(int width, int height, double D0, double n, Mat& dst);
void iILPF(Mat& src, Mat& dst,double D0);
void iHLPF(Mat& src, Mat& dst, double D1);
void iBHPF(Mat& src, Mat& dst, double D1, double n);

int main(int argc, char** argv)
{
	Mat original = imread("D:/images/panda.jpg", IMREAD_GRAYSCALE);
	if (original.empty())
	{
		cout << "can`t open this ph" << endl;
	}
	namedWindow("input", WINDOW_FREERATIO);
	imshow("input", original);
	//填充
	namedWindow("padding", WINDOW_AUTOSIZE);
	Mat padSrc;
	paddingPQ(original, padSrc);
	imshow("padding", padSrc);

	Mat destination;
	takeDFT(original, destination);

	//低通滤波ILPF
	/*
	Mat dst;
	double D0 = 30;
	iILPF(destination,dst,D0);
	*/


	// 理想高通滤波器
	/*
	Mat dst1;
	double D1 = 30;
	iHLPF(destination, dst1, D1);
	*/

	//布特沃斯高通滤波器
	Mat dst2;
	int n = 2;
	double D2 = 30;
	iBHPF(destination, dst2, D2, n);
	//showDFT(destination);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void takeDFT(Mat& source, Mat& destination)
{
	// CV_8UC1 to CV_32FC1
	Mat originalFloat;
	source.convertTo(originalFloat, CV_32FC1, 1.0 / 255.0);
	// ready dft data complex;
	Mat originalComplex[2] = { originalFloat,Mat::zeros(originalFloat.size(),CV_32F) };
	Mat dftOriginal;
	merge(originalComplex, 2, dftOriginal);
	dft(dftOriginal, destination, DFT_COMPLEX_OUTPUT);
}
void showDFT(Mat& source)
{
	Mat sourceComplex[2];
	split(source, sourceComplex);
	Mat logReady;
	magnitude(sourceComplex[0], sourceComplex[1], logReady);
	logReady += Scalar::all(1);
	log(logReady, logReady);
	changeQuadrant(logReady);
	normalize(logReady, logReady, 0, 1, NORM_MINMAX);
	namedWindow("spectrum", WINDOW_FREERATIO);
	imshow("spectrum", logReady);
}
void changeQuadrant(Mat& source)
{
	//draw spectrum
	int cx = source.cols / 2;
	int cy = source.rows / 2;

	Mat q0(source, Rect(0, 0, cx, cy));
	Mat q1(source, Rect(cx, 0, cx, cy));
	Mat q2(source, Rect(0, cy, cx, cy));
	Mat q3(source, Rect(cx, cy, cx, cy));

	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

void paddingPQ(Mat& src, Mat& dst)
{
	//要求输入一张单通道图片
	//输入图像f(x,y) 通常P=2M Q=2N 这里填充为常量0
	int M = src.rows;//高
	int N = src.cols;//宽
	cout << "M N" << M << " " << N << endl;
	dst = Mat::zeros(Size(2 * N, 2 * M), CV_8UC1);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			dst.at<uchar>(i, j) = src.at<uchar>(i, j);
		}
	}
}

void make_ILPE_filter(int width, int height, double D0,Mat& dst) 
{
	dst = Mat::zeros(Size(width, height), CV_32F);
	double D0_2 = pow(D0, 2);
	double half_h = height * (1.0) / 2;
	double half_w = width * (1.0) / 2;
	//创建理想低通滤波器
	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width; j++) 
		{
			double distance = pow((half_h - (double)i), 2) + pow((half_w - (double)j), 2);
			if (less<double>()(distance,D0_2)) {
				dst.at<float>(i, j) = 1;
			}
		}
	}
}

void iILPF(Mat& src, Mat& dst, double D0)
{
	//这里输入的src是刚通过DFT处理后的Mat 并没有进行其他的处理
	//先将低频高亮部分移到中间
	changeQuadrant(src);

	//Mat sourceComplex[2];
	//split(src, sourceComplex);

	//创建低通滤波器
	Mat ifilter;
	make_ILPE_filter(src.cols, src.rows, D0, ifilter);


	Mat sourceComplex[2];
	split(src, sourceComplex);

	Mat temp[2];
	multiply(sourceComplex[0], ifilter, temp[0]);
	multiply(sourceComplex[1], ifilter, temp[1]);

	Mat idft;
	merge(temp, 2, idft);
	//转换回相应的象限
	changeQuadrant(idft);

	dft(idft, dst, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
	imshow("理想低通滤波", dst);
}

void make_IHPE_filter(int width, int height, double D0, Mat& dst)
{
	dst = Mat::ones(Size(width, height), CV_32F);
	double D0_2 = pow(D0, 2);
	double half_h = height * (1.0) / 2;
	double half_w = width * (1.0) / 2;
	//创建理想高通滤波器
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double distance = pow((half_h - (double)i), 2) + pow((half_w - (double)j), 2);
			if (less<double>()(distance, D0_2)) {
				dst.at<float>(i, j) = 0;
			}
		}
	}
}

void iHLPF(Mat& src, Mat& dst, double D1)
{
	//这里输入的src是刚通过DFT处理后的Mat 并没有进行其他的处理
	//先将低频高亮部分移到中间
	changeQuadrant(src);
	Mat ifilter;
	make_IHPE_filter(src.cols, src.rows, D1, ifilter);


	Mat sourceComplex[2];
	split(src, sourceComplex);

	Mat temp[2];
	multiply(sourceComplex[0], ifilter, temp[0]);
	multiply(sourceComplex[1], ifilter, temp[1]);

	Mat idft;
	merge(temp, 2, idft);
	//转换回相应的象限
	changeQuadrant(idft);

	dft(idft, dst, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
	imshow("理想高通滤波", dst);
}

void make_BHPF_filter(int width, int height, double D0,double n, Mat& dst)
{
	dst = Mat::ones(Size(width, height), CV_32F);
	double D0_2 = pow(D0, 2);
	double half_h = height * (1.0) / 2;
	double half_w = width * (1.0) / 2;
	//创建理想高通滤波器
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double distance = pow((half_h - (double)i), 2) + pow((half_w - (double)j), 2);
			double temp = pow(D0 / sqrt(distance), 2 * n);
			dst.at<float>(i, j) = 1.0 / (1.0 + temp);
		}
	}
}

void iBHPF(Mat& src, Mat& dst, double D1,double n) 
{
	//这里输入的src是刚通过DFT处理后的Mat 并没有进行其他的处理
	//先将低频高亮部分移到中间
	changeQuadrant(src);
	Mat ifilter;
	make_BHPF_filter(src.cols, src.rows, D1,n, ifilter);

	Mat sourceComplex[2];
	split(src, sourceComplex);

	Mat temp[2];
	multiply(sourceComplex[0], ifilter, temp[0]);
	multiply(sourceComplex[1], ifilter, temp[1]);

	Mat idft;
	merge(temp, 2, idft);
	//转换回相应的象限
	changeQuadrant(idft);

	dft(idft, dst, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
	imshow("布特沃斯高通滤波", dst);
}