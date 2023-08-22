# include "Header.h"



class Yolo5 {

private:
	const float INPUT_SIZE = 640.0f;
	const float SCORE_THRESHOLD = 0.2f;
	const float NMS_THRESHOLD = 0.4f;
	const float CONFIDENCE_THRESHOLD = 0.4f;

	const int NUM_OF_DETECT = 25200;
	const int NUM_OF_DATA = 85;

	dnn::Net net;

	vector<Detection> output;

	vector<string> classList;

	FrameWrap frameWarp;

	void loadNet();

	void loadClassList();

	Mat formatInputImage();

public:

	Yolo5();
	void setFrame(FrameWrap& currFrame);
	vector<Detection>& getOutput();

	vector<string>& getClassList();
	
	void detect();

};

