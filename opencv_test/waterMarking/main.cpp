#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
/*
* �򵥵Ŀɼ�ˮӡ
* Ҫ����ӳߴ��ͼƬӦ�ô���ˮӡ
* F = (1-a)f + a*w
*/
void sampleImagesWaterMarking(Mat& src,Mat& waterMat,Mat& dst,double a) 
{
	int row = src.rows;
	int col = src.cols;

	int wr = waterMat.rows;
	int wc = waterMat.cols;
	dst = src.clone();
	for (int i = 0; i < wr; i++) 
	{
		for (int j = 0; j < wc; j++) 
		{
			Vec3b temp = waterMat.at<Vec3b>(i, j);
			dst.at<Vec3b>(row - wr + i, col - wc + j) = (1-a)*dst.at<Vec3b>(row - wr + i, col - wc + j)+ a*temp;
		}
	}
}

/*
*
*/
void iLSB(Mat& src, Mat& waterMat, Mat& dst, double a)
{
	int row = src.rows;
	int col = src.cols;

	int wr = waterMat.rows;
	int wc = waterMat.cols;
	dst = src.clone();
	for (int i = 0; i < wr; i++)
	{
		for (int j = 0; j < wc; j++)
		{
			Vec3b temp = waterMat.at<Vec3b>(i, j);
			dst.at<Vec3b>(row - wr + i, col - wc + j) = 4*(dst.at<Vec3b>(row - wr + i, col - wc + j)/4) + temp/64;
		}
	}
}
int main(int argc,char** argv) {

	Mat waterMat = imread("D:/images/chys.jpg", -1);
	Mat src = imread("D:/images/test.jpg", -1);
	imshow("input", src);
	imshow("waterMarking", waterMat);
	Mat dst;
	double a = 0.3;
	//��ˮӡ
	//sampleImagesWaterMarking(src,waterMat,dst,a);
	//LSB
	iLSB(src, waterMat, dst, a);
	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}