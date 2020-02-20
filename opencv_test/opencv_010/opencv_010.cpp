#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv;
using namespace std;
int main(int argc, char ** argv) 
{
	Mat src = imread("D:/images/beauty.jpg", -1);
	if (src.empty()) 
	{
		printf("can`t open this ph\n");
	}
	namedWindow("src_demo", WINDOW_FREERATIO);
	imshow("src_demo", src);
	// ͨ���ķ���
	vector<Mat> src_mat;
	split(src, src_mat);

	//չʾ����ͨ��
	namedWindow("blue_channels", WINDOW_FREERATIO);
	imshow("blue_channels", src_mat[0]);
	imwrite("D:/images/blue_channels.jpg", src_mat[0]);

	namedWindow("green_channels", WINDOW_FREERATIO);
	imshow("green_channels", src_mat[1]);
	imwrite("D:/images/green_channels.jpg", src_mat[1]);

	namedWindow("red_channels", WINDOW_FREERATIO);
	imshow("red_channels", src_mat[2]);
	imwrite("D:/images/red_channels.jpg", src_mat[2]);

	//�ı�ĳ��ͨ����ʹ��ͨ����ɫȱʧ
	//src_mat[0] = Scalar(255);  //bͨ��255
	//src_mat[1] = Scalar(255); //gͨ��255
	//src_mat[2] = Scalar(255); //rͨ��255
	//src_mat[0] = Scalar(0);  //bͨ��0
	src_mat[1] = Scalar(0); //gͨ��0
	//src_mat[2] = Scalar(0); //rͨ��0
	merge(src_mat, src);
	namedWindow("merge_dst",WINDOW_FREERATIO);
	imshow("merge_dst", src);
	imwrite("D:/images/merge_src_green_0.jpg", src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}