#include "SQLHandler.h"


//c'tor
SQLHandler::SQLHandler() : db(nullptr) {
	if (!open("rect_data.db")) {
		Logger::Error("Failed to open database.");
		return;
	}
	if (!cleanDataBase()) {
		Logger::Error("Failed to clean database.");
		return;
	}
	Logger::Info("To cleaned database.");
}

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
	sqlite3_exec(db, selectDataQuery, callbackFunction, nullptr, nullptr);
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


bool SQLHandler::checkRectExistsInLastFrame(Rect rect) {
	// Calculate the middle point of the given rectangle
	int middleX = rect.x + (rect.width / 2);
	int middleY = rect.y + (rect.height / 2);

	// Retrieve the rectangles from the last timestamp
	const char* selectLastTimestampRectsQuery = "SELECT * FROM MyTable WHERE timestamp = (SELECT MAX(timestamp) FROM MyTable);";

	struct RectInfo {
		int leftX;
		int topY;
		int width;
		int height;
	};

	std::vector<RectInfo> lastTimestampRects;

	int result = sqlite3_exec(db, selectLastTimestampRectsQuery, [](void* data, int argc, char** argv, char** azColName) -> int {
		if (argc >= 7) { // Make sure you have at least 7 columns in the query result
			RectInfo rectInfo;
			rectInfo.leftX = std::atoi(argv[3]);
			rectInfo.topY = std::atoi(argv[4]);
			rectInfo.width = std::atoi(argv[5]); // Calculate rightX from width
			rectInfo.height = std::atoi(argv[6]); // Calculate bottomY from height
			reinterpret_cast<std::vector<RectInfo>*>(data)->push_back(rectInfo);
		}
		return 0;
		}, &lastTimestampRects, nullptr);

	if (result != SQLITE_OK) {
		cout << "Error occurred while retrieving data" << endl;
		return false;
	}

	// Check if the middle point is inside any of the last timestamp's rectangles
	for (const RectInfo& rectInfo : lastTimestampRects) {
		//cout << "Checking rectangle: (" << rectInfo.leftX << "," << rectInfo.topY << "," << rectInfo.width << "," << rectInfo.height << ")" << endl;
		if (middleX >= rectInfo.leftX && middleX <= rectInfo.leftX + rectInfo.width &&
			middleY >= rectInfo.topY && middleY <= rectInfo.topY + rectInfo.height) {
			//cout << "Middle point is inside a rectangle" << endl;
			return true;
		}
	}

	cout << "Middle point is not inside any rectangle" << endl;
	return false;
}

