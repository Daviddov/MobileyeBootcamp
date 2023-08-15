
#include "lib/Camera.h"
#include "lib/Server.h"

//something instead waitKey for exit from while(true) in camera part.
//mutex!!!!!!!!!!!!



int main() {

	queue<FrameWrap> dataFromCamera;
	bool isActive = true;

	thread cameraThread(cameraPart, ref(dataFromCamera), ref(isActive));

	thread serverThread(serverPart, ref(dataFromCamera), ref(isActive));

	cameraThread.join();
	serverThread.join();
	
	return 0;
}

