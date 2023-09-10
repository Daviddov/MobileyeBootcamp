#pragma once 

#include "Header.h"
#include "../protos/service.grpc.pb.h"
#include <grpc++/grpc++.h>


using services::CameraService;
using services::CameraDataRequest;
using services::CameraDataResponse;


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

	void run();
};

string currentTime();



class connectionManager {

public:

	connectionManager(const string& server_address);

	void sendToServer(FrameWrap frameWrap);

	int countTryToConnect;

private:

	unique_ptr<services::CameraService::Stub> stub;
};
	