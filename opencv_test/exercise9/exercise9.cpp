#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace cv;
using namespace std;
/*
* ͼ��ȥ��
* ������ֵ�˲��� ���ξ�ֵ�˲��� г������г����ֵ�˲���
*��ֵ�˲��� ����Ӧ��ֵ�˲���
*����Ӧ�ֲ������������˲���
* ���ղ�ɫͼ��ȥ��Ĳ���
*/

/*
* ������ֵ�˲���
* cyssmile 
* 2020/6/15
*/
void arithmeticMeanBlur(Mat& src, Mat& dst,int m,int n);
/*
* get the value of copyMakeBorder ��ȡ��Ҫ��Ե���Ĵ�С
* cyssmile
* 2020/6/7
*/
int getBordValue(int Length, int step, int kernelSize);
/*
* auto fill picture�� ���б�Ե���
* cyssmile
* 2020/6/7
*/
void autoCopyMakeBorder(Mat& images, int borderType, int step, int kernelSize);
/*
* ��ӽ�������, ��������������
* cyssmile
* 2020/6/15
* ͨ��noiseType �ж��Ǽ�����������1Ϊ����,2Ϊ��������3Ϊ������
*/
void addSoaltAndPepperNoise(Mat& images, int numberOfNoise,int noiseType);


/*
* add GaussianNoise into source image �趨��ֵ�ͷ�����Ӹ�˹����
* cyssmile
* 2020/6/15
*/
void addGaussianNoise(Mat& images, Scalar mean, Scalar meanDev);

/*
* ���ξ�ֵ 
* ���ַ�ʽ��������ÿ�����ص�1/mn�Ĵ��ݵõ��������Ŀ��Ա���ϸ���������ϴ�
* ������ ���ξ�ֵ�Խ��� �� �� ���� �ر�����
*/
void geometricMean(Mat& src, Mat& dst, int m, int n);

/*
* �Ƚ�5*5 ��������ֵ�˲��� ���� �� �� ��˹ ��������Ч��
*/
void comparedMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc);

/*
* �Ƚ�5*5 �ļ��ξ�ֵ�˲��� ���� �� �� ��˹ ��������Ч��
*/
void comparedGeometricMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc);

/*
* г����ֵ
* г����ֵ �ʺϴ��������������ʺϴ������������Ҳ�ó������˹����
*/
void harmonicMeanBlur(Mat& src, Mat& dst, int m, int n);

/*
* �Ƚ�г����ֵ�� ���� ���� ���� ��˹ �����Ĵ���
* cyssmile
* 2020/6/15
*/
void comparedHarmonicMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc);

/*
*��г����ֵ�˲�
*/
void inverseHarmonicMeanBlure(Mat& src, Mat& dst, int m, int n, double Q);

/*
* �ȽϷ�г����ֵ�� ���� ���� ���� ��˹ �����Ĵ���
* cyssmile
* 2020/6/15
*/
void comparedInverseHarmonicMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc,double Q);

/*
*��ֵ�˲�
* ��ֵ�˲��Դ��������� ���� ����������Ч���ܺ�
*/
void iMidBlur(Mat& src, Mat& dst, int m, int n);

/*
* �Ƚ���ֵ�˲��Խ��Σ���������������˹�����Ĵ���Ч��
*/
void comparedMidBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc);
/*
* ����Ӧ��ֵ�˲���
*/
void adaptiveMeanBlur(Mat& src, Mat& dst, int n, int m);
/*
* �Ƚ�����Ӧ��ֵ�˲��� �Խ��� ���� ���� ��˹�����Ĵ���Ч��
*/
void comparedAdaptiveMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc);
int main(int argc, char** argv) 
{
	Mat src = imread("D:/images/test.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cout << "��ȡͼƬʧ��" << endl;
		exit(0);
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);


	int row = src.rows;
	int col = src.cols;
	
	/*
	* ���ȫͼ0.1�����Ľ�������
	*/
	Mat sapSrc = src.clone();
	addSoaltAndPepperNoise(sapSrc, row * col * 0.1,1);
	imshow("0.1�����Ľ�������", sapSrc);


	/*
	* ���ȫͼ0.1 �����Ľ�����
	*/
	Mat pSrc = src.clone();
	addSoaltAndPepperNoise(pSrc, row * col * 0.1, 2);
	imshow("0.1�����Ľ�����", pSrc);
	
	/*
	* ���ȫͼ0.1 ������������
	*/
	Mat sSrc = src.clone();
	addSoaltAndPepperNoise(sSrc, row * col * 0.1, 3);
	imshow("0.1������������", sSrc);

	/*
	* ��Ӿ�ֵΪ15 ����Ϊ25 �ĸ�˹����
	*/
	Mat gSrc = src.clone();
	addGaussianNoise(gSrc, 15, 25);
	imshow("��Ӿ�ֵΪ15����Ϊ25��˹����ͼƬ", gSrc);


	/*
	* ���� m, n = 5, 5 �ĺ˽���������ֵ�˲� 
	*/
	//comparedMeanBlur(sapSrc, sSrc, pSrc,gSrc);


	/*
	* ���ξ�ֵ ���ַ�ʽ��������ÿ�����ص�1/mn�Ĵ��ݵõ��������Ŀ��Ա���ϸ���������ϴ�
	*/
	comparedGeometricMeanBlur(sapSrc, sSrc, pSrc, gSrc);


	/*
	*	г����ֵ�˲� �Խ��� ���� ���� ��˹��������
	* г����ֵ ���ڴ��� ���� ��˹�����������ڴ����������
	*/
	//comparedHarmonicMeanBlur(sapSrc, sSrc, pSrc, gSrc);
	
	/*
	*	��г����ֵ�˲�
	*/
	//double Q = -1.0;
	//comparedInverseHarmonicMeanBlur(sapSrc, sSrc, pSrc, gSrc,Q);

	/*
	* ��ֵ�˲�
	*/
	//comparedMidBlur(sapSrc, sSrc, pSrc, gSrc);

	/*
	*����Ӧ��ֵ�˲�
	*/
	//comparedAdaptiveMeanBlur(sapSrc, sSrc, pSrc, gSrc);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void arithmeticMeanBlur(Mat& src, Mat& dst, int m, int n) 
{
	double weight = 1.0 / ((double)m * (double)n);

	//����m*n ��С�ĺ���䴦��ͼ��
	//����Ե��С
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	//����������ֵ�˲�
	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			double sum[3] = { 0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						sum[0] += weight * t_src.at<uchar>(i + k, j + m);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						sum[0] += weight* rgb[0];
						sum[1] += weight * rgb[1];
						sum[2] += weight * rgb[2];
					}
				}
			}
			//�޶�����ֵ��0-255֮��
			for (int i = 0; i < channels; i++) {
				if (sum[i] < 0)
					sum[i] = 0;
				else if (sum[i] > 255)
					sum[i] = 255;
			}
			//
			if (channels == 1) {
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(sum[0]);
			}
			else if (channels == 3) {
				Vec3b rgb;
				rgb[0] = static_cast<uchar>(sum[0]);
				rgb[1] = static_cast<uchar>(sum[1]);
				rgb[2] = static_cast<uchar>(sum[2]);
				dst.at<Vec3b>(i - rowPadding, j - colPadding) = rgb;
			}
		}
	}

}

/*
* get the value of copyMakeBorder ��ȡ��Ҫ��Ե���Ĵ�С
* cyssmile
* 2020/6/7
*/
int getBordValue(int Length, int step, int kernelSize)
{
	return (Length * (step - 1) - step + kernelSize) / 2;
}

/*
* auto fill picture�� ���б�Ե���
* cyssmile
* 2020/6/7
*/
void autoCopyMakeBorder(Mat& images, int borderType, int step, int kernelSize)
{
	int row = images.rows;
	int col = images.cols;
	int hightValue = getBordValue(row, step, kernelSize);
	int widthValue = getBordValue(col, step, kernelSize);
	copyMakeBorder(images, images, hightValue, hightValue, widthValue, widthValue, borderType);
}
/*
* ��ӽ������� �� ����������
*/
void addSoaltAndPepperNoise(Mat& images, int numberOfNoise, int noiseType)
{
	RNG rng(12345);
	int row = images.rows;
	int col = images.cols;
	//��ӽ�������
	if (noiseType == 1)
	{
		for (int i = 0; i < numberOfNoise; i++)
		{
			int x = rng.uniform(0, row);
			int y = rng.uniform(0, col);
			if (i % 2 == 0) {
				images.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
			}
			else {
				images.at<Vec3b>(x, y) = Vec3b(0, 0, 0);
			}
		}
	}
	//��ӽ�����
	if (noiseType == 2)
	{
		for (int i = 0; i < numberOfNoise; i++)
		{
			int x = rng.uniform(0, row);
			int y = rng.uniform(0, col);
			images.at<Vec3b>(x, y) = Vec3b(0, 0, 0);
		}
	}

	//���������
	if (noiseType == 3)
	{
		for (int i = 0; i < numberOfNoise; i++)
		{
			int x = rng.uniform(0, row);
			int y = rng.uniform(0, col);
			images.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
		}
	}
}


/*
* add GaussianNoise into source image
* cyssmile
* 2020/3/15
*/
void addGaussianNoise(Mat& images, Scalar mean, Scalar meanDev)
{
	Mat GaussianNoise = Mat::zeros(images.size(), images.type());
	randn(GaussianNoise, mean, meanDev);//randn�������̬�ֲ�������Mat
	//Mat GaussianNoiseDst;
	add(images, GaussianNoise, images);
	//imshow("GaussianNoiseDst_win", GaussianNoiseDst);
}

void comparedMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc)
{
	//5*5 ��������ֵ�˲�����������
	Mat dst1 = sapSrc.clone();
	arithmeticMeanBlur(sapSrc, dst1, 5, 5);
	imshow("5*5������ֵ�������������", dst1);

	//5*5 ��������ֵ�˲���������
	Mat dst2 = pSrc.clone();
	arithmeticMeanBlur(pSrc, dst2, 5, 5);
	imshow("5*5������ֵ�����������", dst2);

	//5*5 ��������ֵ�˲�����������
	Mat dst3 = sSrc.clone();
	arithmeticMeanBlur(sSrc, dst3, 5, 5);
	imshow("5*5������ֵ�������������", dst3);

	//5*5 ��������ֵ�˲������˹����
	Mat dst4 = gSrc.clone();
	arithmeticMeanBlur(gSrc, dst4, 5, 5);
	imshow("5*5������ֵ�����˹�������", dst4);
}


void geometricMean(Mat& src, Mat& dst, int m, int n)
{
	double weight = 1.0 / ((double)m * (double)n);

	//����m*n ��С�ĺ���䴦��ͼ��
	//����Ե��С
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	//���ﲻҪֱ�����src,��Ϊ���������ã����ܺ����ʵ����ظ����
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			double sum[3] = { 1,1,1 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						sum[0] *= (double)t_src.at<uchar>(i + k, j + m);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						sum[0] *= rgb[0];
						sum[1] *= rgb[1];
						sum[2] *= rgb[2];
					}
				}
			}
			//����1/mn����

			for (int i = 0; i < channels; i++) {
				sum[i] = pow(sum[i], weight);
			}
			//�޶�����ֵ��0-255֮��
			for (int i = 0; i < channels; i++) {
				if (sum[i] < 0)
					sum[i] = 0;
				else if (sum[i] > 255)
					sum[i] = 255;
			}
			//
			if (channels == 1) {
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(sum[0]);
			}
			else if (channels == 3) {
				Vec3b rgb;
				rgb[0] = static_cast<uchar>(sum[0]);
				rgb[1] = static_cast<uchar>(sum[1]);
				rgb[2] = static_cast<uchar>(sum[2]);
				dst.at<Vec3b>(i - rowPadding, j - colPadding) = rgb;
			}
		}
	}

}


void comparedGeometricMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc) 
{
	//5*5 �ļ��ξ�ֵ�˲�����������
	Mat dst1 = sapSrc.clone();
	geometricMean(sapSrc, dst1, 5, 5);
	imshow("5*5���ξ�ֵ�������������", dst1);

	//5*5 �ļ��ξ�ֵ�˲���������
	Mat dst2 = pSrc.clone();
	geometricMean(pSrc, dst2, 5, 5);
	imshow("5*5���ξ�ֵ�����������", dst2);

	//5*5 �ļ��ξ�ֵ�˲�����������
	Mat dst3 = sSrc.clone();
	geometricMean(sSrc, dst3, 5, 5);
	imshow("5*5���ξ�ֵ�������������", dst3);

	//5*5 �ļ��ξ�ֵ�˲������˹����
	Mat dst4 = gSrc.clone();
	geometricMean(gSrc, dst4, 5, 5);
	imshow("5*5���ξ�ֵ�����˹�������", dst4);
}

/*
* г����ֵ
* г����ֵ �ʺϴ��������������ʺϴ������������Ҳ�ó������˹����
*/
void harmonicMeanBlur(Mat& src, Mat& dst, int m, int n)
{
	double weight = ((double)m * (double)n);

	//����m*n ��С�ĺ���䴦��ͼ��
	//����Ե��С
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	//���ﲻҪֱ�����src,��Ϊ���������ã����ܺ����ʵ����ظ����
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	//����������ֵ�˲�
	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			double sum[3] = { 0,0,0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						sum[0] += 1.0/(double)t_src.at<uchar>(i + k, j + m);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						sum[0] += 1.0/rgb[0];
						sum[1] += 1.0/rgb[1];
						sum[2] += 1.0/rgb[2];
					}
				}
			}

			//mn/sum[]
			for (int i = 0; i < channels; i++) {
				sum[i] = weight/sum[i];
			}

			//�޶�����ֵ��0-255֮��
			for (int i = 0; i < channels; i++) {
				if (sum[i] < 0)
					sum[i] = 0;
				else if (sum[i] > 255)
					sum[i] = 255;
			}
			//
			if (channels == 1) {
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(sum[0]);
			}
			else if (channels == 3) {
				Vec3b rgb;
				rgb[0] = static_cast<uchar>(sum[0]);
				rgb[1] = static_cast<uchar>(sum[1]);
				rgb[2] = static_cast<uchar>(sum[2]);
				dst.at<Vec3b>(i - rowPadding, j - colPadding) = rgb;
			}
		}
	}
}

void comparedHarmonicMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc) 
{
	//5*5 ��г����ֵ�˲�����������
	Mat dst1 = sapSrc.clone();
	harmonicMeanBlur(sapSrc, dst1, 5, 5);
	imshow("5*5г����ֵ�������������", dst1);

	//5*5 �ļ��ξ�ֵ�˲���������
	Mat dst2 = pSrc.clone();
	harmonicMeanBlur(pSrc, dst2, 5, 5);
	imshow("5*5г����ֵ�����������", dst2);

	//5*5 ��������ֵ�˲�����������
	Mat dst3 = sSrc.clone();
	harmonicMeanBlur(sSrc, dst3, 5, 5);
	imshow("5*5г����ֵ�������������", dst3);

	//5*5 ��������ֵ�˲������˹����
	Mat dst4 = gSrc.clone();
	harmonicMeanBlur(gSrc, dst4, 5, 5);
	imshow("5*5г����ֵ�����˹�������", dst4);
}

/*
*
*/
void inverseHarmonicMeanBlure(Mat& src, Mat& dst, int m, int n, double Q)
{
	double weight = ((double)m * (double)n);

	//����m*n ��С�ĺ���䴦��ͼ��
	//����Ե��С
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	//���ﲻҪֱ�����src,��Ϊ���������ã����ܺ����ʵ����ظ����
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	//����������ֵ�˲�
	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			double sum[3] = { 0,0,0 };
			double sum1[3] = { 0,0,0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						sum[0] += pow( (double)t_src.at<uchar>(i + k, j + m),Q+1);
						sum1[0] += pow((double)t_src.at<uchar>(i + k, j + m), Q);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						sum[0] += pow(rgb[0],Q+1);
						sum[1] += pow(rgb[1], Q + 1);
						sum[2] += pow(rgb[2], Q + 1);

						sum1[0] += pow(rgb[0], Q);
						sum1[1] += pow(rgb[1], Q);
						sum1[2] += pow(rgb[2], Q);
					}
				}
			}

			double result[3] = { 0,0,0 };
			//�޶�����ֵ��0-255֮��
			for (int t = 0; t < channels; t++) {
				result[t] = (double)sum[t] / sum1[t];
				if (result[t] < 0)
					result[t] = 0;
				else if (result[t] > 255)
					result[t] = 255;
			}
			//
			if (channels == 1) {
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(result[0]);
			}
			else if (channels == 3) {
				Vec3b rgb;
				rgb[0] = static_cast<uchar>(result[0]);
				rgb[1] = static_cast<uchar>(result[1]);
				rgb[2] = static_cast<uchar>(result[2]);
				dst.at<Vec3b>(i - rowPadding, j - colPadding) = rgb;
			}
		}
	}
}

void comparedInverseHarmonicMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc, double Q) 
{
	//5*5 �ķ�г����ֵ�˲�����������
	Mat dst1 = sapSrc.clone();
	inverseHarmonicMeanBlure(sapSrc, dst1, 5, 5, Q);
	imshow("5*5��г����ֵ�������������", dst1);

	//5*5 �ļ��ξ�ֵ�˲���������
	Mat dst2 = pSrc.clone();
	inverseHarmonicMeanBlure(pSrc, dst2, 5, 5, Q);
	imshow("5*5��г����ֵ�����������", dst2);

	//5*5 �ļ��ξ�ֵ�˲�����������
	Mat dst3 = pSrc.clone();
	inverseHarmonicMeanBlure(sSrc, dst3, 5, 5, Q);
	imshow("5*5��г����ֵ���������������", dst3);

	//5*5 �ķ�г���˲������˹����
	Mat dst4 = gSrc.clone();
	inverseHarmonicMeanBlure(gSrc, dst3, 5, 5, Q);
	imshow("5*5��г����ֵ�����˹�������", dst4);
}


/*
*��ֵ�˲�
* ��ֵ�˲��Դ��������� ���� ����������Ч���ܺ�
*/
void iMidBlur(Mat& src, Mat& dst, int m, int n)
{
	double weight = ((double)m * (double)n);

	//����m*n ��С�ĺ���䴦��ͼ��
	//����Ե��С
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	//���ﲻҪֱ�����src,��Ϊ���������ã����ܺ����ʵ����ظ����
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	int channels = src.channels();
	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;

	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {
			vector<double> mid0,mid1,mid2;
			mid0.clear();
			mid1.clear();
			mid2.clear();

			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						mid0.push_back((double)t_src.at<uchar>(i + k, j + m));
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						mid0.push_back((double)rgb[0]);
						mid1.push_back((double)rgb[1]);
						mid2.push_back((double)rgb[2]);
					}
				}
			}

			sort(mid0.begin(), mid0.end());
			sort(mid1.begin(), mid1.end());
			sort(mid2.begin(), mid2.end());


			int r = m * n / 2;
			if (channels == 1) {
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(mid0[r]);
			}
			else if (channels == 3) {
				Vec3b rgb;
				rgb[0] = static_cast<uchar>(mid0[r]);
				rgb[1] = static_cast<uchar>(mid1[r]);
				rgb[2] = static_cast<uchar>(mid2[r]);
				dst.at<Vec3b>(i - rowPadding, j - colPadding) = rgb;
			}
		}
	}
}

void comparedMidBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc) 
{
	//5*5 ����ֵ�˲�����������
	Mat dst1 = sapSrc.clone();
	iMidBlur(sapSrc, dst1, 5, 5);
	imshow("5*5��ֵ�˲��������������", dst1);

	//5*5 ����ֵ�˲���������
	Mat dst2 = pSrc.clone();
	iMidBlur(pSrc, dst2, 5, 5);
	imshow("5*5��ֵ�˲������������", dst2);

	//5*5 ����ֵ�˲�����������
	Mat dst3 = pSrc.clone();
	iMidBlur(sSrc, dst3, 5, 5);
	imshow("5*5��ֵ�˲����������������", dst3);

	//5*5 ����ֵ�˲������˹����
	Mat dst4 = gSrc.clone();
	iMidBlur(gSrc, dst3, 5, 5);
	imshow("5*5��ֵ�˲������˹�������", dst4);
}

/*
* ����Ӧ��ֵ�˲���
*/
void adaptiveMeanBlur(Mat& src, Mat& dst, int n, int m) 
{

	//����m*n ��С�ĺ���䴦��ͼ��
	//����Ե��С
	int row = src.rows;
	int col = src.cols;
	int rowPadding = getBordValue(row, 1, n);
	int colPadding = getBordValue(col, 1, m);
	//���ﲻҪֱ�����src,��Ϊ���������ã����ܺ����ʵ����ظ����
	Mat t_src;
	copyMakeBorder(src, t_src, rowPadding, rowPadding, colPadding, colPadding, BORDER_DEFAULT);

	//����ȫ�ֵķ���
	vector<Mat> splitMat;
	split(src,splitMat);
	double stdDevValue[3] = { 0,0,0 };
	int channels = src.channels();
	for (int i = 0; i < channels;i++) 
	{
		Mat mt, dt;
		meanStdDev(splitMat[i], mt, dt);
		stdDevValue[i] = pow(dt.at<double>(0, 0), 2);
	}

	int cols = t_src.cols - rowPadding;
	int rows = t_src.rows - colPadding;
	int roiSize = m * n;
	for (int i = rowPadding; i < rows; i++) {
		for (int j = colPadding; j < cols; j++) {

			//����ѡ���ROI����ľ�ֵ
			double totalPiex[3] = { 0,0,0 };
			for (int k = -rowPadding; k <= rowPadding; k++) 
			{
				for (int m = -colPadding; m <= colPadding; m++) 
				{
					if (channels == 1) 
					{
						totalPiex[0] += (double)t_src.at<uchar>(i + k, j + m);
					}
					else {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						totalPiex[0] += (double)rgb[0];
						totalPiex[1] += (double)rgb[1];
						totalPiex[2] += (double)rgb[2];
					}
				}
			}
			for (int t = 0; t < channels; t++) {
				//����õ���ֵ
				totalPiex[t] = (double)totalPiex[t] / roiSize;
			}

			//������Ҫ��ֲ�����
			double roiDev[3] = { 0,0,0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						roiDev[0] += pow((double)t_src.at<uchar>(i + k, j + m)-totalPiex[0],2);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						roiDev[0] += pow((double)rgb[0] - totalPiex[0], 2);
						roiDev[1] += pow((double)rgb[1] - totalPiex[1], 2);
						roiDev[2] += pow((double)rgb[2] - totalPiex[0], 2);
					}
				}
			}
			for (int t = 0; t < channels; t++) {
				//����õ�����
				roiDev[t] = roiDev[t] / roiSize;
			}

			//����ÿ�����ص�ֵ ����Ӧ��ֵ��
			double result[3] = { 0,0,0 };
			for (int k = -rowPadding; k <= rowPadding; k++) {
				for (int m = -colPadding; m <= colPadding; m++) {
					if (channels == 1) {
						result[0] = t_src.at<uchar>(i + k, j + m)-(stdDevValue[0]/roiDev[0])*(t_src.at<uchar>(i + k, j + m)-totalPiex[0]);
					}
					else if (channels == 3) {
						Vec3b rgb = t_src.at<Vec3b>(i + k, j + m);
						result[0] = rgb[0] - (stdDevValue[0] / roiDev[0]) * (rgb[0] - totalPiex[0]);
						result[1] = rgb[1] - (stdDevValue[1] / roiDev[1]) * (rgb[1] - totalPiex[1]);
						result[2] = rgb[2] - (stdDevValue[2] / roiDev[2]) * (rgb[2] - totalPiex[2]);
					}
				}
			}
			
			//�޶�����ֵ��0-255֮��
			for (int t = 0; t < channels; t++) {
				if (result[t] < 0)
					result[t] = 0;
				else if (result[t] > 255)
					result[t] = 255;
			}
			//
			if (channels == 1) {
				dst.at<uchar>(i - rowPadding, j - colPadding) = static_cast<uchar>(result[0]);
			}
			else if (channels == 3) {
				Vec3b rgb;
				rgb[0] = static_cast<uchar>(result[0]);
				rgb[1] = static_cast<uchar>(result[1]);
				rgb[2] = static_cast<uchar>(result[2]);
				dst.at<Vec3b>(i - rowPadding, j - colPadding) = rgb;
			}
		}
	}
}

void comparedAdaptiveMeanBlur(Mat& sapSrc, Mat& sSrc, Mat& pSrc, Mat& gSrc) 
{
	//3*3 ������Ӧ��ֵ�˲�����������
	Mat dst1 = sapSrc.clone();
	adaptiveMeanBlur(sapSrc, dst1, 3, 3);
	imshow("3*3����Ӧ��ֵ�˲��������������", dst1);

	//5*5 ������Ӧ��ֵ�˲���������
	Mat dst2 = pSrc.clone();
	adaptiveMeanBlur(pSrc, dst2, 3, 3);
	imshow("3*3����Ӧ��ֵ�˲������������", dst2);

	//3*3 ������Ӧ��ֵ�˲�����������
	Mat dst3 = pSrc.clone();
	adaptiveMeanBlur(sSrc, dst3, 3, 3);
	imshow("3*3����Ӧ��ֵ�˲����������������", dst3);

	//3*3 ������Ӧ��ֵ�˲������˹����
	Mat dst4 = gSrc.clone();
	adaptiveMeanBlur(gSrc, dst3, 3, 3);
	imshow("3*3����Ӧ��ֵ�˲������˹�������", dst4);
}

