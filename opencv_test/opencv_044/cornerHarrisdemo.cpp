#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void cornerHarrisDemo(Mat& images);
void shitomasiDemo(Mat& images);
int main(int argc,char** argv) 
{
	Mat original = imread("D:/images/tri.jpg",-1);
	if (original.empty()) {
		cout<<"can`t open this ph"<<endl;
		exit(0);
	}
	namedWindow("input", WINDOW_FREERATIO);
	imshow("input",original);
	//cornerHarrisDemo(original);
	shitomasiDemo(original);
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

void shitomasiDemo(Mat& images) {
	Mat gray;
	cvtColor(images,gray,COLOR_BGR2GRAY);

	vector<Point2f> corners;
	double quiltyLevel = 0.01;
	goodFeaturesToTrack(gray,corners,3, quiltyLevel,10,Mat(),3,false,0.04);
	RNG rng(12345);
	for (int i = 0; i < corners.size(); i++) {
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		circle(images, corners[i], 2, Scalar(b, g, r), 2, 8);
	}
	namedWindow("GFTT",WINDOW_FREERATIO);
	imshow("GFTT",images);
}