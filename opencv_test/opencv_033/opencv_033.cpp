#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

void drawRandomLine(Mat& canvas, Size size, int type, int NumberOfLine);
void toTwoValued(Mat& images,Mat& destination);
void HoughLines_Demo(Mat& images);
void HoughLinesP_Demo(Mat& images);
int main(int argc, char** arrgv)
{
	Mat orignal = imread("D:/images/lines.jpg", -1);
	imshow("orignal_demo", orignal);
	/*
	* 霍夫直线检测
	* HoughLines_Demo(orignal);
	*/

	Mat randLines;
	drawRandomLine(randLines,Size(512,512),CV_8UC3,6);
	HoughLinesP_Demo(randLines);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
void drawRandomLine(Mat& canvas,Size size,int type,int NumberOfLine) 
{
	canvas = Mat::zeros(size,type);
	RNG rng(12345);
	for (int i = 0; i < NumberOfLine; i++) 
	{
		line(canvas, Point(rng.uniform(0, size.width), rng.uniform(0, size.height)),
			Point(rng.uniform(0, size.width), rng.uniform(0, size.height)),
			Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)),
			1, 8, 0);
	}
}

void toTwoValued(Mat& images, Mat& destination) 
{
	cvtColor(images,destination,COLOR_BGR2GRAY);
	threshold(destination, destination, 0, 255, THRESH_BINARY | THRESH_OTSU);
	bitwise_not(destination, destination);
	//imshow("two_valued", destination);
}

void HoughLines_Demo(Mat& images) 
{
	/*
	Mat images;
	drawRandomLine(images,Size(512,512),CV_8UC3,4);
	*/
	if (images.empty()) 
	{
		cout << "can`t open this ph" << endl;
		return ;
	}

	Mat binary;
	toTwoValued(images, binary);
	//霍夫直线检测
	vector<Vec3f> lines;
	HoughLines(binary, lines, 1, CV_PI / 180.0, 100, 0, 0);

	//将极坐标转换成笛卡尔坐标，绘制
	Point pt1, pt2;
	for (size_t t = 0; t < lines.size(); t++)
	{
		float rth = lines[t][0]; //距离
		float theta = lines[t][1];//角度
		float acc = lines[t][2];//累加值
		cout << "r: " << rth << " theta:" << theta << " acc:" << acc << endl;
		double b = sin(theta);
		double a = cos(theta);
		double x0 = a * rth;
		double y0 = b * rth;


		pt1.x = cvRound(x0 + 512 * (-b));
		pt1.y = cvRound(y0 + 512 * (a));
		pt2.x = cvRound(x0 - 512 * (-b));
		pt2.y = cvRound(y0 - 512 * (a));

		int angle = cvRound((theta/CV_PI)*180);
		if (rth>0) 
		{
			line(images, pt1, pt2, Scalar(255, 255, 0), 1, 8);
			if (angle == 90) 
			{
				line(images, pt1, pt2, Scalar(0,255, 255), 1, 8);
			}
			if (angle < 1) 
			{
				line(images, pt1, pt2, Scalar(255, 0, 255), 1, 8);
			}
		}else 
		{
			line(images, pt1, pt2, Scalar(255, 0, 0), 1, 8);
		}
		
	}
	imshow("houghline", images);
}

void HoughLinesP_Demo(Mat& images) 
{
	Mat binary;
	Canny(images,binary,50,100,3,false);
	imshow("canny_demo",binary);
	vector<Vec4i> lines;
	Mat canvas = Mat::zeros(images.size(), images.type());
	HoughLinesP(binary,lines,1,CV_PI/180.0,50,20,10);
	cout << lines.size() << endl;
	for (size_t t =0;t<lines.size();t++) 
	{
		line(canvas,Point(lines[t][0],lines[t][1]), Point(lines[t][2], lines[t][3]),Scalar(0,0,255),2,8);
	}
	imshow("canvas", canvas);
}