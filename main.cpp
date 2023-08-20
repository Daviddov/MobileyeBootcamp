
#include "lib/Camera.h"
#include "lib/Server.h"

//something instead waitKey for exit from while(true) in camera part and server part(if size == 0).
//mutex!!!!!!!!!!!!


int main() {

	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();
	Logger::Info("the programe is started");

	queue<FrameWrap> dataFromCamera;

	CameraProcessor camera(dataFromCamera);

	ServerProcessor server(dataFromCamera);

	thread cameraThread(CameraProcessor::cameraPart, ref(camera));
	
	thread serverThread(ServerProcessor::serverPart, ref(server));

	cameraThread.join();
	serverThread.join();
	Logger::Info("the programe is finised");

	return 0;
}

