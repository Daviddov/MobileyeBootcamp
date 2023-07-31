#include "Header.h"

// Problems: 1 The time that should be written on the file is Incorrect .lines: 261 ,263 ,296 ,114 ,124,209 227.
//           2 The header should be written on the file to writing every time when program get start . lines: 256 , 228.

const float INPUT_WIDTH = 640.0;
const float INPUT_HEIGHT = 640.0;
const float SCORE_THRESHOLD = 0.2;
const float NMS_THRESHOLD = 0.4;
const float CONFIDENCE_THRESHOLD = 0.4;

const vector<Scalar> colors = {
	Scalar(255, 255, 0),
	Scalar(0, 255, 0),
	Scalar(0, 255, 255),
	Scalar(255, 0, 0)
};

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
	for (int i = 0; i < output.size(); ++i)
	{
		auto box = output[i].box;
		auto classId = output[i].class_id;
		const auto color = colors[classId % colors.size()];
		rectangle(image, box, color, 3);
		rectangle(image, Point(box.x, box.y - 20), Point(box.x + box.width, box.y), color, FILLED);
		putText(image, className[classId].c_str(), Point(box.x, box.y - 5), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));

		writeRectOnCSV(image, box, timestamp, className[classId]);
	}

	cout << "output.size: " << output.size() << endl;
}

bool calcAbsDiff(const Mat& image1, const Mat& image2) {

	for (size_t i = 0; i < 8; i++)
	{
		cout << "?????????????????????????????????????????????????????????????????????????????????\n";
	}
	cout << "\n";
	Mat diff;
	absdiff(image1, image2, diff);
	//convert diff to gray for countNonZero func can to read it 
	cvtColor(diff, diff, COLOR_BGR2GRAY);
	return 0.8 < ((double)(countNonZero(diff)) / (double)(image1.cols * image1.rows));

}

//void cameraPart(queue<Mat>& queue) {
//
//	Mat frame;
//
//	//queue<Mat> queue;
//
//	//VideoCapture capture(R"(C:\Users\1\Pictures\Camera Roll\WIN_20230724_18_39_27_Pro.mp4)");
//	//VideoCapture capture(R"(C:\Users\1\Desktop\movie\parking.mp4)");
//	VideoCapture capture(R"(C:\Users\1\Desktop\movie\police.mp4)");
//
//	if (!capture.isOpened())
//	{
//		cerr << "Error opening video file\n";
//		return;
//	}
//
//	char key = 0;
//
//	while (key != 27) {
//		capture.read(frame);
//		if (frame.empty())
//		{
//			cout << "End of stream\n";
//			break;
//		}
//
//		if (queue.empty() || (calcAbsDiff(queue.back(), frame)) > 3.0);
//		{
//			queue.push(frame.clone());
//		}
//		this_thread::sleep_for(chrono::milliseconds(1));
//
//		key = waitKey(1);
//	}
//}

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

void writeHeaderToFile() {
	ofstream csvfile("./assets/my_file.csv", ios::app);
	csvfile << "Time, Top, Left, Width, Height,object type , AvgR, AvgG, AvgB" << std::endl;
	csvfile.close();
}

void writeRectOnCSV(const Mat& org, Rect rect, double timestamp, string objectType) {
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

	cout << "rect.y" << rect.y << "rect.x " << rect.x << "rect.width" << rect.width << "rect.height" << rect.height << endl;
	cout << "org.cols" << org.cols << "org.rows" << org.rows << objectType << endl;

	rect.x > 20 ? rect.x -= 20 : rect.x = rect.x;
	rect.y > 20 ? rect.y -= 20 : rect.y = rect.y;

	Mat imgFromRect = org(rect);

	float R = 0, G = 0, B = 0;
	calcAvgPerChanel(imgFromRect, &R, &G, &B);

	string path = "./assets/my_file.csv";

	ofstream csvfile(path, ios::app);
	//          
	csvfile << timestamp << "," << rect.y << "," << rect.x << "," << rect.width << "," << rect.height << "," << objectType << "," << R << "," << G << "," << B << endl;

	csvfile.close();
}

int main() {

	queue<Mat> dataFromCamera;


	Mat frame;
	//VideoCapture capture(R"(C:\Users\1\Pictures\Camera Roll\WIN_20230724_18_39_27_Pro.mp4)");
	VideoCapture capture("./assets/Camera_Parkng.mp4");
	//VideoCapture capture(R"(C:\Users\1\Desktop\project_files\parking.mp4)");
	//VideoCapture capture(0);

	if (!capture.isOpened())
	{
		cerr << "Error opening video file\n";
		return 1;
	}
	capture.read(frame);
	dataFromCamera.push(frame.clone());

	auto start = chrono::high_resolution_clock::now();
	int total_frames = 0;

	writeHeaderToFile();

	int countDenied = 0;

	while (true)
	{
		capture.read(frame);

		auto currentTime = chrono::system_clock::now();

		auto timestamp = chrono::duration_cast<chrono::milliseconds>(currentTime.time_since_epoch()).count();

		if (frame.empty())
		{
			cout << "End of stream\n";
			break;
		}

		if (calcAbsDiff(dataFromCamera.back(), frame))
		{
			dataFromCamera.push(frame.clone());
			cout << "Denied: " << countDenied << endl;
			countDenied = 0;
		}
		else
		{
			countDenied++;
			continue;
		}

		total_frames++;

		Mat currFrame = dataFromCamera.front();

		dataFromCamera.pop();

		dnn::Net net;

		load_net(net);

		vector<string> class_list = load_class_list();

		vector<Detection> output;

		detect(currFrame, net, output, class_list);

		toDrawRect(currFrame, output, class_list, timestamp);

		imshow("output", currFrame);

		if (waitKey(1) == 27)
		{
			capture.release();
			cout << "finished by user\n";
			break;
		}
		cout << "Total frames: " << total_frames << "\n";
	}
	return 0;
}



