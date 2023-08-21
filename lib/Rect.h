#include "Header.h"
#include "SQLHandler.h"



class YoloRect {

private:

	vector<Detection>& output;

	vector<string>& class_list;

	FrameWrap& frameWarp;

	vector<Scalar> colors;

	SQLHandler sqlHandler;

	void writeRectOnDB(Rect rect, string objectType);


public:

	YoloRect(FrameWrap& frameW, vector<Detection>& outputP, vector<string>& class_listP);

	void toDrawRect();

	void calcAvgPerChannel(const Mat& img, float* B, float* G, float* R);


};

