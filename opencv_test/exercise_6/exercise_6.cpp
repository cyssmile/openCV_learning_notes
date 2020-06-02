#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<iterator>
using namespace std;
using namespace cv;

/*
* 统计单通道的Mat中的像素信息， 信息保存在calVec中,calMat: 1*L 
* 要求 src CV_8UC1， LMax 为总共的灰度级别
*/
void calHistInfo(const Mat& src, vector<unsigned int>& calVec, vector<unsigned int >& calVecBefor,unsigned int LMax){
	int width = src.cols;
	int height = src.rows;
	int piexl = 0;
	for (int h = 0; h < height; h++) 
	{
		for (int w = 0; w < width; w++) {
			piexl = (int)src.at<uchar>(h, w);
			calVec[round(piexl)] += 1;
		}
	}
	
	calVecBefor[0] = calVec[0];
	for (int i = 1; i < calVec.size(); i++)
	{

		calVecBefor[i] = calVecBefor[i - 1] + calVec[i];
	}
	cout << "统计完毕" << endl;
}

/*
* 构建r 与s 之间的查询表
* s = r/MN * ∑r
*/
void createRSTable(const vector<unsigned int>& calVecBefor,
	unordered_map<unsigned int,unsigned int>& table_rs,unsigned int LMax)
{
	double total = (double)calVecBefor[LMax - 1];
	for (int i =0;i<LMax;i++) 
	{
		double s = LMax*(double)calVecBefor[i] * (1.0) / total;
		if (round(s) <= 255) {
			table_rs.insert(make_pair(i, round(s)));
		}
		else 
		{
			table_rs.insert(make_pair(i, 255));
		}
		
	}
}
/*
* 直方图均衡化
*/
void iHistImp(Mat& src, Mat&dst, unordered_map<unsigned int,unsigned int>& table_rs) {

	dst = Mat::zeros(src.size(), src.type());
	int width = src.cols;
	int height = src.rows;
	int piexl = 0;
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++) {
			piexl = (int)src.at<uchar>(h, w);

				auto it = table_rs.find(piexl);
				if (it != table_rs.end())
				{
					dst.at<uchar>(h, w) = it->second;
				}

		}
	}
}

/*
*  用折线图展示直方图均衡前 和直方图均衡后的像素分布差别
*/

void showHistChart(Mat& canvas,unsigned int LMax,vector<unsigned int> calVec,Scalar sca, int thikness)
{
//横轴是灰度级
//纵轴是像素的分布情况，我采取的方法是像素数目最多的为单位1
	int canvas_height = canvas.rows;
	int canvas_step = canvas.cols / LMax;
	auto it = max_element(calVec.begin(), calVec.end());
	unsigned int calMax = *it;

	//开始画折线图
	for (int i = 0; i < LMax-1; i++) 
	{
		line(canvas, Point(i * canvas_step, canvas_height - (canvas_height*(1.0)*calVec[i]/calMax)),
			Point((i + 1) * canvas_step, canvas_height - (canvas_height * (1.0) * calVec[i+1] / calMax)),
			sca, thikness, 8);
	}
}
/*
* 彩色图像的直方图均衡化
*/
void BGRHist(Mat& src, Mat& dst) 
{
	//将彩色图像的按照BGR三个通道切分
	vector<Mat> splitMat;
	split(src,splitMat);

	//分别对bgr 三个通道进行直方图均衡化
	vector<Mat> mergeMat;
	split(src, mergeMat);
	for (int i = 0; i < 3; i++) 
	{
		unsigned int LMax = 256;
		vector<unsigned int> calVec(LMax, 0);
		vector<unsigned int > calVecBefor(LMax, 0);//用于记录灰度级l之前的所以的像素点个数
		calHistInfo(splitMat[i], calVec, calVecBefor, LMax);
		//构建输入像素r 与输出像素s 之间的 一一映射表
		unordered_map<unsigned int, unsigned int > table_rs;
		createRSTable(calVecBefor, table_rs, LMax);
		iHistImp(splitMat[i],mergeMat[i], table_rs);
	}
	merge(mergeMat,dst);
}
int main(int argc, char** argv) {
	Mat src = imread("D:/images/hist.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cout << "erro" << endl;
		exit(0);
	}
	//统计输入图像中的像素信息
	unsigned int LMax = 256;
	vector<unsigned int> calVec(LMax, 0);
	vector<unsigned int > calVecBefor(LMax, 0);//用于记录灰度级l之前的所以的像素点个数
	calHistInfo(src, calVec, calVecBefor,LMax);
	
	//构建输入像素r 与输出像素s 之间的 一一映射表
	unordered_map<unsigned int, unsigned int > table_rs;
	createRSTable(calVecBefor,table_rs,LMax);

	//进行直方图均衡化
	Mat dst;
	iHistImp(src, dst, table_rs);
	

	//opencv 自带的直方图均衡， 比较自己实现的差别
	Mat dst1;
	equalizeHist(src, dst1);
	namedWindow("api_output", WINDOW_AUTOSIZE);
	imshow("api_output", dst1);
	
	//展示效果
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("output", WINDOW_AUTOSIZE);
	imshow("input", src);
	imshow("output",dst);

	//展示直方图均衡化前的折线图
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	canvas = Scalar(255, 255, 255);
	showHistChart(canvas,LMax,calVec,Scalar(0,0,255),2);
	namedWindow("canvas", WINDOW_FREERATIO);
	imshow("canvas",canvas);
	
	// 展示直方图均衡化后的折线图
	vector<unsigned int> calVec1(LMax, 0);
	vector<unsigned int > calVecBefor1(LMax, 0);//用于记录灰度级l之前的所以的像素点个数
	calHistInfo(dst, calVec1, calVecBefor1, LMax);
	Mat canvas1 = Mat::zeros(Size(512, 512), CV_8UC3);
	canvas1 = Scalar(255, 255, 255);
	showHistChart(canvas1, LMax, calVec1, Scalar(255, 0, 0), 2);
	namedWindow("canvas1", WINDOW_FREERATIO);
	imshow("canvas1", canvas1);
	

	//彩色图像的直方图均衡化
	Mat colorSrc = imread("D:/images/hl.jpg", IMREAD_COLOR);
	namedWindow("color_input",WINDOW_AUTOSIZE);
	namedWindow("color_output", WINDOW_AUTOSIZE);
	imshow("color_input",colorSrc);
	Mat colorDst;
	BGRHist(colorSrc,colorDst);
	imshow("color_output", colorDst);
	Mat guass;
	GaussianBlur(colorDst, guass, Size(3, 3), 0);
	namedWindow("Gauss_output", WINDOW_AUTOSIZE);
	imshow("Gauss_output", guass);
	waitKey(0);
	destroyAllWindows();
	return 0;
}