# include "Header.h"



class Yolo5 {

private:

	dnn::Net net;

	vector<Detection> output;

	vector<string> class_list;

	FrameWrap& frame;

	void load_net();

	void load_class_list();

	Mat format_yolov5();

public:

	Yolo5(FrameWrap& frameW);

	vector<Detection>& getOutput();

	vector<string>& getClassList();
	
	void detect();

};

