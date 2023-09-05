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

	

	CameraProcessor camera("assets/parking.mp4");

	if (!camera.init(30, 0.9))
	{
		Logger::Critical("the path is not found");
		return 1;
	}

	camera.run();

	Logger::Info("the programme is finised");

	

	return 0;
}