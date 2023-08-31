#pragma once

#include "Header.h"
#include "CameraConnector.h"
//#include <grpc++/grpc++.h>
//#include "camera_service.grpc.pb.h"
//


class CameraProcessor {

private:

	int countFrame;

	int cameraId;

	string path;

	int numFramesCheck;

	double frameDiffThreshold;

	bool active;

	FrameWrap frameWarp;

	queue<FrameWrap>& dataFromCamera;

	Mat prev;

	VideoCapture capture;

	//CameraConnector connect;

public:

	CameraProcessor(queue<FrameWrap>& queue, int id, string path);

	~CameraProcessor();

	bool calcAbsDiff();

	void setFrame(Mat f);

	void setPrev(Mat p);

	int getId();

	void setFrameDiffThreshold(double frameDiff);

	bool init(int numFrames, double frame_diff);

	void insertToQueue();

	void run();

	static void  cameraPart(CameraProcessor* camera);
};

string currentTime();