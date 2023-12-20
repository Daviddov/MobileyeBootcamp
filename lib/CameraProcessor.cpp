#include "CameraProcessor.h" 
#include "ConfigurationManager.h"
#include "CameraConnectionManager.h"
#include "IPAddressFinder.h"

using namespace cv;

//c'tor
CameraProcessor::CameraProcessor(string path, int numFrames, double frameDiff) {
	countFrame = 0;
	countSend = 0;
	active = true;
	capture.open(path); 
	numFramesCheck = numFrames;
	frameDiffThreshold = frameDiff;
}
CameraProcessor::CameraProcessor(int cameraID, int numFrames, double frameDiff) {
	countFrame = 0;
	countSend = 0;
	active = true;
	capture.open(cameraID); //for web camera index 0
	numFramesCheck = numFrames;
	frameDiffThreshold = frameDiff;
}
//d'tor
CameraProcessor::~CameraProcessor() {
	capture.release();
}

bool CameraProcessor::calcAbsDiff() {
	Mat diff;
	absdiff(prev, frameWrap.image, diff);

	//convert diff to gray because countNonZero func can't to resive COLOR_IMG 
	cvtColor(diff, diff, COLOR_BGR2GRAY);
	double normalRes = (double)(countNonZero(diff)) / (double)(frameWrap.image.cols * frameWrap.image.rows);

	return frameDiffThreshold < normalRes;
}

void CameraProcessor::run() {
	ConfigurationManager & configManager = ConfigurationManager::getInstance(); 
	string cameraPort = configManager.getFieldValue<string>("backendPort");
	//string localIPv4 = configManager.getFieldValue<string>("backendIP");

	IPAddressFinder ipAddressFinder;

	std::string localIPv4 = ipAddressFinder.getLocalIPv4Address();

	if (!localIPv4.empty()) {
		std::cout << "Local IPv4 Address: " << localIPv4 << std::endl;
	}
	else {
		std::cerr << "Unable to determine local IPv4 address." << std::endl;
	}
	string camera_address = localIPv4 + ":" + cameraPort;


	CameraConnectionManager connect(camera_address);

	while (active) {

		if (connect.countTryToConnect > 4) {
			Logger::Info("camera stoped, no connection");
			break;
		}
		capture.read(frameWrap.image);

		if (frameWrap.image.empty()) {
	
			Logger::Info("End of stream");
			break;
		}

		if (++countFrame == 1 || (countFrame % numFramesCheck == 0 && calcAbsDiff())) {
			prev = frameWrap.image.clone();
			frameWrap.timestamp = currentTime();
			frameWrap.frameNumber = countFrame;
			connect.sendToServer(frameWrap);
			 countSend++;
			/* Size size(800, 600);
			 resize(frameWrap.image, frameWrap.image, size, CV_8UC3),
				 cv::imshow("output", frameWrap.image);*/

			 if (waitKeyEx(1) == 27) {

				 Logger::Info("part server finished by user");
				 break;
			 }
			Logger::Info("counter Send:",countSend);
			Logger::Info("wait 0.6 second");
			this_thread::sleep_for(chrono::milliseconds(666));
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

	//std::cout << "The time is " << formatted_time.str() << std::endl;  // Replace with your logging mechanism
	return formatted_time.str();
}

void CameraProcessor::setFrame(Mat p) {
	frameWrap.image = p;
};

void CameraProcessor::setPrev(Mat& p) {
	prev = p;
};

