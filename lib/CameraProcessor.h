#pragma once 
#include "FrameWarp.h"
#include "Logger.h"
#include <thread>

using namespace std;


class CameraProcessor {

private:
	int countSend;
	int countFrame;

	string path;

	int numFramesCheck;

	double frameDiffThreshold;

	bool active;

	FrameWrap frameWrap;

	cv::Mat prev;

public:

	cv::VideoCapture capture;

	CameraProcessor(string path, int numFrames, double frameDiff);
	CameraProcessor(int cameraID, int numFrames, double frameDiff);
	

	~CameraProcessor();

	bool calcAbsDiff();

	void setFrame(cv::Mat f);

	void setPrev(cv::Mat& p);

	void run();
};

string currentTime();
