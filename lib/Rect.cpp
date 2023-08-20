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
		//add logger??
		cout << "width" <<frame.image.cols  << "hight" << frame.image.rows << "x" << box.x << "y"<<box.y<<endl;	
		
		//Modify x and y for don't overflow from original frame.
		box.x < 0 ? box.x = 0 : box.x = box.x;
		box.y < 0 ? box.y = 0 : box.y = box.y;
		box.x > 20 ? box.x -= 20 : box.x = box.x;
		box.y > 20 ? box.y -= 20 : box.y = box.y;
		writeRectOnDB( box, class_list[classId]);
	}
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
		cerr << "Failed to " << what << endl;
		sqlite3_close(db);
		return true;
	}
	return false;
}
///


void YoloRect::writeRectOnDB(Rect rect, string objectType) {
	Mat imgFromRect = frame.image(rect);

	if (imgFromRect.empty()) {
		cerr << "Failed to extract image from rectangle." << endl;
		return;
	}

	float R = 0, G = 0, B = 0;
	calcAvgPerChannel(imgFromRect, &R, &G, &B);

	if (!sqlHandler.open("rect_data.db")) {
		cerr << "Failed to open database." << endl;
		return;
	}

	bool success = false;
	if (sqlHandler.createTableIfNotExists()) {
		success = sqlHandler.insertData(rect, frame, objectType, R, G, B);
	}

	if (success) {
		sqlHandler.selectMaxID();
	}

	sqlHandler.deleteTable();
	sqlHandler.close();
}
