
#include "Header.h"
#include "CameraProcessor.h"
#include "ConfigurationManager.h"


int main() {
	 //configRun(); //config json example

	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();

	Logger::Info("the camera process is started");

	CameraProcessor camera("assets/parking.mp4", 30, 0.9);
	if (!camera.capture.isOpened()) {
		Logger::Critical("Error opening video file");
		return 1;
	}
	camera.run();
	Logger::Info("the camera process is finised");

	return 0;
}