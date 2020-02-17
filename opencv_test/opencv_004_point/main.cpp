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

	//mat.ptr<index������������>��x�� ��ȡrowÿ�����ص�ָ�뼯��
	for (int row = 0; row < height; row++)
	{
		uchar* curr_row = src.ptr<uchar>(row);
		//��ȡÿ�е����е�ָ�룬����ÿ��ѭ��������һ��Vec3b������ɫ�ʿռ�ļ���
		//����ÿ�ο���ʹ��curr_row++
		uchar* curr_row_t1 = t1.ptr<uchar>(row);
		for (int col = 0; col < width; col++)
		{
			//����ͨ����������Ӧ�Ĳ���
			if (ch == 3)
			{
				int blue = *curr_row++;
				int green = *curr_row++;
				int red = *curr_row++;

				//����src��ֵ��ֵ�ı�t1
				*curr_row_t1++ = blue;
				*curr_row_t1++ = green;
				*curr_row_t1++ = red;

			}
			//��ͨ��
			if (ch == 1)
			{
				int pv = *curr_row++;
				*curr_row_t1++ = pv;
			}
		}
	}
	//չʾ������ͼƬ
	namedWindow("t1_wind", WINDOW_FREERATIO);
	imshow("t1_wind", t1);
	waitKey(0);
	destroyAllWindows();
	return 0;
}