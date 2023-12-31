#include "SQLHandler.h"
using namespace cv;

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
		"\"frame_number\" INT NOT NULL,"
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
	//cout << "frameWarp.timestamp in insert func" << frameWarp.timestamp << endl;
	snprintf(insertDataQuery, sizeof(insertDataQuery),
		"INSERT INTO MyTable (timestamp,\"frame_number\","
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
	return 0;
}

void SQLHandler::printTable() {
	const char* selectAllQuery = "SELECT * FROM MyTable;";
	sqlite3_exec(db, selectAllQuery, callbackFunction, nullptr, nullptr);
}



GetFromDataBase* SQLHandler::getRow(int rowID, GetFromDataBase& getDb) {
	char selectColumnQuery[128];
	snprintf(selectColumnQuery, sizeof(selectColumnQuery),
		"SELECT * FROM MyTable WHERE ID = %d;", rowID);

	vector<GetFromDataBase> Datab;

	int result = sqlite3_exec(db, selectColumnQuery, [](void* data, int argc, char** argv, char** azColName) -> int {
		if (argc >= 7) { // Make sure you have at least 7 columns in the query result
			GetFromDataBase getDbInto;
			getDbInto.id = atoi(argv[0]);
			getDbInto.time = argv[1];
			getDbInto.fw.frameNumber = atoi(argv[2]);
			getDbInto.rect.x = atoi(argv[3]);
			getDbInto.rect.y = atoi(argv[4]);
			getDbInto.rect.width = atoi(argv[5]);
			getDbInto.rect.height = atoi(argv[6]);
			getDbInto.typeObject = argv[7];
			getDbInto.r = stof(argv[8]);
			getDbInto.g = stof(argv[9]);
			getDbInto.b = stof(argv[10]);
			reinterpret_cast<vector<GetFromDataBase>*>(data)->push_back(getDbInto);
		}
		return 0;
		}, &Datab, nullptr);

	if (result != SQLITE_OK) {
		cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
		return nullptr;
	}

	if (!Datab.empty()) {
		getDb = Datab[0];
		return &getDb;

		return nullptr;
	}
	return nullptr;
}

bool SQLHandler::cleanDataBase(){
	const char* dropTableQuery = "DROP TABLE IF EXISTS MyTable;";
	return sqlite3_exec(db, dropTableQuery, nullptr, nullptr, nullptr) == SQLITE_OK;
}

sqlite3* SQLHandler::getDB() {
	return db;
}

bool SQLHandler::isObjectExistsInLastRecordsQuery(Rect& rect) {
	// Calculate the middle point of the given rectangle
	int middleX = rect.x + (rect.width / 2);
	int middleY = rect.y + (rect.height / 2);

	// Query to retrieve the rectangles from the last 100 records
	const char* selectLast100RecordsQuery = "SELECT * FROM MyTable ORDER BY ID DESC LIMIT 100;";

	struct RectInfo {
		int leftX;
		int topY;
		int width;
		int height;
	};

	vector<RectInfo> last100RecordsQuery;

	// Define a lambda function to process query results
	auto processQueryResults = [](void* data, int argc, char** argv, char** azColName) -> int {
		if (argc >= 7) { // Make sure you have at least 7 columns in the query result
			RectInfo rectInfo;
			rectInfo.leftX = atoi(argv[3]);
			rectInfo.topY = atoi(argv[4]);
			rectInfo.width = atoi(argv[5]); // Calculate rightX from width
			rectInfo.height = atoi(argv[6]); // Calculate bottomY from height
			reinterpret_cast<vector<RectInfo>*>(data)->push_back(rectInfo);
		}
		return 0;
	};

	int result = sqlite3_exec(db, selectLast100RecordsQuery, processQueryResults, &last100RecordsQuery, nullptr);

	if (result != SQLITE_OK) {
		//cout << "Error occurred while retrieving data" << endl;
		Logger::Error("Error occurred while retrieving data");
		return false;
	}

	// Check if the middle point is inside any of the last 100 records' rectangles
	for (const RectInfo& rectInfo : last100RecordsQuery) {
		if (middleX >= rectInfo.leftX && middleX <= (rectInfo.leftX + rectInfo.width) &&
			middleY >= rectInfo.topY && middleY <= (rectInfo.topY + rectInfo.height)) {
			return true;
		}
	}

	//cout << "Middle point is not inside any rectangle" << endl;
	return false;
}
