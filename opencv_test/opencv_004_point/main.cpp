#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	Mat src = imread("D:/images/dog.jpg", IMREAD_COLOR);
	namedWindow("src_wind", WINDOW_FREERATIO);
	imshow("src_wind", src);
	
	Mat t1 = Mat::zeros(src.size(), src.type());
	int height = t1.rows;
	int width = t1.cols;
	int ch = t1.channels();

	//mat.ptr<index坐标数据类型>（x） 获取row每个像素的指针集合
	for (int row = 0; row < height; row++)
	{
		uchar* curr_row = src.ptr<uchar>(row);
		//获取每行的所有的指针，以下每次循环，遍历一个Vec3b或其他色彩空间的集合
		//所以每次可以使用curr_row++
		uchar* curr_row_t1 = t1.ptr<uchar>(row);
		for (int col = 0; col < width; col++)
		{
			//根据通道数进行相应的操作
			if (ch == 3)
			{
				int blue = *curr_row++;
				int green = *curr_row++;
				int red = *curr_row++;

				//利用src的值赋值改变t1
				*curr_row_t1++ = blue;
				*curr_row_t1++ = green;
				*curr_row_t1++ = red;

			}
			//单通道
			if (ch == 1)
			{
				int pv = *curr_row++;
				*curr_row_t1++ = pv;
			}
		}
	}
	//展示处理后的图片
	namedWindow("t1_wind", WINDOW_FREERATIO);
	imshow("t1_wind", t1);
	waitKey(0);
	destroyAllWindows();
	return 0;
}