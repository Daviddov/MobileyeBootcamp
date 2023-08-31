
#include "Header.h"
#include "ListeningManager.h"
#include "Server.h"


int main() {
	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();
	Logger::Info("the programme is started");

	queue<FrameWrap> dataFromCamera;

	ListeningManager CManager(dataFromCamera);

	thread listenThread(ListeningManager::startListen, ref(CManager));

	ServerProcessor server(dataFromCamera);

	thread runThread(ServerProcessor::serverPart, ref(server));

	runThread.join();
	listenThread.join();

	Logger::Info("the programme is finised");

	return 0;
}