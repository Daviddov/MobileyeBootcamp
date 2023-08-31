
#include "Header.h"
#include "CameraManager.h"
#include "Server.h"
#include "ConfigurationManeger.h"

int main() {
	 //configRun(); //config json example

	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();
	Logger::Info("the programme is started");

	Queue<FrameWrap> dataFromCamera;

	int id = 1;

	thread listenThread(ListeningManager::startListen, ref(CManager));

	ServerProcessor server(dataFromCamera);

	thread serverThread(ServerProcessor::serverPart, ref(server));

	serverThread.join();

	Logger::Info("the programme is finised");

	return 0;
}