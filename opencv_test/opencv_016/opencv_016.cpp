#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;
int main(int argc, char ** argv) 
{
	/*
	* ʹ��������˹��������ǿͼƬ
	*/
	Mat src_0 = imread("D:/images/moon.jpg",-1);
	if (src_0.empty()) 
	{
		cout << "can`t open this ph" << endl;
	}
	
	Mat src;
	GaussianBlur(src_0,src,Size(3,3),0,BORDER_DEFAULT);
	imshow("src_win", src);
	/*
	*������˹���Ӷ���
	*/
	//Mat Rok = (Mat_<int>(3,3)<<0,1,0,1,-4,1,0,1,0);
	Mat Rok = (Mat_<int>(3, 3) << -1,-1,-1,-1,8,-1,-1,-1,-1);
	Mat dst;
	/*
	* δ�궨������˹��ͼƬ
	*/
	filter2D(src,dst,CV_32F,Rok,Point(-1,-1),0,BORDER_DEFAULT);
	convertScaleAbs(dst, dst);//��ԭͼת����8bit

	/*
	* ����ע�ʹ����ǲ���ͨ�� convertScaleAbsת����ͼƬ�����ص�������Сֵ
	*/
	/*
	double min, max;
	Point minIndex, maxIndex;
	vector<Mat> split_dst(3);
	split(dst, split_dst);
	minMaxLoc(split_dst[2], &min, &max, &minIndex, &maxIndex);
	cout << min <<" "<<max<< endl;
	*/
	/*
	*��������˹ͼƬ�������и�
	*/
	imshow("dst_win",dst);

	/*
	* ���궨���������˹ͼƬ
	*/
	Mat calibration_dst;
	filter2D(src, calibration_dst, CV_32F, Rok, Point(-1, -1),20, BORDER_DEFAULT);
	convertScaleAbs(calibration_dst, calibration_dst);//��ԭͼת����8bit
	imshow("calibration_dst_win", calibration_dst);

	/*
	* ��ԭʼͼƬ��궨���ϸ��ͼƬ�ϳ�
	*/
	Mat merge_dst;
	add(src, calibration_dst,merge_dst,Mat(),-1);
	normalize(merge_dst, merge_dst,0,255,NORM_MINMAX,-1,Mat());
	imshow("merge_dst_win", merge_dst);

	waitKey(0);
	destroyAllWindows();
	return 0;
}