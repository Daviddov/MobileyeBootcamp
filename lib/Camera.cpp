#include "Camera.h" 


//c'tor
CameraProcessor::CameraProcessor(queue<FrameWrap>& queue, int id, string _path) : dataFromCamera(queue) {
	countFrame = 0;
	active = true;
	cameraId = id;
	path = _path;
	numFramesCheck = 0;
	frameDiffThreshold = 0.0;
}

//d'tor
CameraProcessor::~CameraProcessor() {
	capture.release();
}

bool CameraProcessor::calcAbsDiff() {
	Mat diff;
	absdiff(prev, frameWarp.image, diff);

	//convert diff to gray because countNonZero func can't to resive COLOR_IMG 
	cvtColor(diff, diff, COLOR_BGR2GRAY);
	double normalRes = (double)(countNonZero(diff)) / (double)(frameWarp.image.cols * frameWarp.image.rows);

	return frameDiffThreshold < normalRes;
}

bool CameraProcessor::init(int numFrames, double frame_diff) {

	numFramesCheck = numFrames;

	frameDiffThreshold = frame_diff;

	capture.open(path);

	if (!capture.isOpened()) {
		Logger::Error("Error opening video file");
		return false;
	}
	Logger::Info("Video file is opening ");
	capture.read(frameWarp.image);
	insertToQueue();
	return true;
}

void CameraProcessor::insertToQueue() {

	frameWarp.frameNumber = ++countFrame;

	frameWarp.timestamp = currentTime();

	FrameWrap temp = frameWarp;
	temp.image = frameWarp.image.clone();
	dataFromCamera.push(temp);

	prev = frameWarp.image.clone();
}

void CameraProcessor::run() {

	while (active) {

		capture.read(frameWarp.image);
		//countFrame++;

		if (frameWarp.image.empty()) {
			cout << "End of stream\n";
			Logger::Info("End of stream");
			break;
		}
		if (++countFrame % numFramesCheck == 0 && calcAbsDiff()) {
			Logger::Info("wait 0.3 second");
			this_thread::sleep_for(chrono::milliseconds(333));
			insertToQueue();
			Logger::Info("insert to queue");
		}
		else {
			continue;
		}
	}
}

string currentTime() {

	auto timestamp = chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch()
	).count();

	int milliseconds = timestamp % 1000;

	time_t time_t_timestamp = timestamp / 1000;

	tm timeinfo;
	localtime_s(&timeinfo, &time_t_timestamp);

	char buffer[28];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

	sprintf_s(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), ":%03d", milliseconds);

	string formatted_time = buffer;
	Logger::Info("the time camera is %s", formatted_time);
	return formatted_time;
}

void CameraProcessor::cameraPart(CameraProcessor* camera) {


	//the user input it using Qt
	int numFrames = 30;

	//the user input it using Qt
	double frameDiffThreshold = 0.9;

	if (!camera->init(numFrames, frameDiffThreshold))
	{
		Logger::Critical("the path is not found");
		return;
	}

	camera->run();
}

//this nedded for test.cpp 
void CameraProcessor::setFrame(Mat f) {
	frameWarp.image = f;
}
//this nedded for test.cpp 
void CameraProcessor::setPrev(Mat p) {
	prev = p;
}
//this nedded for test.cpp
void CameraProcessor::setFrameDiffThreshold(double frameDiff) {
	frameDiffThreshold = frameDiff;
}

int CameraProcessor::getId() {
	return cameraId;
}