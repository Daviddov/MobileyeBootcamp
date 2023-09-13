#include "Server.h"
#include "ServerListeningManager.h"

int main() {
	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();

	Logger::Info("the server process is started");

	Queue<FrameWrap> dataFromCamera;
	condition_variable conditionVar;

	ServerListeningManager service(dataFromCamera, conditionVar);
	thread listenThread(&ServerListeningManager::startListen,&service);

	ServerProcessor server(dataFromCamera, conditionVar);
	thread runThread(&ServerProcessor::run, &server);

	listenThread.join();
	runThread.join();

	Logger::Info("the server process is finised");

	return 0;
}