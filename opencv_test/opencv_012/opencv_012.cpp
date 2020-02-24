#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv;
using namespace std;

void Show_Hist_chart(Mat &canvas, Mat b_calc_h, Scalar sca, int thikness);
int main(int argc, char** argv)
{
	Mat src = imread("D:/images/beauty.jpg", -1);
	namedWindow("source_demo", WINDOW_FREERATIO);
	if (src.empty())
	{
		printf("can`t open this ph\n");
	}
	imshow("source_demo", src);
	//做一个直方图统计
	vector<Mat> split_src;
	split(src, split_src);//先将src Mat 按照 b g r 分隔
	//这里调用cv的 直方图统计的api
	float range[] = { 0, 256 };
	const float *histRange = { range };
	//cout << histRange[1] << endl;
	Mat b_calc_h, g_calc_h, r_calc_h;
	int histSize = 256;
	//统计b通道的像素信息
	calcHist(&split_src[0], 1, 0, Mat(), b_calc_h,
		1, &histSize, &histRange, true, false);
	/*
	calcHist(&split_src[1], 1, 0, Mat(), g_calc_h,
		1, &histSize, &histRange, true, false);
	calcHist(&split_src[2], 1, 0, Mat(), r_calc_h,
		1, &histSize, &histRange, true, false);
		*/
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	canvas = Scalar(255, 255, 255);
	Show_Hist_chart(canvas, b_calc_h, (0, 255, 0), 1);
	
	equalizeHist(split_src[0], split_src[0]);//直方图均衡化

	calcHist(&split_src[0], 1, 0, Mat(), b_calc_h,
		1, &histSize, &histRange, true, false);
	
	Show_Hist_chart(canvas, b_calc_h, (0, 255, 255), 1);
	
	imshow("source_demo", canvas);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
void Show_Hist_chart(Mat &canvas,Mat b_calc_h,Scalar sca, int thikness) 
{
	int canvas_height = canvas.rows;
	int canvas_step = canvas.cols / b_calc_h.rows;
	normalize(b_calc_h, b_calc_h, 0, canvas_height, NORM_MINMAX, -1, Mat());
	// 将通过calcHist 得到的统计直方图进行归一化 0 到512 之间
	for (int i = 0; i < b_calc_h.rows - 1; i++)
	{
		line(canvas, Point(i * canvas_step, canvas_height - b_calc_h.at<float>(i, 0)),
			Point((i + 1) * canvas_step, canvas_height - b_calc_h.at<float>(i + 1, 0)),
			sca, thikness, 8);
	}
}