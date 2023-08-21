#pragma once
#include "Header.h"

class SQLHandler {

public:

	SQLHandler();

	~SQLHandler();

	bool open(const char* dbName);

	void close();

	bool createTableIfNotExists();

	bool insertData(Rect rect, FrameWrap& frame, const string& objectType, float R, float G, float B);

	void selectMaxID();

	static int callbackFunction(void* data, int argc, char** argv, char** azColName);

	void printTable();

private:

	sqlite3* db;
};
