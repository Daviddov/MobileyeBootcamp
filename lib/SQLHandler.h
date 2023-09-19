#pragma once
//#include "Header.h"
#include <opencv2/opencv.hpp>
#include "sqlite3.h"
#include "Logger.h"
#include "FrameWarp.h"

struct GetFromDataBase {
	int id;
	string time;
	cv::Rect rect;
	FrameWrap fw;
	string typeObject;
	float r, g, b;
};

class SQLHandler {

public:

	SQLHandler();

	~SQLHandler();

	bool open(const char* dbName);

	void close();

	bool createTableIfNotExists();

	bool insertData(cv::Rect rect, FrameWrap& frameWarp, const string& objectType, float R, float G, float B);

	void selectMaxID();

	static int callbackFunction(void* data, int argc, char** argv, char** azColName);

	bool cleanDataBase();

	void printTable();

	bool getDataFromRow(int rowID);

	GetFromDataBase* getRow(int rowID, GetFromDataBase& getDb);

	sqlite3* getDB();

    bool isObjectExistsInLastRecordsQuery(cv::Rect &rect);

private:

	sqlite3* db;
};

