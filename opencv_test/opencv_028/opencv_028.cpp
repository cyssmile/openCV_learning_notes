#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc,char** argv) 
{
	//Mat original = imread("D:/images/test.jpg",IMREAD_GRAYSCALE);
	Mat original = imread("D:/opencv/sources/samples/data/lena.jpg", IMREAD_GRAYSCALE);
	namedWindow("input",WINDOW_FREERATIO);
	imshow("input",original);
	// get optimal DFT size
	int h = getOptimalDFTSize(original.rows);
	int w = getOptimalDFTSize(original.cols);
	
	//
	copyMakeBorder(original, original, 0, h-original.rows, 0, w - original.cols, BORDER_DEFAULT);
	//copyMakeBorder(original, original, 0, h - original.rows, 0, w - original.cols, BORDER_CONSTANT, Scalar::all(0));
	// CV_8UC1 to CV_32FC1
	Mat originalFloat;
	//original.convertTo(originalFloat,CV_32FC1,1.0/255.0);
	original.convertTo(originalFloat, CV_32FC1, 1.0);
	// ready dft data complex;

	Mat originalComplex[2]={originalFloat,Mat::zeros(originalFloat.size(),CV_32F)};
	Mat dftOriginal;
	merge(originalComplex, 2, dftOriginal);

	// dft
	Mat dftAfter;
	//dft(dftOriginal,dftAfter,DFT_COMPLEX_OUTPUT);
	dft(dftOriginal, dftAfter);
	// C = R + jI  , R = originalComplex[0], I = originalComplex[1] 
	split(dftAfter, originalComplex);

	//Euler distance |C| = sqart(R^2 +I^2)
	magnitude(originalComplex[0], originalComplex[0], originalComplex[1]);
	
	//log(1 + sqart(R^2 +I^2))
	Mat logReady = originalComplex[0];
	logReady += Scalar::all(1);
	log(logReady, logReady);
	// spectrum  Tailoring   to Even
	logReady = logReady(Rect(0,0,logReady.cols & -2,logReady.rows & -2));

	//draw spectrum
	int cx = logReady.cols / 2;
	int cy = logReady.rows / 2;

	Mat q0(logReady, Rect(0, 0, cx, cy));       
	Mat q1(logReady, Rect(cx, 0, cx, cy));    
	Mat q2(logReady, Rect(0, cy, cx, cy));     
	Mat q3(logReady, Rect(cx, cy, cx, cy));     

	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	normalize(logReady, logReady, 0, 1, NORM_MINMAX);
	
	namedWindow("spectrum", WINDOW_FREERATIO);
	imshow("spectrum",logReady);
	waitKey(0);
	destroyAllWindows();
	return 0;
}