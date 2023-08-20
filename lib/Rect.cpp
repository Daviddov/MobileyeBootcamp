#include "Rect.h"

//c'tor
YoloRect::YoloRect(FrameWrap& frameW, vector<Detection>& outputP, vector<string>& class_listP) :frame(frameW), output(outputP), class_list(class_listP)
{
	colors = { Scalar(255, 255, 0),Scalar(0, 255, 0),Scalar(0, 255, 255),Scalar(255, 0, 0) };
}

void YoloRect::toDrawRect() {

	for (int i = 0; i < output.size(); ++i)
	{
		auto box = output[i].box;
		auto classId = output[i].class_id;
		const auto color = colors[classId % colors.size()];
		rectangle(frame.image, box, color, 3);
		rectangle(frame.image, Point(box.x, box.y - 5), Point(box.x + box.width, box.y), color, FILLED);
		putText(frame.image, class_list[classId].c_str(), Point(box.x, box.y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
		
		Logger::Debug("origin frame width is %d hight is %d ", frame.image.cols, frame.image.rows);
		Logger::Debug("Top left x is %d Top left y is %d ", box.x, box.y);
		Logger::Debug("Box width is %d Box hight is %d ", box.width, box.height);

		//Modify x and y for don't overflow from original frame.
		box.x < 0 ? box.x = 0 : box.x ;
		box.y < 0 ? box.y = 0 : box.y ;
		box.x > 20 ? box.x -= 20 : box.x;
		box.y > 20 ? box.y -= 20 : box.y;

		writeRectOnDB( box, class_list[classId]);
	}
}

void YoloRect::writeRectOnDB(Rect rect, string objectType) {

	Mat imgFromRect = frame.image(rect);

	float R = 0, G = 0, B = 0;
	calcAvgPerChannel(imgFromRect, &R, &G, &B);

	sqlite3* db;

	int rc = sqlite3_open("rect_data.db", &db);

	if (handleDBError(rc, db, "open db")) { return; }

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

	rc = sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);

	if (handleDBError(rc, db, "creat table")) { return; }

	char insertDataQuery[256];
	sprintf_s(insertDataQuery, sizeof(insertDataQuery),
		"INSERT INTO MyTable (timestamp,\"frame number\","
		" \"Top left X\",\"Top left Y\","
		"width, height, \"object type\", "
		"\"R avg\", \"G avg\", \"B avg\") "
		"VALUES ('%s', %d, %d, %d, %d, %d, '%s', %lf, %lf, %lf);",
		frame.timestamp.c_str(), frame.frameNamber, rect.x, rect.y, rect.width, rect.height, objectType.c_str(), R, G, B);

	rc = sqlite3_exec(db, insertDataQuery, nullptr, nullptr, nullptr);

	if (handleDBError(rc, db, "insert")) { return; }

	const char* selectDataQuery = "SELECT * FROM MyTable WHERE ID = (SELECT MAX(ID) FROM MyTable);";
	rc = sqlite3_exec(db, selectDataQuery, callbackFunction, nullptr, nullptr);

	if (handleDBError(rc, db, "select query")) { return; }

	const char* deleteTableQuery = "DELETE FROM MyTable;";

	rc = sqlite3_exec(db, deleteTableQuery, nullptr, nullptr, nullptr);
	sqlite3_close(db);
}

void YoloRect::calcAvgPerChannel(const Mat& img, float* B, float* G, float* R) {

	float sumB = 0, sumG = 0, sumR = 0;
	for (int row = 0; row < img.rows; row++) {
		for (int col = 0; col < img.cols; col++) {
			const uchar* row_data = img.ptr(row);
			sumB += row_data[(col * 3) + 0];
			sumG += row_data[(col * 3) + 1];
			sumR += row_data[(col * 3) + 2];
		}
	}
	int size = img.rows * img.cols;
	*B = sumB / size;
	*G = sumG / size;
	*R = sumR / size;
}

int YoloRect::callbackFunction(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; ++i) {
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
	}
	cout << endl;
	return 0;
}

bool YoloRect::handleDBError(int failed, sqlite3* db, string what) {
	if (failed != SQLITE_OK) {
		Logger::Error("Failed to %s", what);
		sqlite3_close(db);
		return true;
	}
	return false;
}
