#include "lib/Header.h"
#include "lib/CameraManager.h"
//#include "lib/Camera.h"
#include "lib/Server.h"


int main() {
	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();
	Logger::Info("the programe is started");

	queue<FrameWrap> dataFromCamera;

	int id = 1;

	string path = R"(./assets/parking.mp4)";
	//string path = R"(C:\Users\1\Desktop\project_files\police.mp4)";


	CameraManager CManager(dataFromCamera);

	CManager.addCamera(id, path);

	CManager.startCameraRun(id);



	ServerProcessor server(dataFromCamera);

	thread serverThread(ServerProcessor::serverPart, ref(server));

	serverThread.join();

	Logger::Info("the programme is finised");

	return 0;
}