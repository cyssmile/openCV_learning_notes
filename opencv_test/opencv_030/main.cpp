#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc,char** arrgv) 
{
	Mat source = imread("D:/images/test.jpg",IMREAD_GRAYSCALE);
	if (source.empty()) 
	{
		cout << "can`t open this ph" << endl;
	}
	imshow("source",source);
	source.convertTo(source,CV_32FC1,1.0/255.0);
	Mat sourceComplex[2] = {source,Mat::zeros(source.size(),CV_32F)};
	Mat dftReady;
	merge(sourceComplex, 2, dftReady);
	dft(dftReady,dftReady,DFT_COMPLEX_OUTPUT);
	Mat dst;
	dft(dftReady, dst, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
	imshow("invertDft", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}