#pragma once
#include "SQLHandler.h"


class RectHandler {

private:

	vector<Detection>& output;

	vector<string>& class_list;

	FrameWrap& frameWarp;

	vector<cv::Scalar> colors;

	SQLHandler& sqlHandler;

public:
	void writeRectOnDB(cv::Rect rect, string objectType);

	RectHandler(FrameWrap& frameW, vector<Detection>& outputP, vector<string>& class_listP, SQLHandler& sqlHandler);
	
	void toDrawRect();

	 void calcAvgPerChannel(const cv::Mat& img, float* B, float* G, float* R);


};

