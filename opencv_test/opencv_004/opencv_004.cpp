#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv) 
{
	Mat src = imread("D:/images/dog.jpg", IMREAD_COLOR);
	namedWindow("src_wind", WINDOW_FREERATIO);
	imshow("src_wind", src);
	Mat t1 = src.clone();
	int height = t1.rows;
	int width = t1.cols;
	int ch = t1.channels();

	//��������  ��������ָ��ķ�ʽ
	//mat.at<��������>��x, y��
	for (int row = 0; row<height; row++) 
	{
		for (int col = 0; col < width; col++) 
		{	
			//����ͨ����������Ӧ�Ĳ���
			if (ch == 3) 
			{
				Vec3b pixel = t1.at<Vec3b>(row, col);
				int blue = pixel[0];
				int green = pixel[1];
				int red = pixel[2];
				t1.at<Vec3b>(row, col)[0] = 255 - blue;
				t1.at<Vec3b>(row, col)[1] = 255 - green;
				t1.at<Vec3b>(row, col)[2] = 255 - red;
			}
			//��ͨ��
			if (ch == 1)
			{
				int pv = t1.at<uchar>(row, col);
				t1.at<uchar>(row, col) = 255 - pv;
			}
		}
	}
	//չʾ������ͼƬ
	namedWindow("t1_wind", WINDOW_FREERATIO);
	imshow("t1_wind", t1);
	waitKey(0);
	destroyAllWindows();
	return 0;
}