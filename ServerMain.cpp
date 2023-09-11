#include "Server.h"
#include "ListeningManager.h"


int main() {
	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();

	Logger::Info("the server process is started");

	Queue<FrameWrap> dataFromCamera;
	condition_variable conditionVar;

	ListeningManager service(dataFromCamera, conditionVar);
	thread listenThread(&ListeningManager::startListen,&service);

	ServerProcessor server(dataFromCamera, conditionVar);
	thread runThread(&ServerProcessor::run, &server);

	listenThread.join();
	runThread.join();

	Logger::Info("the server process is finised");

	return 0;
}