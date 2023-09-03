
#include "Header.h"
#include "Camera.h"
#include "ConfigurationManeger.h"


int main() {
	 //configRun(); //config json example

	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();
	Logger::Info("the programme is started");

	Queue<FrameWrap> dataFromCamera;

	CameraProcessor* camera = new CameraProcessor(dataFromCamera,1, "assets/parking.mp4");

	CameraProcessor::cameraPart(camera);

	Logger::Info("the programme is finised");

	return 0;
}