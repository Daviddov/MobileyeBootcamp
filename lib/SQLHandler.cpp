#include "SQLHandler.h"
#include "../lib_logger/Logger.h"

//c'tor
SQLHandler::SQLHandler() : db(nullptr) {}

//d'tor
SQLHandler::~SQLHandler() {
	close();
}

bool SQLHandler::open(const char* dbName) {
	return sqlite3_open(dbName, &db) == SQLITE_OK;
}

void SQLHandler::close() {
	if (db) {
		sqlite3_close(db);
		db = nullptr;
	}
}

bool SQLHandler::createTableIfNotExists() {
	const char* createTableQuery = "CREATE TABLE IF NOT EXISTS MyTable ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"timestamp TEXT NOT NULL,"
		"\"frame number\" INT NOT NULL,"
		"\"Top left X\" INTEGER NOT NULL,"
		"\"Top left Y\" INTEGER NOT NULL,"
		"width INTEGER NOT NULL,"
		"height INTEGER NOT NULL,"
		"\"object type\" TEXT NOT NULL,"
		"\"R avg\" REAL NOT NULL,"
		"\"G avg\" REAL NOT NULL,"
		"\"B avg\" REAL NOT NULL);";

	return sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr) == SQLITE_OK;
}

bool SQLHandler::insertData(Rect rect, FrameWrap& frameWarp, const string& objectType, float R, float G, float B) {
	char insertDataQuery[256];
	snprintf(insertDataQuery, sizeof(insertDataQuery),
		"INSERT INTO MyTable (timestamp,\"frame number\","
		" \"Top left X\",\"Top left Y\","
		"width, height, \"object type\", "
		"\"R avg\", \"G avg\", \"B avg\") "
		"VALUES ('%s', %d, %d, %d, %d, %d, '%s', %lf, %lf, %lf);",
		frameWarp.timestamp.c_str(), frameWarp.frameNumber, rect.x, rect.y, rect.width, rect.height,
		objectType.c_str(), R, G, B);

	return sqlite3_exec(db, insertDataQuery, nullptr, nullptr, nullptr) == SQLITE_OK;
}

void SQLHandler::selectMaxID() {
	const char* selectDataQuery = "SELECT * FROM MyTable WHERE ID = (SELECT MAX(ID) FROM MyTable);";
	//sqlite3_exec(db, selectDataQuery, callbackFunction, nullptr, nullptr);
}

int SQLHandler::callbackFunction(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; ++i) {
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
	}
	cout << endl;
	return 0;
}

void SQLHandler::printTable() {
	const char* selectAllQuery = "SELECT * FROM MyTable;";
	sqlite3_exec(db, selectAllQuery, callbackFunction, nullptr, nullptr);
}

bool SQLHandler::cleanDataBase() {

	const char* dropTableQuery = "DROP TABLE IF EXISTS MyTable;";

	return sqlite3_exec(db, dropTableQuery, nullptr, nullptr, nullptr) == SQLITE_OK;
}

sqlite3* SQLHandler::getDB() {
	return db;
}