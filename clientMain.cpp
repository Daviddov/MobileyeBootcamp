
#include "Header.h"
#include "CameraProcessor.h"
#include "ConfigurationManager.h"


int main() {
	ConfigurationManager configManager;
	
	// Retrieve the "cameraThreshold" field as a double
	double frameDiff = configManager.getFieldValue<double>("cameraThreshold");
	int numFrames = configManager.getFieldValue<int>("numFrames");

	string path = "assets/parking.mp4";

	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();

	Logger::Info("the camera process is started");

	CameraProcessor camera(path, numFrames, frameDiff);
	if (!camera.capture.isOpened()) {
		Logger::Critical("Error opening video file");
		return 1;
	}
	camera.run();
	Logger::Info("the camera process is finised");

	return 0;
}