#pragma once 

#include "Header.h"
#include "CameraConnector.h"
#include "./proto_gen/camera_service.grpc.pb.h"
#include <grpc++/grpc++.h>



class CameraProcessor {

private:

	int countFrame;

	int cameraId;

	string path;

	int numFramesCheck;

	double frameDiffThreshold;

	bool active;

	FrameWrap frameWarp;

	Queue<FrameWrap>& dataFromCamera;

	cv::Mat prev;

	cv::VideoCapture capture;

	//CameraConnector connect;

public:

	CameraProcessor(Queue<FrameWrap>& queue, int id, string path);

	~CameraProcessor();

	bool calcAbsDiff();

	void setFrame(cv::Mat f);

	void setPrev(cv::Mat& p);

	int getId();

	void setFrameDiffThreshold(double frameDiff);

	bool init(int numFrames, double frameDiff);

	void send();

	void run();

	static void  cameraPart(CameraProcessor camera);
};

string currentTime();