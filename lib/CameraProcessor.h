#pragma once 

#include "Header.h"
#include "../proto_gen/camera_service.grpc.pb.h"
#include <grpc++/grpc++.h>



class CameraProcessor {

private:

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

	~CameraProcessor();

	bool calcAbsDiff();

	void setFrame(cv::Mat f);

	void setPrev(cv::Mat& p);

	void setFrameDiffThreshold(double frameDiff);

	void run();
};

string currentTime();



class connectionManager {

public:

	connectionManager(const string& server_address);

	void sendToServer(FrameWrap& frameWrap);


private:

	unique_ptr<services::CameraService::Stub> stub;
};
	