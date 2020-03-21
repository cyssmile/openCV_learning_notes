#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void CCL_withStatus(Mat &images);
int main(int argc, char** crgv)
{
	Mat src = imread("D:/images/coin.jpg", -1);
	if (src.empty())
	{
		cout << "can`t open this ph" << endl;
	}
	GaussianBlur(src, src, Size(3, 3), 0);
	imshow("input", src);

	CCL_withStatus(src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
void CCL_withStatus(Mat &images)
{
	Mat gray;
	cvtColor(images, gray, COLOR_BGR2GRAY);
	imshow("gray_demo", gray);
	Mat dst;
	threshold(gray, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);
	//adaptiveThreshold(gray, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 3);
	bitwise_not(dst, dst, Mat());
	imshow("OTSU", dst);
	Mat labels = Mat::zeros(dst.size(), CV_32S);
	Mat stats, centroid;
	int number_labels = connectedComponentsWithStats(dst, labels, stats, centroid, 8, CV_32S, CCL_DEFAULT);
	/*
	* lables 记录着dst的每个像素点属于哪个类别
	*/
	/*
	*设置填充色
	*/
	RNG rng(12345);
	vector<Vec3b> colorTable(number_labels);
	colorTable[0] = Vec3b(0, 0, 0); //背景色
	for (int i =1;i<number_labels;i++) 
	{
		colorTable[i] = Vec3b(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
	}

	/*
	* 对原图填色
	*/
	
	Mat result = Mat::zeros(images.size(), images.type());
	for (int h =0;h<result.rows;h++) 
	{
		for (int w=0;w<result.cols;w++) 
		{
			int label = labels.at<int>(h, w);
			result.at<Vec3b>(h, w) = colorTable[label];
		}
	}
	/*
	* 在图片中记录有几个区域
	*/
	putText(result,format("label:%d",number_labels-1),Point(10,10),FONT_HERSHEY_PLAIN,1.0,Scalar(0,0,255),
							1,8,false);
	/*
	* 画出每个类别的边框
	*/
	for (int i = 1; i < number_labels; i++) 
	{
		// 每个label的中心
		int cx = centroid.at<double>(i, 0);
		int cy = centroid.at<double>(i, 1);
		circle(result, Point(cx, cy), 2, colorTable[i], 1, 8, 0);
		//外接矩形
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);
		Rect rec(x, y, width, height);
		rectangle(result,rec,Scalar(255,255,255),1,8,0);
		putText(result, format("label:%d", i), Point(x, y), FONT_HERSHEY_PLAIN, 1.0, colorTable[i],
			1, 8, false);
	}
	imshow("total_color", result);

}