#pragma once

#include "Header.h"

class SQLHandler {
public:
    SQLHandler();
    ~SQLHandler();

    bool open(const char* dbName);
    void close();

    bool createTableIfNotExists();
    bool SQLHandler:: SQLHandler::insertData(Rect rect, FrameWrap& frame, const string& objectType, float R, float G, float B);
		void selectMaxID();
    void deleteTable();
    static int callbackFunction(void* data, int argc, char** argv, char** azColName);

private:
    sqlite3* db;
};
