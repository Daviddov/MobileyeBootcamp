#include "Server.h"
#include "ListeningManager.h"
#include "ConfigurationManager.h"


int main() {
	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();
	Logger::Info("the programme is started");

	Queue<FrameWrap> dataFromCamera;

	thread listenThread(startListen,ref(dataFromCamera));

	ServerProcessor server(dataFromCamera);
	thread runThread(&ServerProcessor::run, &server);

	runThread.join();
	listenThread.join();

	Logger::Info("the programme is finised");

	return 0;
}