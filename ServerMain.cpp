
#include "Header.h"
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

	ListeningManager LManager(dataFromCamera);

	thread listenThread(ListeningManager::startListen, ref(LManager));

	ServerProcessor server(dataFromCamera);

	thread runThread(ServerProcessor::serverPart, ref(server));

	runThread.join();
	listenThread.join();

	Logger::Info("the programme is finised");

	return 0;
}