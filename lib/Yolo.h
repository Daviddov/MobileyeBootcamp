#pragma once
# include "CameraProcessor.h"
#include "Detection.h"

enum  {
	ZERO,
	BICYCLE,
	CAR,
	MOTORBIKE,
	AEROPLANE,
	BUS,
	TRAIN,
	TRUCK
};

class Yolo5 {
private:
	 float INPUT_SIZE ;
	 float SCORE_THRESHOLD ;
	 float NMS_THRESHOLD ;
	 float CONFIDENCE_THRESHOLD ;

	 int NUM_OF_DETECT;
	 int NUM_OF_DATA ;

	
	 cv::dnn::Net net;

	vector<Detection> output;

	vector<string> classList;

	FrameWrap frameWarp;

	void loadNet();

	void loadClassList();

	cv::Mat formatInputImage();
public:

	Yolo5();

	void setFrame(FrameWrap& currFrame);

	vector<Detection>& getOutput();
	
	vector<string>& getClassList();
	
	void detect();

};

