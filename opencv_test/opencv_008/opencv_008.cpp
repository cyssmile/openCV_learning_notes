#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv) 
{
	namedWindow("basic_demo", WINDOW_FREERATIO);
	Mat canvas = Mat(Size(512, 512), CV_8UC3);
	canvas = Scalar(255, 255, 255);
	//line 函数 在画布上 直线 （画布  起点 终点 线的颜色 线条粗细 渲染方式） 
	line(canvas,Point(0,0),Point(512,512),Scalar(0,0,255),3,LINE_8);

	//矩形绘制   先画好矩形， 再放到画布上
	Rect rec(10, 10, 100, 200);  //前两个参数 左上角 高 宽
	rectangle(canvas,rec,Scalar(0, 255,0),2,LINE_4);

	//绘制圆 
	circle(canvas, Point(256, 256), 100, Scalar(255, 0, 0), -1, LINE_8);

	//绘制椭圆
	RotatedRect rrt;
	rrt.center = Point2f(256, 256);
	rrt.angle = 45;
	rrt.size = Size(100, 200);
	ellipse(canvas,rrt,Scalar(0, 255,255),-1,LINE_8);//当线条选项为 -1  就代表填充
	imshow("basic_demo", canvas);

	//绘制随机图形
	Mat images = Mat(Size(512, 512), CV_8UC3);
	RNG rng(12345);
	int x1 = rng.uniform(0, 256);
	int x2 = rng.uniform(0, 256);
	int r_radios = 0;
	namedWindow("circle_demo", WINDOW_FREERATIO);
	while (true)
	{
		x1 = rng.uniform(0, 256);
		x2 = rng.uniform(0, 256);
		r_radios = rng.uniform(0, 512);
		circle(images, Point(x1, x2), r_radios, 
			Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)),
			1, LINE_8);
		imshow("circle_demo", images);
		int c = waitKey(10);
		if (c == 27) 
		{
			break;
		}
	}
	waitKey(0);
	destroyAllWindows(); 
	return 0;
}