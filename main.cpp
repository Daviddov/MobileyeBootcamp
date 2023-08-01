#include "Header.h"
// Problems: 1 The time that should be written on the file is Incorrect .lines: 261 ,263 ,296 ,114 ,124,209 227.

void detect_with_YOLO5(Mat currFrame, double timestamp) {

	dnn::Net net;

	load_net(net);

	vector<string> class_list = load_class_list();

	vector<Detection> output;

	detect(currFrame, net, output, class_list);

	toDrawRect(currFrame, output, class_list, timestamp);
}

vector<string> load_class_list()
{
	vector<string> class_list;
	ifstream ifs("./assets/classes.txt");
	string line;
	while (getline(ifs, line))
	{
		class_list.push_back(line);
	}
	return class_list;
}

void load_net(cv::dnn::Net& net)
{
	auto result = dnn::readNet("./assets/yolov5s.onnx");

	cout << "Running on CPU\n";
	result.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	result.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

	net = result;
}

Mat format_yolov5(const Mat& src) {

	int _max = MAX(src.cols, src.rows);
	Mat result = Mat::zeros(_max, _max, CV_8UC3);
	src.copyTo(result(Rect(0, 0, src.cols, src.rows)));
	return result;
}

void detect(Mat& image, dnn::Net& net, vector<Detection>& output, const vector<string>& className) {

	const float INPUT_WIDTH = 640.0;
	const float INPUT_HEIGHT = 640.0;
	const float SCORE_THRESHOLD = 0.2;
	const float NMS_THRESHOLD = 0.4;
	const float CONFIDENCE_THRESHOLD = 0.4;

	Mat blob;

	auto input_image = format_yolov5(image);

	dnn::blobFromImage(input_image, blob, 1. / 255., Size(INPUT_WIDTH, INPUT_HEIGHT), Scalar(), true, false);

	net.setInput(blob);
	vector<Mat> outputs;
	net.forward(outputs, net.getUnconnectedOutLayersNames());

	float x_factor = input_image.cols / INPUT_WIDTH;
	float y_factor = input_image.rows / INPUT_HEIGHT;

	float* data = (float*)outputs[0].data;


	vector<int> class_ids;
	vector<float> confidences;
	vector<Rect> boxes;

	const int NUM_OF_DETECT = 25200;
	const int NUM_OF_DATA = 85;

	for (int i = 0; i < NUM_OF_DETECT; ++i) {

		float confidence = data[4];
		if (confidence >= CONFIDENCE_THRESHOLD) {

			float* classes_scores = data + 5;
			Mat scores(1, className.size(), CV_32FC1, classes_scores);
			Point class_id;
			double max_class_score;

			minMaxLoc(scores, 0, &max_class_score, 0, &class_id);

			if (max_class_score > SCORE_THRESHOLD && (class_id.x == 2 || class_id.x == 3 || class_id.x == 5 || class_id.x == 7)) {

				confidences.push_back(confidence);

				class_ids.push_back(class_id.x);

				float x = data[0];
				float y = data[1];
				float w = data[2];
				float h = data[3];

				int left = int((x - 0.5 * w) * x_factor);
				int top = int((y - 0.5 * h) * y_factor);
				int width = int(w * x_factor);
				int height = int(h * y_factor);
				boxes.push_back(Rect(left, top, width, height));
			}
		}
		data += NUM_OF_DATA;
	}

	vector<int> nms_result;
	dnn::NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, nms_result);
	for (int i = 0; i < nms_result.size(); i++) {
		int idx = nms_result[i];
		Detection result;
		result.class_id = class_ids[idx];
		result.confidence = confidences[idx];
		result.box = boxes[idx];
		output.push_back(result);
	}
}

void toDrawRect(Mat& image, vector<Detection>& output, const vector<string>& className, double timestamp) {

	const vector<Scalar> colors = { Scalar(255, 255, 0),Scalar(0, 255, 0),Scalar(0, 255, 255),Scalar(255, 0, 0) };

	for (int i = 0; i < output.size(); ++i)
	{
		auto box = output[i].box;
		auto classId = output[i].class_id;
		const auto color = colors[classId % colors.size()];
		rectangle(image, box, color, 3);
		rectangle(image, Point(box.x, box.y - 5), Point(box.x + box.width, box.y), color, FILLED);
		putText(image, className[classId].c_str(), Point(box.x, box.y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));

		//Modify x and y for don't overflow from original frame.
		box.x > 20 ? box.x -= 20 : box.x = box.x;
		box.y > 20 ? box.y -= 20 : box.y = box.y;
		writeRectOnDB(image, box, timestamp, className[classId]);
	}
}

bool calcAbsDiff(const Mat& image1, const Mat& image2) {

	Mat diff;
	absdiff(image1, image2, diff);

	//convert diff to gray because countNonZero func can't to resive COLOR_IMG 
	cvtColor(diff, diff, COLOR_BGR2GRAY);

	return 0.9 < ((double)(countNonZero(diff)) / (double)(image1.cols * image1.rows));

}

void calcAvgPerChanel(const Mat& img, float* B, float* G, float* R) {

	float sumB = 0, sumG = 0, sumR = 0;
	//
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

static int callbackFunction(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; ++i) {
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
	}
	cout << endl;
	return 0;
}

bool handleDBError(int failed, sqlite3* db, string what) {
	if (failed != SQLITE_OK) {
		cerr << "Failed to " << what << endl;
		sqlite3_close(db);
		return true;
	}
	return false;
}

void writeRectOnDB(const Mat& org, Rect rect, double timestamp1, string objectType) {

	Mat imgFromRect = org(rect);

	float R = 0, G = 0, B = 0;
	calcAvgPerChanel(imgFromRect, &R, &G, &B);

	sqlite3* db;

	string timestamp = "10:32";


	int rc = sqlite3_open("rect_data.db", &db);

	if (handleDBError(rc, db, "open db")) { return; }


	const char* createTableQuery = "CREATE TABLE IF NOT EXISTS MyTable ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"timestamp TEXT NOT NULL,"
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
		"INSERT INTO MyTable (timestamp,"
		" \"Top left X\",\"Top left Y\","
		"width, height, \"object type\", "
		"\"R avg\", \"G avg\", \"B avg\") "
		"VALUES ('%s', %d, %d, %d, %d, '%s', %lf, %lf, %lf);",
		timestamp.c_str(), rect.x, rect.y, rect.width, rect.height, objectType.c_str(), R, G, B);

	rc = sqlite3_exec(db, insertDataQuery, nullptr, nullptr, nullptr);

	if (handleDBError(rc, db, "insert")) { return; }

	const char* selectDataQuery = "SELECT * FROM MyTable WHERE ID = (SELECT MAX(ID) FROM MyTable);";

	//!!!this line to print all the DB evrey time that function called!!!.
	rc = sqlite3_exec(db, selectDataQuery, callbackFunction, nullptr, nullptr);

	if (handleDBError(rc, db, "select query")) { return; }

	sqlite3_close(db);
}

int main() {

	queue<Mat> dataFromCamera;

	Mat frame;
	VideoCapture capture(R"(./assets/parking.mp4)");
	if (!capture.isOpened())
	{
		cerr << "\nError opening video file\n";
		return 1;
	}

	capture.read(frame);
	dataFromCamera.push(frame.clone());

	int count_frames = 0;

	while (true)
	{
		capture.read(frame);
		auto timestamp = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

		if (frame.empty())
		{
			cout << "End of stream\n";
			break;
		}

		count_frames++;
		if (count_frames % 30 != 0 && calcAbsDiff(dataFromCamera.back(), frame))
		{
			continue;
		}
		dataFromCamera.push(frame.clone());

		Mat currFrame = dataFromCamera.front();

		dataFromCamera.pop();

		detect_with_YOLO5(currFrame, timestamp);

		imshow("output", currFrame);

		if (waitKey(1) == 27)
		{
			capture.release();
			cout << "finished by user\n";
			break;
		}
	}
	return 0;
}



