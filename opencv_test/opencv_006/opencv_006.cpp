#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv) 
{
	//ͼ���λ����
	Mat src = imread("D:/opencv/sources/samples/data/fruits.jpg", -1);
	if (src.empty()) 
	{
		cout << "��ͼƬʧ��" << endl;
	}
	namedWindow("src_demo", WINDOW_FREERATIO);
	imshow("src_demo", src);

	//ͼ��ȡ��
	Mat dst1;
	bitwise_not(src, dst1, Mat());
	//ͼ��ȡ�� ��һ��������ԭͼ�� �ڶ����������ͼ�� ��������mask
	//ͼ��ȡ�� �൱�� 255 ��ȥԭ����ֵ
	//src.at<Vec3b>(row,col)[0] = 255 - src.at<Vec3b>(row, col);
	//Mat mask = MaT::zears(src.size(),CV_8UC1);
	imshow("bitwise_not", dst1);

	//ͼ��ȡ��
	//mask����Ҫ��С��srcԭͼƬ��ͬ����ͨ�������ȥ����maskֵΪ0����Ϊ��ɫ
	//������㣬ȫ1������255��������ȡ��
	Mat dst3;
	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	/**
	����ͨ��mask��ʵ��ROI����ѡ����ֻ��Ҫ������ͬ��С����ͨ����ȫ���mask
	��ROI�����ֵ��Ϊ255��������ȡ��������ʱ��Ϊ255�����򽫻�ȫ��ȡ��
	**/
	int hieght = mask.rows;
	int width = mask.cols;
	for (int hi = 0; hi < hieght / 2; hi++) 
	{
		for (int wi = 0; wi < width / 2; wi++) 
		{
			mask.at<uchar>(hi, wi) = 255;
		}
	}
	bitwise_not(src, dst3, mask);
	imshow("bitwise_not_mask", dst3);
	/*
	bitwise_and ���ĸ����� ��һԭͼ �ڶ�����ʲôͼƬ���룬 ���������Mat ���ĸ�mask
	*/
	Mat dst2;
	//bitwise_and(src, src, dst2, Mat());//ԭͼ�����ԭͼ
	bitwise_and(src, src, dst2, mask);
	imshow("bitwise_and", dst2);
	

	//bitwise_or ����� ��1 ����1
	Mat dst4;
	Mat mask2 = Mat::zeros(src.size(), src.type());
	//ROI ����
	int hieght2 = mask2.rows;
	int width2 = mask2.cols;
	for (int hi = 0; hi < hieght2 / 2; hi++)
	{
		for (int wi = 0; wi < width2 / 2; wi++)
		{
			mask.at<uchar>(hi, wi) = 127;
		}
	}

	bitwise_or(src, mask2,dst4, mask);
	imshow("bitwise_or", dst4);

	waitKey(0);
	destroyAllWindows();
	return 0;
}