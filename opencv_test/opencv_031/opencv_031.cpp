#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

void contours_info(Mat& source,vector<vector<Point>>& contours,int mod);
void compareContours(Mat& images1, Mat& images2 );
int main(int argc, char** arrgv)
{
	Mat source1 = imread("D:/images/ACE.jpg", IMREAD_COLOR);
	Mat source2 = imread("D:/images/C.jpg", IMREAD_COLOR);
	if (source1.empty() || source2.empty())
	{
		cout << "can`t open this ph" << endl;
		return -1;
	}
	imshow("source1", source1);
	imshow("source2", source2);
	compareContours(source1, source2);
	imshow("compare_s1_s2", source1);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
void contours_info(Mat& source, vector<vector<Point>>& contours, int mod)
{
	//two valued 
	GaussianBlur(source, source, Size(3, 3), 0);
	Mat gray;
	cvtColor(source, gray, COLOR_BGRA2GRAY);
	Mat twoValued;
	threshold(gray, twoValued, 0, 255, THRESH_BINARY | THRESH_OTSU);
	bitwise_not(twoValued, twoValued);
	//find contours
	vector<Vec4i> hirearchy;
	findContours(twoValued, contours, hirearchy, mod, CHAIN_APPROX_SIMPLE, Point());
}
void compareContours(Mat& images1, Mat& images2) 
{
	vector<vector<Point>> contours1;
	vector<vector<Point>> contours2;
	contours_info(images1, contours1,RETR_TREE);
	contours_info(images2, contours2, RETR_EXTERNAL);
	cout << "图1中有："<<contours1.size()<<"个轮廓"<<endl;
	Moments mm2;
	mm2 = moments(contours2[0]);
	Mat humm2;
	HuMoments(mm2,humm2);

	//在轮廓A集合中匹配轮廓B
	for (int i =0;i<contours1.size();i++) 
	{
		Moments mm1 = moments(contours1[i]);
		Mat hum1;
		HuMoments(mm1, hum1);
		double dist = matchShapes(hum1,humm2,CONTOURS_MATCH_I1,0);
		//double dist = matchShapes(hum1, humm2, CONTOURS_MATCH_I2, 0);
		//double dist = matchShapes(hum1, humm2, CONTOURS_MATCH_I3, 0);
		if (dist < 1) 
		{
			cout << "第" << i << "轮廓与图2的最大轮廓相似" << " " << "相似度dist=" << dist << endl;
			drawContours(images1,contours1,i,Scalar(0,0,255),2,8);
			/*
			double cx = mm1.m10 / mm1.m00; //当前轮廓的中心(x,y)
			double cy = mm1.m01 / mm1.m00;
			circle(images1, Point(cx, cy), 3, Scalar(0, 0, 0), 3, 8);
			*/
		}
	}
}