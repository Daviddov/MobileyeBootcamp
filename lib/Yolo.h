# include "Header.h"



class Yolo5 {

private:

	dnn::Net net;

	vector<Detection> output;

	vector<string> classList;

	FrameWrap& frameWarp;

	void loadNet();


	Mat formatYolov5();

	void loadClassList();
		Mat formatInputImage();

public:

	Yolo5(FrameWrap& frameW);

	vector<Detection>& getOutput();

	vector<string>& getClassList();
	
	void detect();

};

