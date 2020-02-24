#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv) 
{
	Mat src1 = imread("D:/images/dog.jpg",-1);
	Mat src2 = imread("D:/images/cat.jpg", -1);
	if (src1.empty() || src2.empty()) 
	{
		printf("can't open those ph\n");
	}
	int channels[] = { 0,1,2 };
	Mat src_1_calc, src_2_calc;
	float c1[] = { 0,255 };
	float c2[] = {0,255};
	float c3[] = { 0,255 };
	const float * ranges[] = { c1,c2,c3 };
	int histSize[] = { 256,256,256 };
	calcHist(&src1,1,channels,Mat(),src_1_calc,3,histSize,ranges,true,false);
	calcHist(&src2, 1, channels, Mat(), src_2_calc, 3, histSize, ranges, true, false);

	//归一化
	normalize(src_1_calc,src_1_calc,0,1,NORM_MINMAX,-1,Mat());
	normalize(src_2_calc, src_2_calc, 0, 1, NORM_MINMAX, -1, Mat());
	

	//相关性
	double h11 = compareHist(src_1_calc,src_1_calc,HISTCMP_CORREL);
	double h12 = compareHist(src_1_calc, src_2_calc, HISTCMP_CORREL);
	printf("h11:%.2f h12:%.2f\n", h11, h12);
	
	// 巴氏距离
	double p11 = compareHist(src_1_calc, src_1_calc, HISTCMP_BHATTACHARYYA);
	double p12 = compareHist(src_1_calc, src_2_calc, HISTCMP_BHATTACHARYYA);
	printf("p11:%.2f p12:%.2f\n", p11, p12);


	imshow("dog_demo", src1);
	imshow("cat_demo", src2);
	waitKey(0);
	destroyAllWindows();
	return 0;
}