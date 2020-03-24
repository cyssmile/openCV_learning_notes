#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

/*
* Preprocessing and DFT 
* cyssmile
* 2020/03/24
*/
void takeDFT(Mat& source, Mat& destination);
/*
* show DFT
* cyssmile
* 2020/03/24
*/
void showDFT(Mat& source);
/*
* Quadrant change to make High frequency part in the middle
* cyssmile
* 2020/03/24
*/
void changeQuadrant(Mat& source);

int main(int argc, char** argv)
{
	Mat original = imread("D:/images/needDeal.jpg", IMREAD_GRAYSCALE);
	if (original.empty()) 
	{
		cout << "can`t open this ph" << endl;
	}
	namedWindow("input", WINDOW_FREERATIO);
	imshow("input", original);
	Mat destination;
	takeDFT(original,destination);
	showDFT(destination);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void takeDFT(Mat& source, Mat& destination) 
{
	int h = getOptimalDFTSize(source.rows);
	int w = getOptimalDFTSize(source.cols);
	copyMakeBorder(source, source, 0, h - source.rows, 0, w - source.cols, BORDER_DEFAULT);
	//copyMakeBorder(original, original, 0, h - original.rows, 0, w - original.cols, BORDER_CONSTANT, Scalar::all(0));
	// CV_8UC1 to CV_32FC1
	Mat originalFloat;
	//original.convertTo(originalFloat,CV_32FC1,1.0/255.0);
	source.convertTo(originalFloat, CV_32FC1, 1.0);

	// ready dft data complex;
	Mat originalComplex[2] = { originalFloat,Mat::zeros(originalFloat.size(),CV_32F) };
	Mat dftOriginal;
	merge(originalComplex, 2, dftOriginal);
	
	dft(dftOriginal, destination,DFT_COMPLEX_OUTPUT);
	// spectrum  Tailoring   to Even
	destination = destination(Rect(0, 0, destination.rows&-2, destination.cols&-2));
}
void showDFT(Mat& source) 
{
	Mat sourceComplex[2];
	split(source, sourceComplex);
	Mat logReady;
	magnitude(sourceComplex[0],sourceComplex[1], logReady);
	logReady += Scalar::all(1);
	log(logReady,logReady);
	changeQuadrant(logReady);
	normalize(logReady,logReady,0,1,NORM_MINMAX);
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