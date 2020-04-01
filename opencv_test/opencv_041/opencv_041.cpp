#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
using namespace std;
using namespace cv;
void cameraDemo();
void RealTimeDemo(string savePath);
void videoDemo(string path);
int main(int argc, char **argv) 
{
	//videoDemo("D:/images/peony.mp4");
	//cameraDemo();
	RealTimeDemo("D:/images/test.mp4");
	waitKey(0);
	destroyAllWindows();
	return 0;
}
/*
* open a video by path 
*/
void videoDemo(string path) 
{
	VideoCapture capture(path.c_str());
	if (!capture.isOpened())
	{
		cout << "can`t opeen this vido" << endl;
	}
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int fps = capture.get(CAP_PROP_FPS);
	int countOfFrame = capture.get(CAP_PROP_FRAME_COUNT);
	cout << "w:" << width << " height:" << height << " fps:" << fps <<" count: "<<countOfFrame<< endl;
	namedWindow("frame", WINDOW_FREERATIO);
	Mat frame;
	while (true)
	{
		bool ret = capture.read(frame);
		if (!ret)
		{
			break;
		}
		imshow("frame", frame);
		char c = waitKey(23);
		if (c == 27)
		{
			break;
		}
	}
	capture.release();
}
/*
* use the camera to svae real time video stream
*/
void RealTimeDemo(string savePath)
{
	VideoCapture capture(0);
	if (!capture.isOpened())
	{
		cout << "can`t opeen this camera" << endl;
	}
	namedWindow("frame", WINDOW_AUTOSIZE);

	double width = capture.get(CAP_PROP_FRAME_WIDTH);
	double height = capture.get(CAP_PROP_FRAME_HEIGHT);
	double fps = capture.get(CAP_PROP_FPS);
	int videoType = capture.get(CAP_PROP_FOURCC);

	VideoWriter writer(savePath.c_str(),videoType,fps,Size(width,height),true);
	Mat frame;
	while (true)
	{
		bool ret = capture.read(frame);
		if (!ret)
		{
			break;
		}
		imshow("frame", frame);
		writer.write(frame);
		char c = waitKey(23);
		if (c == 27)
		{
			break;
		}
	}
	capture.release();
	writer.release();
}

void cameraDemo()
{
	VideoCapture capture(0);
	if (!capture.isOpened())
	{
		cout << "can`t opeen this camera" << endl;
	}
	namedWindow("frame", WINDOW_AUTOSIZE);
	Mat frame;
	while (true)
	{
		bool ret = capture.read(frame);
		if (!ret)
		{
			break;
		}
		imshow("frame", frame);
		char c = waitKey(23);
		if (c == 27)
		{
			break;
		}
	}
	capture.release();
}