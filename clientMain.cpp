#include <grpc++/grpc++.h>
#include "Header.h"
#include "CameraProcessor.h"
#include "ConfigurationManager.h"


int main() {
	 //configRun(); //config json example

	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();
	Logger::Info("the programme is started");

	Queue<FrameWrap> dataFromCamera;

	CameraProcessor camera(dataFromCamera,1, "assets/parking.mp4");

	CameraProcessor::cameraPart(camera);

	Logger::Info("the programme is finised");

	return 0;
}