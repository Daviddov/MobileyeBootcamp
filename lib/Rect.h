#include "Header.h"




class YoloRect {

private:

	vector<Detection>& output;

	vector<string>& class_list;

	FrameWrap& frame;

	vector<Scalar> colors;

	void writeRectOnDB(Rect rect, string objectType);

	static int callbackFunction(void* data, int argc, char** argv, char** azColName);

	bool handleDBError(int failed, sqlite3* db, string what);

public:

	YoloRect(FrameWrap& frameW, vector<Detection>& outputP, vector<string>& class_listP);

	void toDrawRect();

	void calcAvgPerChannel(const Mat& img, float* B, float* G, float* R);

};

