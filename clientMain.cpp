
//#include "Header.h"
#include "CameraProcessor.h"
#include "ConfigurationManager.h"


int main() {
	ConfigurationManager configManager("config.json");
	
	// Retrieve the "cameraThreshold" field as a double
	double frameDiff = configManager.getFieldValue<double>("cameraThreshold");
	int numFrames = configManager.getFieldValue<int>("numFrames");
	string videoPath = configManager.getFieldValue<string>("videoPath");
	
	//log init
	LogPriority priority = InfoPriority;
	mutex logMutex;
	Logger::EnableFileOutput();

	Logger::Info("the camera process is started");

	CameraProcessor camera(videoPath, numFrames, frameDiff);
	if (!camera.capture.isOpened()) {
		Logger::Critical("Error opening video file");
		return 1;
	}
	camera.run();
	Logger::Info("the camera process is finised");

	return 0;
}