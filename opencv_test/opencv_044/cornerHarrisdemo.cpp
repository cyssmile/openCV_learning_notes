#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void cornerHarrisDemo(Mat& images);
int main(int argc,char** argv) 
{
	Mat original = imread("D:/images/tri.jpg",-1);
	if (original.empty()) {
		cout<<"can`t open this ph"<<endl;
		exit(0);
	}
	namedWindow("input", WINDOW_FREERATIO);
	imshow("input",original);
	cornerHarrisDemo(original);

	waitKey(0);
	destroyAllWindows();
	return 0;
}

void cornerHarrisDemo(Mat& images) {
	Mat gray, dst;
	cvtColor(images, gray, COLOR_BGR2GRAY);

	double k = 0.04;
	int blocksize = 2;
	int ksize = 3;
	cornerHarris(gray,dst,blocksize,ksize,k);

	Mat dst_norm = Mat::zeros(dst.size(),dst.type());
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, -1, Mat());
	convertScaleAbs(dst_norm,dst_norm);

	for (int row = 0; row < images.rows; row++) {
		for (int col = 0; col < images.cols;col++) {
			int sp = dst_norm.at<uchar>(row, col);
			if (sp > 182) {
				circle(images, Point(col, row), 3, Scalar(0, 0, 255), 2, 8);
			}
		}
	}

	namedWindow("dst",WINDOW_FREERATIO);
	imshow("dst", images);

}