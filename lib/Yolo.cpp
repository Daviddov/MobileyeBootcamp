#include "Yolo.h"

Yolo5::Yolo5(FrameWrap& frameW):frameWarp(frameW)
{
	cout << "start yolo load: " << currentTime() << endl;

	load_net();
	load_class_list();

	cout << "end yolo load : " << currentTime() << endl;

}

void Yolo5::load_class_list()
{
	ifstream ifs("./assets/classes.txt");
	string line;
	while (getline(ifs, line))
	{
		class_list.push_back(line);
	}
	Logger::Info("the class list of yolo is readed");
}

void Yolo5::load_net()
{
	auto result = dnn::readNet("./assets/yolov5s.onnx");

	cout << "Running on CPU\n";
	result.setPreferableBackend(dnn::DNN_BACKEND_OPENCV);
	result.setPreferableTarget(dnn::DNN_TARGET_CPU);

	net = result;
}

Mat Yolo5::format_yolov5() {
	int _max = MAX(frameWarp.image.cols, frameWarp.image.rows);
	Mat result = Mat::zeros(_max, _max, CV_8UC3);
	frameWarp.image.copyTo(result(Rect(0, 0, frameWarp.image.cols, frameWarp.image.rows)));
	return result;
}

void Yolo5::detect() {
	

	const float INPUT_WIDTH = 640.0f;
	const float INPUT_HEIGHT = 640.0f;
	const float SCORE_THRESHOLD = 0.2f;
	const float NMS_THRESHOLD = 0.4f;
	const float CONFIDENCE_THRESHOLD = 0.4f;

	Mat blob;

	auto input_image = format_yolov5();
	cout << "blob func start: " << currentTime() << endl;

	dnn::blobFromImage(input_image, blob, 1. / 255., Size(INPUT_WIDTH, INPUT_HEIGHT), Scalar(), true, false);
	cout << "blob func end: " << currentTime() << endl;
	cout << "setinput func start: " << currentTime() << endl;

	net.setInput(blob);
	cout << "setinput func end: " << currentTime() << endl;

	vector<Mat> outputs;
	cout << "forward func start: " << currentTime() << endl;

	net.forward(outputs, net.getUnconnectedOutLayersNames());
	cout << "forward func end: " << currentTime() << endl;

	float x_factor = input_image.cols / INPUT_WIDTH;
	float y_factor = input_image.rows / INPUT_HEIGHT;

	float* data = (float*)outputs[0].data;


	vector<int> class_ids;
	vector<float> confidences;
	vector<Rect> boxes;

	const int NUM_OF_DETECT = 25200;
	const int NUM_OF_DATA = 85;
	cout << "big for start: " << currentTime() << endl;

	for (int i = 0; i < NUM_OF_DETECT; ++i) {

		float confidence = data[4];
		if (confidence >= CONFIDENCE_THRESHOLD) {

			float* classes_scores = data + 5;
			Mat scores(1, class_list.size(), CV_32FC1, classes_scores);
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
	cout << "big for end: " << currentTime() << endl;
	cout << "mms boxxes start: " << currentTime() << endl;

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
	cout << "mms boxxes end: " << currentTime() << endl;

}

vector<Detection>& Yolo5::getOutput() {
	return output;
}

vector<string>& Yolo5::getClassList() {
	return class_list;
}