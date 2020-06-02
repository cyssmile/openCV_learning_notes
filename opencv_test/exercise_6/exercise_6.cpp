#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<iterator>
using namespace std;
using namespace cv;

/*
* ͳ�Ƶ�ͨ����Mat�е�������Ϣ�� ��Ϣ������calVec��,calMat: 1*L 
* Ҫ�� src CV_8UC1�� LMax Ϊ�ܹ��ĻҶȼ���
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
	cout << "ͳ�����" << endl;
}

/*
* ����r ��s ֮��Ĳ�ѯ��
* s = r/MN * ��r
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
* ֱ��ͼ���⻯
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
*  ������ͼչʾֱ��ͼ����ǰ ��ֱ��ͼ���������طֲ����
*/

void showHistChart(Mat& canvas,unsigned int LMax,vector<unsigned int> calVec,Scalar sca, int thikness)
{
//�����ǻҶȼ�
//���������صķֲ�������Ҳ�ȡ�ķ�����������Ŀ����Ϊ��λ1
	int canvas_height = canvas.rows;
	int canvas_step = canvas.cols / LMax;
	auto it = max_element(calVec.begin(), calVec.end());
	unsigned int calMax = *it;

	//��ʼ������ͼ
	for (int i = 0; i < LMax-1; i++) 
	{
		line(canvas, Point(i * canvas_step, canvas_height - (canvas_height*(1.0)*calVec[i]/calMax)),
			Point((i + 1) * canvas_step, canvas_height - (canvas_height * (1.0) * calVec[i+1] / calMax)),
			sca, thikness, 8);
	}
}
/*
* ��ɫͼ���ֱ��ͼ���⻯
*/
void BGRHist(Mat& src, Mat& dst) 
{
	//����ɫͼ��İ���BGR����ͨ���з�
	vector<Mat> splitMat;
	split(src,splitMat);

	//�ֱ��bgr ����ͨ������ֱ��ͼ���⻯
	vector<Mat> mergeMat;
	split(src, mergeMat);
	for (int i = 0; i < 3; i++) 
	{
		unsigned int LMax = 256;
		vector<unsigned int> calVec(LMax, 0);
		vector<unsigned int > calVecBefor(LMax, 0);//���ڼ�¼�Ҷȼ�l֮ǰ�����Ե����ص����
		calHistInfo(splitMat[i], calVec, calVecBefor, LMax);
		//������������r ���������s ֮��� һһӳ���
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
	//ͳ������ͼ���е�������Ϣ
	unsigned int LMax = 256;
	vector<unsigned int> calVec(LMax, 0);
	vector<unsigned int > calVecBefor(LMax, 0);//���ڼ�¼�Ҷȼ�l֮ǰ�����Ե����ص����
	calHistInfo(src, calVec, calVecBefor,LMax);
	
	//������������r ���������s ֮��� һһӳ���
	unordered_map<unsigned int, unsigned int > table_rs;
	createRSTable(calVecBefor,table_rs,LMax);

	//����ֱ��ͼ���⻯
	Mat dst;
	iHistImp(src, dst, table_rs);
	

	//opencv �Դ���ֱ��ͼ���⣬ �Ƚ��Լ�ʵ�ֵĲ��
	Mat dst1;
	equalizeHist(src, dst1);
	namedWindow("api_output", WINDOW_AUTOSIZE);
	imshow("api_output", dst1);
	
	//չʾЧ��
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("output", WINDOW_AUTOSIZE);
	imshow("input", src);
	imshow("output",dst);

	//չʾֱ��ͼ���⻯ǰ������ͼ
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	canvas = Scalar(255, 255, 255);
	showHistChart(canvas,LMax,calVec,Scalar(0,0,255),2);
	namedWindow("canvas", WINDOW_FREERATIO);
	imshow("canvas",canvas);
	
	// չʾֱ��ͼ���⻯�������ͼ
	vector<unsigned int> calVec1(LMax, 0);
	vector<unsigned int > calVecBefor1(LMax, 0);//���ڼ�¼�Ҷȼ�l֮ǰ�����Ե����ص����
	calHistInfo(dst, calVec1, calVecBefor1, LMax);
	Mat canvas1 = Mat::zeros(Size(512, 512), CV_8UC3);
	canvas1 = Scalar(255, 255, 255);
	showHistChart(canvas1, LMax, calVec1, Scalar(255, 0, 0), 2);
	namedWindow("canvas1", WINDOW_FREERATIO);
	imshow("canvas1", canvas1);
	

	//��ɫͼ���ֱ��ͼ���⻯
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