#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
using namespace cv;

void addSoaltAndPepperNoise(Mat &images, int numberOfNoise);
void adaptiveMedianBlur(Mat &images);
int getBordValue(int Length, int step, int kernelSize);
void autoCopyMakeBorder(Mat &images, int borderType, int step, int kernelSize);
void getMinMaxSplitChannel(Mat &images, double &min_val, double &max_val);
void getMedianSplitChannel(Mat &images, double &median_val);
double process_B(double Z_xy, double min_val, double max_val, double median_val);
double dealSplitSubImages(Mat &split_images,int &S_now);
void dealMainSplitImages(Mat &split_images, Mat &split_images_clone);
void dealDstEdges(Mat &src, int edges);

int main(int argc, char** argv)
{
	Mat src = imread("D:/images/test.jpg", -1);
	if (src.empty())
	{
		cout << " can`t open this ph" << endl;
	}
	imshow("src_win", src);
	Mat images_src = src.clone();
	/*
	* 添加全图0.25比例的椒盐噪声
	*/
	int row = images_src.rows;
	int col = images_src.cols;
	addSoaltAndPepperNoise(images_src, row*col*0.25);
	adaptiveMedianBlur(images_src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

/*
* add salt and pepper noise into source images
* cyssmile
* 2020/3/15
*/
void addSoaltAndPepperNoise(Mat &images, int numberOfNoise)
{
	RNG rng(12345);
	int row = images.rows;
	int col = images.cols;
	for (int i = 0; i < numberOfNoise; i++)
	{
		int x = rng.uniform(0, row);
		int y = rng.uniform(0, col);
		if (i % 2 == 0)
		{
			images.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
		}
		else
		{
			images.at<Vec3b>(x, y) = Vec3b(0, 0, 0);
		}
	}
	imshow("salt and pepper noise", images);
}

/*
* get the value of copyMakeBorder
* cyssmile
* 2020/3/19
*/
int getBordValue(int Length, int step, int kernelSize) 
{
	return (Length*(step - 1) - step + kernelSize) / 2;
}

/*
* auto fill picture
* cyssmile
* 2020/3/19
*/
void autoCopyMakeBorder(Mat &images, int borderType, int step, int kernelSize)
{
	int row = images.rows;
	int col = images.cols;
	int hightValue = getBordValue(row, step, kernelSize);
	int widthValue = getBordValue(col, step, kernelSize);
	copyMakeBorder(images, images, hightValue, hightValue, widthValue, widthValue, borderType);
}
/*
* adaptive median filtering
* Anchor Point at top left corner
* S_Min =3,S_Max=5
* cyssmile
* 2020/3/19
*/
void adaptiveMedianBlur(Mat &images) 
{
	int S_Max = 5;
	int S_Min = 3;
	int row = images.rows;
	int col = images.cols;
	Mat images_clone = images.clone();
	autoCopyMakeBorder(images, BORDER_DEFAULT, 1, S_Min);
	
	vector<Mat> sub_images;
	split(images,sub_images);

	vector<Mat> sub_images_clone;
	split(images_clone, sub_images_clone);

	for (int i=0;i<images.channels();i++) 
	{
		dealMainSplitImages(sub_images[i], sub_images_clone[i]);
	}
	Mat dst;
	merge(sub_images_clone,dst);
	dealDstEdges(dst, S_Max);
	imshow("dst_output", dst);
}
/*
* get the min and max value in images
* cyssmile
* 2020/03/19
*/
void getMinMaxSplitChannel(Mat &images,double &min_val,double &max_val)
{
	Point minloc, maxloc;
	minMaxLoc(images, &min_val, &max_val, &minloc, &maxloc);
}

/*
* get the median  value in images(roi)
* cyssmile
* 2020/03/19
*/
void getMedianSplitChannel(Mat &images,double &median_val) 
{
	vector<double> images_data;
	for (int i =0;i<images.rows;i++) 
	{
		for (int j = 0; j < images.cols; j++) 
		{
			images_data.push_back(images.at<uchar>(i, j));
		}
	}
	sort(images_data.begin(),images_data.end());
	median_val = images_data[images.rows*images.cols/2];
}
/*
* process_B
* cyssmile
* 2020/03/19
*/
double process_B(double Z_xy,double min_val,double max_val,double median_val) 
{
	if (Z_xy-min_val>0 && Z_xy-max_val<0) 
	{
		return Z_xy;
	}
	else
	{
		return median_val;
	}
}
/*
* give a roi images and then return in (x,y) its (maybe) value
* cyssmile
* 20/03/19
*/
double dealSplitSubImages(Mat &split_images,int &S_now) 
{
	double min = split_images.at<uchar>(0, 0);
	double &min_val = min;
	double max = split_images.at<uchar>(0, 0);
	double &max_val = max;
	getMinMaxSplitChannel(split_images, min_val, max_val);

	double median = split_images.at<uchar>(0, 0);
	double &median_val = median;
	getMedianSplitChannel(split_images, median_val);

	double result_piexl= split_images.at<uchar>(0, 0);
	if (median - min_val > 0 && median - max_val < 0)
	{ // turn process B
		result_piexl = process_B(split_images.at<uchar>(0, 0), min_val, max_val, median_val);

	}else {
		S_now = S_now + 2;
	}
	return result_piexl;
}
/*
* deal a splited channel images
* cyssmile
* 20/03/19
*/
void dealMainSplitImages(Mat &split_images,Mat &split_images_clone) 
{
	int S_Min = 3, S_Max = 7;
	for (int i = 0; i < split_images_clone.rows; i++)
	{
		for (int j = 0; j < split_images_clone.cols; j++)
		{
			int S_now = S_Min;
			double median;
			double result_piexl = split_images_clone.at<uchar>(i, j);
			if ((i + S_Max < split_images.rows )&& (j + S_Max < split_images.cols))
			{
				while (S_now <= S_Max)
				{ //重复A处理过程
					Rect rec;
					rec.x = j;
					rec.y = i;
					rec.width = S_now;
					rec.height = S_now;
					if ((rec.x + S_now >= split_images.rows) && (rec.y + S_now >= split_images.cols))
					{
						break;
					}
					Mat sub = split_images(rec);
					int S_old = S_now;
					result_piexl = dealSplitSubImages(sub, S_now);
					if (S_old == S_now) 
					{
						break;
					}
					else 
					{
						getMedianSplitChannel(sub, median);
						result_piexl = median;
					}
				}
			}
			split_images_clone.at<uchar>(i, j) = result_piexl;
		}
	}
}

/*
* deal edges int dst images
* cyssmile
* 20/03/19
*/
void dealDstEdges(Mat &src,int edges) 
{
	Rect rec;
	rec.x = src.cols - edges;
	rec.y = 0 ;
	rec.width = edges;
	rec.height = src.rows;
	Mat NeedDealMat = src(rec);
	medianBlur(NeedDealMat, NeedDealMat, 3);
	
	Rect rec_bottom;
	rec_bottom.x = 0;
	rec_bottom.y = src.rows - edges;
	rec_bottom.width = src.cols;
	rec_bottom.height = edges;
	Mat NeedDealMat_bottom = src(rec_bottom);
	medianBlur(NeedDealMat_bottom, NeedDealMat_bottom, 3);
}