#pragma once
#include "SQLHandler.h"
#include "Detection.h"


class RectHandler {

private:

	vector<Detection>& output;

	vector<string>& class_list;

	FrameWrap& frameWarp;

	vector<cv::Scalar> colors;

	SQLHandler& sqlHandler;

	void writeRectOnDB(cv::Rect& rect, string objectType);
	void drawDetectBox(cv::Rect& box, int& classId);
public:

	RectHandler(FrameWrap& frameW, vector<Detection>& outputP, vector<string>& class_listP, SQLHandler& sqlHandler);

	void drawAllDetectsBoxs();

	void calcAvgPerChannel(const cv::Mat& img, float* B, float* G, float* R);


};

