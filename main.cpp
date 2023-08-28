
#include "Header.h"
#include "CameraManager.h"
#include "Server.h"
#include "json.hpp"

int main() {

	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();
	Logger::Info("the programe is started");

	queue<FrameWrap> dataFromCamera;

	int id = 1;

	string path = R"(./assets/parking.mp4)";



	CameraManager CManager(dataFromCamera);

	CManager.addCamera(id, path);

	CManager.startCameraRun(id);



	ServerProcessor server(dataFromCamera);

	thread serverThread(ServerProcessor::serverPart, ref(server));

	serverThread.join();

	Logger::Info("the programme is finised");

	return 0;
}