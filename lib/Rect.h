#include "Header.h"
#include "SQLHandler.h"



class YoloRect {

private:

	vector<Detection>& output;

	vector<string>& class_list;

	FrameWrap& frame;

	vector<Scalar> colors;

	SQLHandler sqlHandler;

	void writeRectOnDB(Rect rect, string objectType);


public:

	YoloRect(FrameWrap& frameW, vector<Detection>& outputP, vector<string>& class_listP);

	void toDrawRect();

	void calcAvgPerChannel(const Mat& img, float* B, float* G, float* R);


	//bool createTableIfNotExists(sqlite3* db);
	//bool insertData(sqlite3* db, Rect rect, string objectType, float R, float G, float B);
	//void selectMaxID(sqlite3* db);
	//void deleteTable(sqlite3 * db);

};

