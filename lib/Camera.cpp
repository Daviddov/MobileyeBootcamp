#include "Camera.h" 


//c'tor
CameraProcessor::CameraProcessor(Queue<FrameWrap>& queue, int id, string _path) :
	dataFromCamera(queue) ,cameraId (id) ,path  (_path) {
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

std::string currentTime() {
	auto now = std::chrono::system_clock::now();
	auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
		now.time_since_epoch()
	);

	auto milliseconds = timestamp % 1000;

	auto time_t_timestamp = std::chrono::duration_cast<std::chrono::seconds>(
		timestamp
	).count();

	std::time_t time_t_timestamp_t = static_cast<std::time_t>(time_t_timestamp);

	std::tm timeinfo;
	// Use localtime or gmtime depending on your requirement
#ifdef _WIN32
	localtime_s(&timeinfo, &time_t_timestamp_t);
#else
	localtime_r(&time_t_timestamp_t, &timeinfo);
#endif

	char buffer[28];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

	std::ostringstream formatted_time;
	formatted_time << buffer << ":" << std::setfill('0') << std::setw(3) << milliseconds.count();

	std::cout << "The time is " << formatted_time.str() << std::endl;  // Replace with your logging mechanism
	return formatted_time.str();
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