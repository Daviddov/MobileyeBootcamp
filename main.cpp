#include "lib/Header.h"


int main() {

	queue<FrameWrap> dataFromCamera;
	std::mutex queueMutex; // Mutex to protect access to the queue

	std::thread cameraThread(cameraPart, std::ref(dataFromCamera), std::ref(queueMutex));
	std::thread serverThread(serverPart, std::ref(dataFromCamera), std::ref(queueMutex));


	cameraThread.join();
	serverThread.join();

	//cameraPart(dataFromCamera);
	//serverPart(dataFromCamera);
	
	

	return 0;
}







