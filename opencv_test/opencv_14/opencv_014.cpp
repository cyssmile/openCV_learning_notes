#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) 
{
	/* 
	*  ͼ��ľ�ֵ���  һ�ִ����  һ�ֵ���api
	*/
	Mat src = imread("D:/images/dog.jpg",-1);
	namedWindow("src_win", WINDOW_FREERATIO);
	imshow("src_win", src);
	
	Mat result = src.clone();
	/*
	* ��ͳ����ʵ��3*3 �ľ�ֵ���
	*/
	int col = src.cols;
	int row = src.rows;
	for (int i =1;i<row-1;i++) 
	{
		for (int j=1;j<col-1;j++) 
		{
			int sb = src.at<Vec3b>(i - 1, j - 1)[0] + src.at<Vec3b>(i - 1, j)[0] + src.at<Vec3b>(i - 1, j + 1)[0]
				+ src.at<Vec3b>(i, j - 1)[0] + src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i, j + 1)[0]
				+ src.at<Vec3b>(i + 1,j - 1)[0] + src.at<Vec3b>(i+ 1, j)[0] + src.at<Vec3b>(i + 1, j + 1)[0];

			int sg = src.at<Vec3b>(i - 1, j - 1)[1] + src.at<Vec3b>(i - 1, j)[1] + src.at<Vec3b>(i - 1, j + 1)[1]
				+ src.at<Vec3b>(i, j - 1)[1] + src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i, j + 1)[1]
				+ src.at<Vec3b>(i + 1, j - 1)[1] + src.at<Vec3b>(i + 1, j)[1] + src.at<Vec3b>(i + 1, j+ 1)[1];
			
			int sr = src.at<Vec3b>(i - 1, j - 1)[2] + src.at<Vec3b>(i - 1, j)[2] + src.at<Vec3b>(i - 1, j + 1)[2]
				+ src.at<Vec3b>(i, j - 1)[2] + src.at<Vec3b>(i, j)[2] + src.at<Vec3b>(i, j + 1)[2]
				+ src.at<Vec3b>(i + 1, j - 1)[2] + src.at<Vec3b>(i + 1, j)[2] + src.at<Vec3b>(i + 1,j + 1)[2];
			
			result.at<Vec3b>(i,j)[0] = sb / 9;
			result.at<Vec3b>(i, j)[1] = sg / 9;
			result.at<Vec3b>(i, j)[2] = sr / 9;
		}
	}

	namedWindow("result_win",WINDOW_FREERATIO);
	imshow("result_win",result);

	/*
	* ����api
	*/
	Mat dst;
	blur(src,dst,Size(3,3),Point(1,1),BORDER_DEFAULT);

	/*
	* ��ͼƬ�ı�Ե�������
	*/
	Mat dst1;
	int board = 8;
	copyMakeBorder(src,dst1,board,board,board,board,BORDER_CONSTANT,Scalar(0,0,255));
	imshow("border_win", dst1);
	namedWindow("dst_win", WINDOW_FREERATIO);
	imshow("dst_win", dst);
	
	waitKey(0);
	destroyAllWindows();
	return 0;

}