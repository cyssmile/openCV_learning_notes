#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

void contours_info(Mat& source, vector<vector<Point>>& contours, int mod);
void contours_approxPolyDP_demo(Mat &images);
void fitEclipseDemo(Mat& images,Mat& canvas);
int main(int argc, char** arrgv)
{
	Mat source1 = imread("D:/images/test11.jpg", IMREAD_COLOR);

	if (source1.empty())
	{
		cout << "can`t open this ph" << endl;
		return -1;
	} 
	imshow("source1", source1);
	contours_approxPolyDP_demo(source1);
	imshow("images_demo",source1);
	//ÍÖÔ²ÂÖÀªÄâºÏ
	Mat source2 = imread("D:/images/ellpise.jpg",-1);
	if (source2.empty()) 
	{
		cout<<" not find this source "<<endl;
		return -1;
	}
	imshow("source2",source2);
	Mat canvas;
	fitEclipseDemo(source2,canvas);
	imshow("fiteclipse",canvas);
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
	//imshow("two_Valued", twoValued);
	//find contours
	vector<Vec4i> hirearchy;
	findContours(twoValued, contours, hirearchy, mod, CHAIN_APPROX_SIMPLE, Point());
}
void contours_approxPolyDP_demo(Mat &images) 
{
	/*
	* ÂÖÀª±Æ½ü
	*/
	vector<vector<Point>> contours;
	contours_info(images,contours,RETR_EXTERNAL);
	for (size_t i =0;i<contours.size();i++) 
	{
		Mat result;
		approxPolyDP(contours[i],result,4,true);
		

		Moments mm = moments(contours[i]);
		double cx = mm.m10 / mm.m00;
		double cy = mm.m01 / mm.m00;
		double area = contourArea(contours[i],false);
		cout << "corner:" << result.cols << " " << "Point:" << result.rows <<" "<<"area"<<area<<endl;
		circle(images,Point(cx,cy),2,Scalar(0,0,255),1,8);
		if (result.rows == 4) 
		{
			putText(images,"rectangle",Point(cx,cy-10),FONT_HERSHEY_PLAIN,1.0,Scalar(0,0,255),1,8);
		}
		if (result.rows == 3)
		{
			putText(images, "tritangle", Point(cx, cy - 10), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 0, 255), 1, 8);
		}
		if (result.rows >=5 && result.rows <= 12)
		{
			putText(images, "poly", Point(cx, cy - 10), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 0, 255), 1, 8);
		}
		if (result.rows >= 13)
		{
			putText(images, "circle", Point(cx, cy - 10), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 0, 255), 1, 8);
		}
		
	}
}

void fitEclipseDemo(Mat& images, Mat& canvas)
{
	vector<vector<Point>> contours;
	contours_info(images, contours, RETR_EXTERNAL);

	canvas = Mat::zeros(images.size(),images.type());
	canvas = Scalar::all(255);
	//ÄâºÏÍÖÔ²
	for (size_t i=0;i<contours.size();i++) 
	{
		RotatedRect rrt = fitEllipse(contours[i]);
		cout << rrt.size.width << " " << rrt.size.height << " " << rrt.center << endl;
		ellipse(canvas,rrt,Scalar(0,0,255),1,8);
		circle(canvas,rrt.center,2,Scalar(0,0,255),1,8);
	}
}