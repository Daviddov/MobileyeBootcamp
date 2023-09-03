#pragma once
#include "Header.h"

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

    bool checkRectExistsInLastFrame(cv::Rect rect);

private:

	sqlite3* db;
};

