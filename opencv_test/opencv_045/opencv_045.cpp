#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;

void roiCardNumber(Mat&images);
int main(int argc, char **argv) 
{
	Mat src = imread("D:/images/ICBC.png",-1);
	if (src.empty()) {
		cout<<"can`t open this ph"<<endl;
		exit(0);
	}
	resize(src, src, Size(640, 400));
	namedWindow("input",WINDOW_FREERATIO);
	imshow("input",src);
	roiCardNumber(src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void roiCardNumber(Mat&images) 
{
	Mat gray;
	cvtColor(images, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);
	Mat binary;
	threshold(gray,binary,0,255,THRESH_BINARY_INV|THRESH_OTSU);
	imshow("binary",binary);

	Mat kernel = getStructuringElement(MORPH_RECT,Size(10,2),Point(-1,-1));
	Mat erode_dst;
	morphologyEx(binary,erode_dst,MORPH_OPEN,kernel,Point(-1,-1),2);
	erode(erode_dst, erode_dst, kernel, Point(-1, -1), 4);
	imshow("erode_dst", erode_dst);
	//find controus
	vector<vector<Point>> controus;
	findContours(erode_dst,controus,RETR_LIST,CHAIN_APPROX_SIMPLE,Point());

	vector<Rect> rets;
	rets.clear();
	for (size_t t = 0; t < controus.size(); t++) {
		Rect rec = boundingRect(controus.at(t));
		rets.push_back(rec);
	}
	namedWindow("cardNumber", WINDOW_FREERATIO);
	Mat roi;
	for (size_t t = 0; t < rets.size(); t++) {
		if (rets[t].width > rets[t].height * 10) {
			rectangle(images, rets[t], Scalar(0, 0, 255), 2, 8);
			roi = images(rets[t]).clone();
		}
	}
	imshow("images", images);
	imshow("cardNumber",roi);
	

}
