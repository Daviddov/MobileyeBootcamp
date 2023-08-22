#include "Header.h"
#include "SQLHandler.h"



class RectHandler {

private:

	vector<Detection>& output;

	vector<string>& class_list;

	FrameWrap& frameWarp;

	vector<Scalar> colors;

	SQLHandler& sqlHandler;

	void writeRectOnDB(Rect rect, string objectType);


public:

	RectHandler(FrameWrap& frameW, vector<Detection>& outputP, vector<string>& class_listP, SQLHandler& sqlHandler);
	
	void toDrawRect();

	void calcAvgPerChannel(const Mat& img, float* B, float* G, float* R);


};

