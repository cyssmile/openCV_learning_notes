#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char **argv) 
{
	Mat src = imread("D:/images/cat.jpg",-1);
	if (src.empty()) 
	{
		cout << " can`t open this ph" << endl;
	}
	imshow("src_demo", src);

	Mat dst;
	GaussianBlur(src,dst,Size(5,5),0);
	imshow("GaussianBlur_demo",dst);
	//Size ��sigmaX ֻ��Ҫ����һ���ͺ���,SizeӦΪ����*����
	//GaussianBlur(src, dst, Size(0, 0), 15);//������sigmaX������������sigmaX���SIze
	// Ĭ��sigmaY =0
	/*
	*
	* ����ģ�� ����ģ����Ϊx ��y ����
	*/
	Mat box_dst;
	boxFilter(src, box_dst, -1, Size(12, 3), Point(-1, -1), true, BORDER_DEFAULT);
	//ͨ���� -1 ��ʾĬ�Ϸ��� ê����Ϊ��-1��-1��
	imshow("box_dst_win",box_dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}