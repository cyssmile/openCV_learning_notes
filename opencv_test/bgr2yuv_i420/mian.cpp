#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstring>
using namespace cv;
using namespace std;

void test_bgr2yuv(Mat &src, unsigned char** yuv_buf) {
	//创建yuv二维的数组
	size_t src_w = src.cols;
	size_t src_h = src.rows;
	yuv_buf[0] = (unsigned char*)malloc(src_w * src_h * sizeof(unsigned char));
	yuv_buf[1] = (unsigned char*)malloc(src_w * src_h * sizeof(unsigned char)/4);
	yuv_buf[2] = (unsigned char*)malloc(src_w * src_h * sizeof(unsigned char)/4);
	if (yuv_buf == nullptr || yuv_buf[0] == nullptr || yuv_buf[1] == nullptr || yuv_buf[2] == nullptr) {
		std::cout << " malloc failed" << std::endl;
	}
	Mat temp_yuv;
	cvtColor(src, temp_yuv, COLOR_BGR2YUV_I420);
	namedWindow("yuvi420", WINDOW_FREERATIO);
	imshow("yuvi420", temp_yuv);
	memcpy(yuv_buf[0], temp_yuv.data, src_w * src_h);
	memcpy(yuv_buf[1], temp_yuv.data + src_w * src_h, src_w * src_h/4);
	memcpy(yuv_buf[2], temp_yuv.data + src_w * src_h*5/4, src_w * src_h / 4);
}
void test_yuv2bgr_i420(unsigned char **yuv_buf, size_t planner, size_t yuv_w, size_t yuv_h) {
	unsigned char* temp_data = (unsigned char*)malloc(yuv_w * yuv_h * sizeof(unsigned char*));
	memcpy(temp_data, yuv_buf[0], yuv_w * yuv_h * 2 / 3);
	memcpy(temp_data+ yuv_w * yuv_h * 2 / 3, yuv_buf[1], yuv_w * yuv_h  / 6);
	memcpy(temp_data + yuv_w * yuv_h * 2 / 3 + yuv_w * yuv_h / 6, yuv_buf[2], yuv_w * yuv_h / 6);
	Mat temp_yuv(yuv_h, yuv_w, CV_8UC1, temp_data);

	Mat bgr;
	cvtColor(temp_yuv, bgr, COLOR_YUV2BGRA_I420);
	namedWindow("yuvi420 to bgr", WINDOW_FREERATIO);
	imshow("yuvi420 to bgr", bgr);
	free(temp_data);
	temp_data = nullptr;
}
int main(int argc, char** argv) {
	Mat src = imread("D:/images/dog.jpg"); // BGR
	if (src.empty()) {
		cout << " read images error" << endl;
		return -1;
	}

	unsigned char** yuv_buf = (unsigned char**)malloc(3 * sizeof(unsigned char*));
	test_bgr2yuv(src, yuv_buf);
	size_t yuv_h = src.rows * 3 / 2;
	size_t yuv_w = src.cols;
	test_yuv2bgr_i420(yuv_buf, 3, yuv_w, yuv_h);
	//验证我们的yuv_buf数据是否正确


	//释放资源
	for (size_t i = 0; i < 3; i++) {
		if (yuv_buf[i] != nullptr) {
			free(yuv_buf[i]);
			yuv_buf[i] = nullptr;
		}
	}
	if (yuv_buf != nullptr) {
		free(yuv_buf);
		yuv_buf = nullptr;
	}
	namedWindow("input", WINDOW_FREERATIO);
	imshow("input", src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}